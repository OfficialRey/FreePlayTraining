#pragma once

#include "pch.h"

#include "GameInformation.h"
#include "Utility.h"

#define STARTING_LOCATION Vector{0, -200, 20}
#define STARTING_TIME 3
#define DEFAULT_ROTATION Rotator{0, (int) (((double) MAX_ROTATION.Y - (double) MIN_ROTATION.Y) * 0.25),0}

#define END_TIME 5

class TrainingMode
{
private:

	double EndTime = 0;
	double TimeRemaining = 0;

	void ExecuteTimer(GameInformation* gameInfo);
	void RenderTimer(CanvasWrapper canvas);

protected:

	virtual void RunGame(GameInformation*) = 0;
	virtual void EnableGame(GameInformation*) = 0;
	virtual void RenderGame(CanvasWrapper) = 0;
	virtual void CheckGameOver() = 0;

public:

	bool IsGameOver;

	void Run(GameInformation*);

	void OnEnable(GameInformation*);
	virtual void OnDisable(GameInformation*) = 0;
	
	virtual void OnBallHit(GameInformation*) = 0;
	virtual void OnBoostPickUp(GameInformation*) = 0;
	virtual void OnGoalScored(GameInformation*) = 0;
	virtual void OnReplayBegin(GameInformation*) = 0;
	virtual void OnReplayEnd(GameInformation*) = 0;

	void Render(CanvasWrapper);
	virtual void RenderGameEnd(CanvasWrapper) = 0;
};