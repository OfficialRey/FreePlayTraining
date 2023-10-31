#pragma once

#include "TrainingMode.h"

#define PATHING_TIMER_YELLOW 7.0f
#define PATHING_TIMER_GREEN 12.0f

#define PATHING_TITLE "Pathing Training"
#define PATHING_TOOLTIP "Show pathing training options"

// Base Time

#define PATHING_BASE_MIN_TIME 5
#define PATHING_BASE_DEFAULT_TIME 15
#define PATHING_BASE_MAX_TIME 20

#define PATHING_BASE_TIME_TITLE "PATHING_BASE_TIME"
#define PATHING_BASE_TIME_USER_TITLE "Base Time"
#define PATHING_BASE_TIME_USER_TOOLTIP "Change Base Time"

// Max Boost

#define PATHING_BOOST_MIN_MAX 50
#define PATHING_BOOST_DEFAULT_MAX 100
#define PATHING_BOOST_MAX_MAX 100

#define PATHING_BOOST_MAX_TITLE "PATHING_BOOST_MAX"
#define PATHING_BOOST_MAX_USER_TITLE "Max Boost"
#define PATHING_BOOST_MAX_USER_TOOLTIP "Change Max Boost"

// Boost Decay

#define PATHING_BOOST_MIN_DECAY 0.0f
#define PATHING_BOOST_DEFAULT_DECAY 0.0f
#define PATHING_BOOST_MAX_DECAY 3.0f

#define PATHING_BOOST_DECAY_TITLE "PATHING_BOOST_DECAY"
#define PATHING_BOOST_DECAY_USER_TITLE "Boost Decay"
#define PATHING_BOOST_DECAY_USER_TOOLTIP "Change Boost Decay"

// Boost Collection Time Bonus

#define PATHING_BOOST_COLLECTION_MIN_TIME 0.5f
#define PATHING_BOOST_COLLECTION_DEFAULT_TIME 0.66f
#define PATHING_BOOST_COLLECTION_MAX_TIME 1.0f

#define PATHING_BOOST_COLLECTION_TITLE "PATHING_BOOST_COLLECTION_TIME"
#define PATHING_BOOST_COLLECTION_USER_TITLE "Boost Collection Time Bonus"
#define PATHING_BOOST_COLLECTION_USER_TOOLTIP "Change Boost Collection Time Bonus"

// Ball Touch Time Bonus

#define PATHING_BALL_TOUCH_MIN_TIME 2.5f
#define PATHING_BALL_TOUCH_DEFAULT_TIME 3.5f
#define PATHING_BALL_TOUCH_MAX_TIME 5.0f

#define PATHING_BALL_TOUCH_TITLE "PATHING_BALL_TOUCH_TIME"
#define PATHING_BALL_TOUCH_USER_TITLE "Ball Touch Time Bonus"
#define PATHING_BALL_TOUCH_USER_TOOLTIP "Change Ball Touch Time Bonus"

// Recovery Bonus

#define PATHING_MIN_RECOVERY 0
#define PATHING_DEFAULT_RECOVERY 600
#define PATHING_MAX_RECOVERY 1200

#define PATHING_RECOVERY_TITLE "PATHING_RECOVERY"
#define PATHING_RECOVERY_USER_TITLE "Recovery Bonus"
#define PATHING_RECOVERY_USER_TOOLTIP "Change Recovery Bonus"

// Ball Height Boost Bonus

#define BALL_HEIGHT_NORMALIZER 15000

#define PATHING_BALL_MIN_BONUS 0.0f
#define PATHING_BALL_DEFAULT_BONUS 1.0f
#define PATHING_BALL_MAX_BONUS 1.5f

#define PATHING_BALL_BONUS_TITLE "PATHING_BALL_HEIGHT_BONUS"
#define PATHING_BALL_BONUS_USER_TITLE "Boost Bonus"
#define PATHING_BALL_BONUS_USER_TOOLTIP "Change Boost Bonus"


class PathingMode : public TrainingMode
{

private:

	Vector BallPosition{ 0, 0, 100 };
	double PathingBaseTime;
	double PathingBoostCollectionTime;
	double PathingBallTouchTime;
	double PathingRecoveryBonus;
	double PathingBallHeightBoostBonus;

	void SetBallPosition(GameInformation*);

public:

	PathingMode();

	virtual void RunGame(GameInformation*);
	virtual void EnableGame(GameInformation*);
	virtual void OnDisable(GameInformation*);

	virtual void OnBallHit(GameInformation*);
	virtual void OnBoostPickUp(GameInformation*);
	virtual void OnGoalScored(GameInformation*);
	virtual void OnReplayBegin(GameInformation*);
	virtual void OnReplayEnd();
	virtual void OnTimeRunOut(GameInformation*);

	virtual void RenderGame(CanvasWrapper);
	virtual void RenderGameEnd(CanvasWrapper);
};

