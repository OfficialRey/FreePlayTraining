#pragma once

#include "pch.h"

#include "GameInformation.h"
#include "Utility.h"

#define STARTING_LOCATION Vector{0, -200, 20}
#define STARTING_TIME 3

class TrainingMode
{
private:

	double TimeRemaining = 0;

	void ExecuteTimer(GameInformation gameInfo);
	void RenderTimer(CanvasWrapper canvas);



protected:
	virtual void RunGame(GameInformation) = 0;
	virtual void EnableGame(GameInformation) = 0;
	virtual void RenderGame(CanvasWrapper) = 0;

public:

	void Run(GameInformation);

	void OnEnable(GameInformation);
	virtual void OnDisable(GameInformation) = 0;


	virtual void OnBallHit(GameInformation) = 0;
	virtual void OnBoostPickUp(GameInformation) = 0;

	void Render(CanvasWrapper);
};