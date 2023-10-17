#pragma once

#include "TrainingMode.h"

#define STARTING_TIME 15
#define BOOST_PICKUP_TIME_INCREASE 0.75
#define BALL_TOUCH_TIME_INCREASE 3
#define CUSTOM_BOOST_DECAY_PER_SECOND 3
#define BOOST_DECAY_PER_SECOND 33
#define BALL_HEIGHT_BOOST_GAIN_FACTOR (150 * 100)

#define RECOVERY_BONUS 600

class PathingMode : public TrainingMode
{

private:

	Vector BallPosition{0, 0 , 100};

	double TimeLeft = STARTING_TIME;
	double CurrentTime = 0;
	LinearColor Color{ 255, 255, 255, 255 };

	void StartMode(GameInformation);
	void DecayBoost(GameInformation);
	void SetBallPosition(GameInformation);

public:

	PathingMode() = default;

	virtual void CheckGameOver();

	virtual void RunGame(GameInformation);
	virtual void EnableGame(GameInformation);
	virtual void OnDisable(GameInformation);

	virtual void OnBallHit(GameInformation);
	virtual void OnBoostPickUp(GameInformation);
	virtual void OnGoalScored(GameInformation);

	virtual void RenderGame(CanvasWrapper);
};

