#pragma once

#include "TrainingMode.h"

class RecoveryMode : public TrainingMode
{

private:
	Vector RecoveryPosition;
	Vector RecoveryTarget;

	void SetTargetPosition(GameInformation);

public:

	RecoveryMode() = default;

	virtual void Run(GameInformation);
	virtual void OnEnable(GameInformation);
	virtual void OnDisable(GameInformation);

	virtual void OnBallHit(GameInformation);
	virtual void onBoostPickUp(GameInformation);
	
	virtual void Render(CanvasWrapper);
};