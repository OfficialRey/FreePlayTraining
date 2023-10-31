#pragma once

#include "pch.h"

#include "GameInformation.h"
#include "Utility.h"

#define STARTING_LOCATION Vector{0, -200, 20}
#define PRE_GAME_TIMER 3
#define DEFAULT_ROTATION Rotator{0, (int) (((double) MAX_ROTATION.Y - (double) MIN_ROTATION.Y) * 0.25),0}

#define END_GAME_TIMER 5

#define STALL_DELAY 0.1

enum TrainingState {
	UNDEFINED,
	PRE_GAME,
	POST_GAME,
	STALLED,
	RUNNING,
	REPLAY,
	DONE
};

class TrainingMode
{
private:

	GameState* StallState = 0;
	TrainingState OldTrainingState = UNDEFINED;
	TrainingState CurrentTrainingState = PRE_GAME;

	bool AutoReduceTime = false; // Use clock automatically
	bool DisableGoal = true; // Disable goal scoring

	double MaxBoost = FULL_BOOST;
	double BoostDecay = 0;

	double PreGameTimer = PRE_GAME_TIMER;
	double PostGameTimer = END_GAME_TIMER;

	double YellowTime = 0;
	double GreenTime = 0;

	double StallTime = 0;

	void ChangeCurrentTrainingState(TrainingState);

	void ExecuteGameStall(GameInformation*);

	void ExecutePreGameTimer(GameInformation*);
	void ExecutePostGameTimer(GameInformation*);
	void ExecuteGameLoop(GameInformation*);

	void ExecuteTimer(GameInformation*);

	void RenderPreGameTimer(CanvasWrapper);
	void RenderGameResult(CanvasWrapper);

	void LimitBoost(GameInformation*);
	void DecayBoost(GameInformation*);
	void DisableGoals(GameInformation*);

	void RenderStats(CanvasWrapper);

protected:

	double TimeRemaining = 0;
	double CurrentTime = 0;

	double CurrentScore = 0;
	double PossibleScore = 0;

	void Reset();
	void EndGame();

	void StallGame(GameState*, double);

	void AddScore(int, int);

	virtual void RunGame(GameInformation*) = 0;
	virtual void EnableGame(GameInformation*) = 0;
	virtual void OnReplayBegin(GameInformation*) = 0;
	virtual void OnReplayEnd() = 0;
	virtual void RenderGame(CanvasWrapper) = 0;

	void SetBoostLimitation(bool);
	void SkipGoalReplay();

public:
	TrainingMode(double greenTime = 0, double yellowTime = 0, bool autoReduceTime = true, unsigned int maxBoost = 100, float boostDecay = 0);

	void Run(GameInformation*);

	void OnEnable(GameInformation*);
	virtual void OnDisable(GameInformation*) = 0;
	
	virtual void OnBallHit(GameInformation*) = 0;
	virtual void OnBoostPickUp(GameInformation*) = 0;
	virtual void OnGoalScored(GameInformation*) = 0;
	virtual void OnTimeRunOut(GameInformation*) = 0;

	void ReplayBegin(GameInformation*);
	void ReplayEnd();

	void Render(CanvasWrapper);
	virtual void RenderGameEnd(CanvasWrapper) = 0;

	bool IsState(TrainingState);
};