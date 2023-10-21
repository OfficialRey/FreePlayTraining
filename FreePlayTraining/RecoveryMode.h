#pragma once

#include "TrainingMode.h"
#include "Utility.h"

#define RECOVERY_TIMER_YELLOW 3.0f
#define RECOVERY_TIMER_GREEN 5.0f

#define RECOVERY_TITLE "Recovery Training"
#define RECOVERY_TOOLTIP "Show recovery training options"

// Base Time

#define RECOVERY_BASE_MIN_TIME 3.0f
#define RECOVERY_BASE_DEFAULT_TIME 4.5f
#define RECOVERY_BASE_MAX_TIME 5.0f

#define RECOVERY_BASE_TIME_TITLE "RECOVERY_BASE_TIME"
#define RECOVERY_BASE_TIME_USER_TITLE "Base Time"
#define RECOVERY_BASE_TIME_USER_TOOLTIP "Change Base Time"

// Boost Factor

#define RECOVERY_BOOST_MIN_FACTOR 0.75f
#define RECOVERY_BOOST_DEFAULT_FACTOR 1.0f
#define RECOVERY_BOOST_MAX_FACTOR 1.25f

#define RECOVERY_BOOST_FACTOR_TITLE "RECOVERY_BOOST_FACTOR"
#define RECOVERY_BOOST_FACTOR_USER_TITLE "Boost Factor"
#define RECOVERY_BOOST_FACTOR_USER_TOOLTIP "Change Boost Factor"

// Time Factor

#define RECOVERY_TIME_MIN_FACTOR 0.9f
#define RECOVERY_TIME_DEFAULT_FACTOR 1.0f
#define RECOVERY_TIME_MAX_FACTOR 1.5f

#define RECOVERY_TIME_FACTOR_TITLE "RECOVERY_TIME_FACTOR"
#define RECOVERY_TIME_FACTOR_USER_TITLE "Time Factor"
#define RECOVERY_TIME_FACTOR_USER_TOOLTIP "Change Time Factor"

class RecoveryMode : public TrainingMode
{

private:

	float BaseTime;
	float BoostFactor;
	float TimeFactor;

	Vector RecoveryPosition;
	Vector RecoveryTarget;

	void SetTargetPosition(GameInformation*);

	void LoseRound(GameInformation*);
	void WinRound(GameInformation*);

public:

	RecoveryMode();

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