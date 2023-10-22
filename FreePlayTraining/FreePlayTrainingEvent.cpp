#include "pch.h"

#include "FreePlayTraining.h"


// Events

void FreePlayTraining::OnBallHit() {
	if (!CurrentMode || !CurrentMode->IsState(RUNNING)) { return; }
	CurrentMode->OnBallHit(GameInfo);
}

void FreePlayTraining::OnCollectBoost() {
	if (!CurrentMode || !CurrentMode->IsState(RUNNING)) { return; }
	CurrentMode->OnBoostPickUp(GameInfo);
}

void FreePlayTraining::OnGoalScored() {
	if (!CurrentMode || !CurrentMode->IsState(RUNNING)) { return; }
	CurrentMode->OnGoalScored(GameInfo);
}

void FreePlayTraining::OnReplayStart() {
	if (!CurrentMode || !CurrentMode->IsState(RUNNING)) { return; }
	CurrentMode->ReplayBegin(GameInfo);
}

void FreePlayTraining::OnReplayEnd() {
	if (!CurrentMode || !CurrentMode->IsState(RUNNING)) { return; }
	CurrentMode->ReplayEnd(GameInfo);
}

void FreePlayTraining::OnResetTraining() {
	ResetMode();
}

void FreePlayTraining::OnQuitMatch() {
	ResetMode();
}