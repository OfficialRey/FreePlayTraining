#pragma once

#include "pch.h"

#include "Utility.h"
#include "TrainingMode.h"

#define SHOT_FACTOR 0.5

class GoalieMode : public TrainingMode
{
private:

	enum ShotType {
		BACKPOST,
		AERIAL_REVERSE
	};

	void StartMode(GameInformation);

public:

	GoalieMode() = default;

	virtual void CheckGameOver();

	virtual void RunGame(GameInformation);
	virtual void EnableGame(GameInformation);
	virtual void OnDisable(GameInformation);

	virtual void OnBallHit(GameInformation);
	virtual void OnBoostPickUp(GameInformation);
	virtual void OnGoalScored(GameInformation);

	virtual void RenderGame(CanvasWrapper);
};

