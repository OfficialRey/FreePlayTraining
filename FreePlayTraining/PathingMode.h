#pragma once

#include "TrainingMode.h"

#define STARTING_TIME 10
#define TIME_INCREASE 1.5

class PathingMode : public TrainingMode
{

private:
	float TimeLeft;
	float CurrentTime;
	LinearColor Color{};

	void StartMode(GameInformation);

public:

	PathingMode() = default;

	virtual void Run(GameInformation);
	virtual void OnEnable(GameInformation);
	virtual void OnDisable(GameInformation);

	virtual void OnBallHit(GameInformation);
	virtual void onBoostPickUp(GameInformation);

	virtual void Render(CanvasWrapper);
};

