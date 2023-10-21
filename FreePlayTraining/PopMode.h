#pragma once

#include "pch.h"

#include "Utility.h"

#include "TrainingMode.h"

#define POP_START_TIME 30
#define POP_TIMER_GREEN 20
#define POP_TIMER_YELLOW 10

#define MIN_BALL_HEIGHT 200

#define START_POSITION Vector{0,0, CEILING}
#define START_VELOCITY Vector{0,0, QUARTER_CEILING}

class PopMode : public TrainingMode
{

private:

	void DecayTime(GameInformation*);

public:

	PopMode();

	virtual void CheckGameOver();

	virtual void RunGame(GameInformation*);
	virtual void EnableGame(GameInformation*);
	virtual void OnDisable(GameInformation*);

	virtual void OnBallHit(GameInformation*);
	virtual void OnBoostPickUp(GameInformation*);
	virtual void OnGoalScored(GameInformation*);
	virtual void OnReplayBegin(GameInformation*);
	virtual void OnReplayEnd(GameInformation*);
	virtual void OnTimeRunOut(GameInformation*);

	virtual void RenderGame(CanvasWrapper);
	virtual void RenderGameEnd(CanvasWrapper);

};
