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

	bool AutoReduceTime = false;

	double PreGameTimer = 0;
	double EndGameTimer = 0;

	double YellowTime = 0;
	double GreenTime = 0;

	void ExecutePreGameTimer(GameInformation* gameInfo);
	void ExecutePostGameTimer(GameInformation* gameInfo);
	void ExecuteGameLoop(GameInformation* gameInfo);

	void ExecuteTimer(GameInformation* gameInfo);
	void OnGameEnable(GameInformation* gameInfo);

	void RenderPreGameTimer(CanvasWrapper canvas);
	

protected:

	double TimeRemaining = 0;
	double CurrentTime = 0;

	double CurrentScore = 0;
	double PossibleScore = 0;

	void Reset();
	void EndGame();

	virtual void RunGame(GameInformation*) = 0;
	virtual void EnableGame(GameInformation*) = 0;
	virtual void RenderGame(CanvasWrapper) = 0;

public:

	TrainingMode();
	TrainingMode(double, double, bool);

	bool IsGameOver = false;
	bool Running = false;

	bool IsActive();

	void Run(GameInformation*);

	void OnEnable(GameInformation*);
	virtual void OnDisable(GameInformation*) = 0;
	
	virtual void OnBallHit(GameInformation*) = 0;
	virtual void OnBoostPickUp(GameInformation*) = 0;
	virtual void OnGoalScored(GameInformation*) = 0;
	virtual void OnReplayBegin(GameInformation*) = 0;
	virtual void OnReplayEnd(GameInformation*) = 0;
	virtual void OnTimeRunOut(GameInformation*) = 0;

	void Render(CanvasWrapper);
	virtual void RenderGameEnd(CanvasWrapper) = 0;
};