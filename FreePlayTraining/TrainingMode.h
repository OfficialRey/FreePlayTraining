#pragma once

#include "GameInformation.h"

#include "pch.h"

class TrainingMode
{
public:

	virtual void Run(GameInformation) = 0;
	virtual void OnEnable(GameInformation) = 0;
	virtual void OnDisable(GameInformation) = 0;


	virtual void OnBallHit(GameInformation) = 0;
	virtual void onBoostPickUp(GameInformation) = 0;

	virtual void Render(CanvasWrapper) = 0;
};