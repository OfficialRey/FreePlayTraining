#include "pch.h"

#include "FreePlayTraining.h"


// Util

TrainingMode* FreePlayTraining::GetCurrentGUIMode() {
	switch (CurrentContext)
	{
	case FreePlayTraining::RECOVERY:
		return new RecoveryMode{};
	case FreePlayTraining::PATHING:
		return new PathingMode{};
	case FreePlayTraining::POP:
		return new PopMode{};
	case FreePlayTraining::GOALIE:
		return new GoalieMode{};
	default:
		return new RecoveryMode{};
	}
}

ServerWrapper FreePlayTraining::GetServerWrapper() {
	return gameWrapper->GetCurrentGameState();
}
BallWrapper FreePlayTraining::GetBall() {
	ServerWrapper wrapper = GetServerWrapper();
	if (!wrapper) { return NULL; }
	return wrapper.GetBall();
}
CarWrapper FreePlayTraining::GetLocalCar() {
	return gameWrapper->GetLocalCar();
}

CameraWrapper FreePlayTraining::GetCamera() {
	return gameWrapper->GetCamera();
}

bool FreePlayTraining::IsInFreeplay() {
	return gameWrapper->IsInFreeplay();
}