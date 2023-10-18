#include "pch.h"

#include "FreePlayTraining.h"


// Util

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