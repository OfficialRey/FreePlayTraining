#pragma once

#include "TrainingMode.h"

#define BASE_RECOVERY_TIME 4.5

#define TIMER_YELLOW 3
#define TIMER_GREEN 5

class RecoveryMode : public TrainingMode
{

private:

	double RecoveryTime;
	double RecoveriesSucceeded;
	double RecoveriesGeneral;

	Vector RecoveryPosition;
	Vector RecoveryTarget;

	void SetTargetPosition(GameInformation*);
	void TickClock(GameInformation*);

	void LoseRound(GameInformation*);
	void WinRound(GameInformation*);

public:

	RecoveryMode() = default;

	virtual void CheckGameOver();

	virtual void RunGame(GameInformation*);
	virtual void EnableGame(GameInformation*);
	virtual void OnDisable(GameInformation*);

	virtual void OnBallHit(GameInformation*);
	virtual void OnBoostPickUp(GameInformation*);
	virtual void OnGoalScored(GameInformation*);
	virtual void OnReplayBegin(GameInformation*);
	virtual void OnReplayEnd(GameInformation*);

	virtual void RenderGame(CanvasWrapper);
	virtual void RenderGameEnd(CanvasWrapper);
};