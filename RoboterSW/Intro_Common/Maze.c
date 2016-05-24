/*
 * Maze.c
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_CONFIG_HAS_LINE_MAZE
#include "Maze.h"
#include "Turn.h"
#include "CLS1.h"
#include "LineFollow.h"
#include "Event.h"
#include "UTIL1.h"
#include "Shell.h"
#include "Reflectance.h"

#define MAZE_MIN_LINE_VAL      0x60   /* minimum value indicating a line */
static uint16_t SensorHistory[REF_NOF_SENSORS]; /* value of history while moving forward */
static ALGORITHM_Kind solver = LEFT_HAND;
static uint16_t solvedIndx = 0;

void MAZE_SetSolveAlgorithm(ALGORITHM_Kind algorithm)
{
	solver = algorithm;
}

ALGORITHM_Kind MAZE_GetSolveAlgorithm()
{
	return solver;
}

static void MAZE_SampleSensorHistory(void) {
  uint8_t i;
  uint16_t val[REF_NOF_SENSORS];

  REF_GetSensorValues(&val[0], REF_NOF_SENSORS);
  for(i=0; i<REF_NOF_SENSORS; i++) {
    if (val[i]>=(MAZE_MIN_LINE_VAL)) { /* only count line values */
      if (val[i]>SensorHistory[i]) {
        SensorHistory[i] = val[i];
      }
    }
  }
}

/*!
 * \brief Called during turning, will use it to sample sensor values.
 */
static bool MAZE_SampleTurnStopFunction(void) {
  MAZE_SampleSensorHistory();
  return FALSE; /* do not stop turning */
}

static REF_LineKind MAZE_HistoryLineKind(void) {
  int i, cnt, cntLeft, cntRight;

  cnt = cntLeft = cntRight = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (SensorHistory[i]>MAZE_MIN_LINE_VAL) { /* count only line values */
      cnt++;
      if (i<REF_NOF_SENSORS/2) {
        cntLeft++;
      } else {
        cntRight++;
      }
    }
  }
  if (cnt==0) {
    return REF_LINE_NONE;
  } else if (cnt==REF_NOF_SENSORS) {
    return REF_LINE_FULL;
  } else if (cntLeft>cntRight) {
    return REF_LINE_LEFT;
  } else { /* must be cntRight>cntLeft */
    return REF_LINE_RIGHT;
  }
}

void MAZE_ClearSensorHistory(void) {
  int i;

  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorHistory[i] = 0;
  }
}


#define MAZE_MAX_PATH        64 /* maximum number of turns in path */

static TURN_Kind path[MAZE_MAX_PATH]; /* recorded maze */
static uint16_t pathLength = 0; /* number of entries in path[] */
static bool isSolved = FALSE; /* if we have solved the maze */

static TURN_Kind RevertTurn(TURN_Kind turn) {
  if (turn==TURN_LEFT90) {
    turn = TURN_RIGHT90;
  } else if (turn==TURN_RIGHT90) {
    turn = TURN_LEFT90;
  }
  return turn;
}

/**
 * \brief Reverts the path 
 */
static void MAZE_RevertPath(void) {
  int i, j;
  TURN_Kind tmp;
  
  if (pathLength==0) {
    return;
  }
  j = pathLength-1;
  i = 0;
  while(i<=j) {
    tmp = path[i];
    path[i] = RevertTurn(path[j]);
    path[j] = RevertTurn(tmp);

	if(TURN_RIGHT90==path[i])
	{
		SHELL_SendString((unsigned char*)"R");
	}
	else if(TURN_LEFT90==path[i])
	{
		SHELL_SendString((unsigned char*)"L");
	}
	else if(TURN_STRAIGHT==path[i])
	{
		SHELL_SendString((unsigned char*)"S");
	}
	
    i++; j--;
  }
    SHELL_SendString((unsigned char*)"\r\n");
}

TURN_Kind MAZE_SelectTurn(REF_LineKind prev, REF_LineKind curr) {
	TURN_Kind selectedTurn = TURN_STOP;

	/* Dead ends are handled before this !!! */

	if(prev==REF_LINE_FULL && curr==REF_LINE_FULL)
	{
		return TURN_FINISHED;
	}
	if(solver == LEFT_HAND)
	{
		if ((prev==REF_LINE_FULL || prev==REF_LINE_LEFT) && curr!=REF_LINE_FULL)
		{
			SHELL_SendString((unsigned char*)"turn: L\r\n");
			selectedTurn = TURN_LEFT90;
		}
		else if (curr==REF_LINE_STRAIGHT)
		{
			SHELL_SendString((unsigned char*)"turn: S\r\n");
			selectedTurn = TURN_STRAIGHT;
		}
		else
		{
			SHELL_SendString((unsigned char*)"turn: R\r\n");
			selectedTurn = TURN_RIGHT90;
		}
	} else if(solver == RIGHT_HAND) {
		if ((prev== REF_LINE_FULL || prev==REF_LINE_RIGHT) && curr!=REF_LINE_FULL)
		{
			SHELL_SendString((unsigned char*)"turn: R\r\n");
			selectedTurn = TURN_RIGHT90;
		}
		else if (curr==REF_LINE_STRAIGHT)
		{
			SHELL_SendString((unsigned char*)"turn: S\r\n");
			selectedTurn = TURN_STRAIGHT;
		}
		else
		{
			SHELL_SendString((unsigned char*)"turn: L\r\n");
			selectedTurn = TURN_LEFT90;
		}
	} else if (solver == STRAIGHT_HAND) {
		if (curr==REF_LINE_STRAIGHT) {
			SHELL_SendString((unsigned char*)"turn: S\r\n");
			selectedTurn = TURN_STRAIGHT;
		} else if ((prev== REF_LINE_FULL || prev==REF_LINE_LEFT) && curr!=REF_LINE_FULL) {
			SHELL_SendString((unsigned char*)"turn: L\r\n");
			selectedTurn = TURN_LEFT90;
		} else {
			SHELL_SendString((unsigned char*)"turn: R\r\n");
			selectedTurn = TURN_RIGHT90;
		}
		/* First crosssection over -> go to default algorithm */
		MAZE_SetSolveAlgorithm(LEFT_HAND);
	}
	//after the selection is done, add the turn to the solution path
	MAZE_AddPath(selectedTurn);
	return selectedTurn;
}

void MAZE_SetSolved(void) {
  isSolved = TRUE;
  /*! \todo here the path could be reverted */
  MAZE_SimplifyPath();
  MAZE_RevertPath();
  MAZE_AddPath(TURN_STOP); /* add an action to stop */
}

bool MAZE_IsSolved(void) {
  return isSolved;
}

void MAZE_AddPath(TURN_Kind kind) {
  if (pathLength<MAZE_MAX_PATH) {
    path[pathLength] = kind;
    pathLength++;
  } else {
    /* error! */
  }
}

uint8_t MAZE_RemovePathOnIndex(uint8_t index)
{
	int i;

	if(index >= pathLength)
	{
		return ERR_OVERFLOW;
	}
	path[index] = 0;
	for(i = index; i < pathLength; i++)
	{
		path[i] = path[i+1];
	}
	pathLength--;
	return ERR_OK;
}
/*!
 * \brief Performs path simplification.
 * The idea is that whenever we encounter x-TURN_RIGHT180-x or x-TURN_LEFT180-x, we simplify it by cutting the dead end.
 * For example if we have TURN_LEFT90-TURN_RIGHT180-TURN_LEFT90, this can be simplified with TURN_STRAIGHT.
 */
void MAZE_SimplifyPath(void) {
	int i = 0;
	unsigned char dst;

	while(i < (pathLength-2))
	{
		//check if index' neighbour is a U-turn
		if(path[i+1] == TURN_RIGHT180 || path[i+1] == TURN_LEFT180)
		{
			// R U S => L
			if(path[i] == TURN_RIGHT90 && path[i+2] == TURN_STRAIGHT)
			{
			  path[i] = TURN_LEFT90;
			}
			// S U R => L
			else if(path[i] == TURN_STRAIGHT && path[i+2] == TURN_RIGHT90)
			{
			  path[i] = TURN_LEFT90;
			}
			// L U R => U
			else if(path[i] == TURN_LEFT90 && path[i+2] == TURN_RIGHT90)
			{
			  path[i] = TURN_RIGHT180;
			}
			// R U R => S
			else if(path[i] == TURN_RIGHT90 && path[i+2] == TURN_RIGHT90)
			{
			  path[i] = TURN_STRAIGHT;
			}
			// L U S => R
			else if(path[i] == TURN_LEFT90 && path[i+2] == TURN_STRAIGHT)
			{
			  path[i] = TURN_RIGHT90;
			}
			// R U L => U
			else if(path[i] == TURN_RIGHT90 && path[i+2] == TURN_LEFT90)
			{
				path[i] = TURN_RIGHT180;
			}
			// L U L => S
			else if(path[i] == TURN_LEFT90 && path[i+2] == TURN_LEFT90)
			{
				path[i] = TURN_STRAIGHT;
			}
			// S U S => U
			else if(path[i] == TURN_STRAIGHT && path[i+2] == TURN_STRAIGHT)
			{
				path[i] = TURN_RIGHT180;
			}
			// S U L => R
			else if(path[i] == TURN_STRAIGHT && path[i+2] == TURN_LEFT90)
			{
				path[i] = TURN_RIGHT90;
			}
			//remove the U and its following turn kind from the path
			MAZE_RemovePathOnIndex(i+2);
			MAZE_RemovePathOnIndex(i+1);
			//set index back one step
			if(path[i] == TURN_RIGHT180)
			{
			  i--;
			}
		}
		else
		{
			i++;
		}
	}
}

/*!
 * \brief Performs a turn.
 * \return Returns TRUE while turn is still in progress.
 */
uint8_t MAZE_EvaluteTurn(bool *finished) {
	REF_LineKind historyLineKind, currLineKind;
	TURN_Kind turn;

	*finished = FALSE;
	currLineKind = REF_GetLineKind();
	if (isSolved)
	{
		TURN_Turn(TURN_STEP_LINE_FW_POST_LINE,MAZE_SampleTurnStopFunction);
		turn = MAZE_GetSolvedTurn(&solvedIndx);
		CLS1_SendNum16s(solvedIndx,CLS1_GetStdio()->stdOut);
	}
	else if(currLineKind==REF_LINE_NONE) { /* nothing, must be dead end */
		SHELL_SendString((unsigned char*)"turn: U\r\n");
		turn = TURN_LEFT180;
		MAZE_AddPath(turn);
	}
	else
	{
		MAZE_ClearSensorHistory(); /* clear history values */
		MAZE_SampleSensorHistory(); /* store current values */
		TURN_Turn(TURN_STEP_LINE_FW_POST_LINE, MAZE_SampleTurnStopFunction); /* do the line and beyond in one step */
		historyLineKind = MAZE_HistoryLineKind(); /* new read new values */
		currLineKind = REF_GetLineKind();
		turn = MAZE_SelectTurn(historyLineKind, currLineKind);
	}
	if (turn==TURN_FINISHED) {
		*finished = TRUE;
		//LF_StopFollowing();
		TURN_Turn(TURN_RIGHT180,MAZE_SampleTurnStopFunction);
		SHELL_SendString((unsigned char*)"MAZE: finished!\r\n");
		return ERR_OK;
	} else if (turn==TURN_STRAIGHT) {
		/*! \todo Extend if necessary */
		//SHELL_SendString((unsigned char*)"going straight\r\n");
		return ERR_OK;
	} else if (turn==TURN_STOP) { /* should not happen here? */
		LF_StopFollowing();
		SHELL_SendString((unsigned char*)"Failure, stopped!!!\r\n");
		return ERR_FAILED; /* error case */
	}
	else
	{
		TURN_Turn(turn,MAZE_SampleTurnStopFunction);
		/*! \todo (optional) Extend if necessary */
		return ERR_OK; /* turn finished */
	}
}

static void MAZE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"maze", (unsigned char*)"Group of maze following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows maze help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  clear", (unsigned char*)"Clear the maze solution\r\n", io->stdOut);
}

#if PL_CONFIG_HAS_SHELL
static void MAZE_PrintStatus(const CLS1_StdIOType *io) {
  int i;
  
  CLS1_SendStatusStr((unsigned char*)"maze", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  solved", MAZE_IsSolved()?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  path", (unsigned char*)"(", io->stdOut);
  CLS1_SendNum8u(pathLength, io->stdOut);
  CLS1_SendStr((unsigned char*)") ", io->stdOut);
  for(i=0;i<pathLength;i++) {
    CLS1_SendStr(TURN_TurnKindStr(path[i]), io->stdOut);
    CLS1_SendStr((unsigned char*)" ", io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

uint8_t MAZE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"maze help")==0) {
    MAZE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"maze status")==0) {
    MAZE_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"maze clear")==0) {
    MAZE_ClearSolution();
    *handled = TRUE;
  }
  return res;
}
#endif

TURN_Kind MAZE_GetSolvedTurn(uint16_t *solvedIdx) {
  if (*solvedIdx < pathLength) {
    return path[(*solvedIdx)++];
  } else {
    return TURN_STOP; 
  }
}

void MAZE_ClearSolution(void) {
  isSolved = FALSE;
  solvedIndx = 0;
  pathLength = 0;
}

void MAZE_Deinit(void) {
}

void MAZE_Init(void) {
  MAZE_ClearSolution();
}
#endif /* PL_HAS_LINE_SENSOR */
