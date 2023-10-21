#pragma once

#include "TrainingMode.h"

#define PATHING_BASE_DEFAULT_TIME 15
#define BOOST_PICKUP_TIME_INCREASE 0.66
#define BALL_TOUCH_TIME_INCREASE 3
#define CUSTOM_BOOST_DECAY_PER_SECOND 1
#define BALL_HEIGHT_BOOST_GAIN_FACTOR (150 * 100)

#define RECOVERY_BONUS 600

#define MAX_BOOST 0.75

#define PATHING_TIMER_YELLOW 7
#define PATHING_TIMER_GREEN 12

class PathingMode : public TrainingMode
{

private:

	Vector BallPosition{0, 0 , 100};

	void DecayBoost(GameInformation*);
	void SetBallPosition(GameInformation*);
	void LimitBoost(GameInformation*);

public:

	PathingMode();

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

