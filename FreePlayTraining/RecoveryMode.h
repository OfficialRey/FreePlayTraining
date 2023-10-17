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

	virtual void RunGame(GameInformation);
	virtual void EnableGame(GameInformation);
	virtual void OnDisable(GameInformation);

	virtual void OnBallHit(GameInformation);
	virtual void OnBoostPickUp(GameInformation);

	virtual void RenderGame(CanvasWrapper);
};