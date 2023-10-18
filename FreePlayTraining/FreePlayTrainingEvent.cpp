#include "pch.h"

#include "FreePlayTraining.h"


// Events

void FreePlayTraining::OnBallHit() {
	if (!CurrentMode || CurrentMode->IsGameOver) { return; }
	CurrentMode->OnBallHit(GameInfo);
}

void FreePlayTraining::OnCollectBoost() {
	if (!CurrentMode || CurrentMode->IsGameOver) { return; }
	CurrentMode->OnBoostPickUp(GameInfo);
}

void FreePlayTraining::OnGoalScored() {
	if (!CurrentMode || CurrentMode->IsGameOver) { return; }
	CurrentMode->OnGoalScored(GameInfo);
}

void FreePlayTraining::OnReplayStart() {
	if (!CurrentMode || CurrentMode->IsGameOver) { return; }
	CurrentMode->OnReplayBegin(GameInfo);
}

void FreePlayTraining::OnReplayEnd() {
	if (!CurrentMode || CurrentMode->IsGameOver) { return; }
	CurrentMode->OnReplayEnd(GameInfo);
}

void FreePlayTraining::OnResetTraining() {
	ResetMode();
}

void FreePlayTraining::OnQuitMatch() {
	ResetMode();
}