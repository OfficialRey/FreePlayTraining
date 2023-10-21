#pragma once

#include "pch.h"

#include "Utility.h"

#include "TrainingMode.h"

#define POP_TIMER_GREEN 10.0f
#define POP_TIMER_YELLOW 5.0f

// Base Time

#define POP_BASE_MIN_TIME 15
#define POP_BASE_DEFAULT_TIME 30
#define POP_BASE_MAX_TIME 60

#define POP_BASE_TIME_TITLE "POP_BASE_TIME"
#define POP_BASE_TIME_USER_TITLE "Base Time"
#define POP_BASE_TIME_USER_TOOLTIP "Change Base Time"

// Minimum Ball Height

#define POP_BALL_MIN_HEIGHT 200
#define POP_BALL_DEFAULT_HEIGHT 200
#define POP_BALL_MAX_HEIGHT (CEILING / 2)

#define POP_BALL_HEIGHT_TITLE "POP_BALL_HEIGHT"
#define POP_BALL_HEIGHT_USER_TITLE "Minimum Ball Height"
#define POP_BALL_HEIGHT_USER_TOOLTIP "Change Minimum Ball Height"

// Gravity

#define GRAVITY_OFFSET 1.0f

#define POP_MIN_GRAVITY 0.5f
#define POP_DEFAULT_GRAVITY 1.0f
#define POP_MAX_GRAVITY 2.0f

#define POP_GRAVITY_TITLE "POP_GRAVITY"
#define POP_GRAVITY_USER_TITLE "Gravity Force"
#define POP_GRAVITY_USER_TOOLTIP "Change Gravity Force"

// Max Boost

#define POP_BOOST_MIN_MAX 25
#define POP_BOOST_DEFAULT_MAX 100
#define POP_BOOST_MAX_MAX 100

#define POP_BOOST_MAX_TITLE "POP_BOOST_MAX"
#define POP_BOOST_MAX_USER_TITLE "Max Boost"
#define POP_BOOST_MAX_USER_TOOLTIP "Change Max Boost"

// Boost Decay

#define POP_BOOST_MIN_DECAY 0.0f
#define POP_BOOST_DEFAULT_DECAY 0.0f
#define POP_BOOST_MAX_DECAY 5.0f

#define POP_BOOST_DECAY_TITLE "POP_BOOST_DECAY"
#define POP_BOOST_DECAY_USER_TITLE "Boost Decay"
#define POP_BOOST_DECAY_USER_TOOLTIP "Change Boost Decay"

#define MIN_BALL_HEIGHT 200

#define START_POSITION Vector{0,0, CEILING}
#define START_VELOCITY Vector{0,0, QUARTER_CEILING}

class PopMode : public TrainingMode
{

private:

	double PopBaseTime;
	unsigned int PopMinBallHeight;
	double PopGravity;

	void EnhanceGravity(GameInformation*);
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
