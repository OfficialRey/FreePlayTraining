#pragma once

#include "pch.h"

#include "TrainingMode.h"

class AirDribbleMode : public TrainingMode
{

private:
	enum ShotType {
		WALL,
		MID_AIR,
		GROUND_TO_AIR
	};

	void CreateShot();
	void IsBallDropped(GameInformation*);

public:

	AirDribbleMode() = default;

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

