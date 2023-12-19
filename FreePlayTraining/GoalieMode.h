#pragma once

#include "pch.h"

#include "Utility.h"
#include "TrainingMode.h"

#define SHOT_HEIGHT_DISTANCE_FACTOR 0.52f
#define SHOT_HEIGHT_LOCATION_FACTOR 0.55f
#define SHOT_HEIGHT_ADJUSTMENT 1.2f
#define SHOT_OFFSET 200

#define GOALIE_TITLE "Goalie Training"
#define GOALIE_TOOLTIP "Show goalie training options"

#define SHOT_FACTOR 0.5f
#define SHOT_MIN_SPEED MAX_SPEED * 1.5f
#define SHOT_MAX_SPEED MAX_SPEED * 3
#define STALL_TIME 1

#define MIN_SAVE_ANGLE 45
#define MIN_SHOT_SAVE_TIME 1

// Ball Speed

#define GOALIE_BALL_SPEED_MIN_FACTOR 0.9f
#define GOALIE_BALL_SPEED_DEFAULT_FACTOR 1.0f
#define GOALIE_BALL_SPEED_MAX_FACTOR 1.2f

#define GOALIE_BALL_SPEED_TITLE "GOALIE_BALL_SPEED"
#define GOALIE_BALL_SPEED_USER_TITLE "Ball Speed"
#define GOALIE_BALL_SPEED_USER_TOOLTIP "Change Ball Speed"

// Shot Placement Height

#define GOALIE_BALL_MIN_PLACEMENT 0.5f
#define GOALIE_BALL_DEFAULT_PLACEMENT 0.8f
#define GOALIE_BALL_MAX_PLACEMENT 1.0f

#define GOALIE_BALL_PLACEMENT_TITLE "GOALIE_BALL_PLACEMENT"
#define GOALIE_BALL_PLACEMENT_USER_TITLE "Ball Placement Strength"
#define GOALIE_BALL_PLACEMENT_USER_TOOLTIP "Change Ball Placement Strength"


// Min and Max Boost

#define GOALIE_BOOST_MIN_MAX 25
#define GOALIE_BOOST_DEFAULT_MAX 100
#define GOALIE_BOOST_MAX_MAX 100

#define GOALIE_BOOST_MAX_TITLE "GOALIE_MAX_BOOST"
#define GOALIE_BOOST_USER_TITLE "Max Boost"
#define GOALIE_BOOST_USER_TOOLTIP "Change Max Boost"


class GoalieMode : public TrainingMode
{
private:

	double GoalieBallSpeedFactor;
	double GoalieBallPlacementFactor;

	double BallHitTimer = 0;

	enum ShotType {
		BACKPOST,
		AERIAL_REVERSE
	};

	void CreateShot();
	void CheckSave(GameInformation*);
	bool IsBallSaved(GameInformation*);

public:

	GoalieMode();

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

