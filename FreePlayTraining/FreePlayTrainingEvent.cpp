#include "pch.h"

#include "FreePlayTraining.h"


// Events

void FreePlayTraining::RegisterCommands() {
	// Register game commands	
	cvarManager->registerNotifier(RECOVERY_COMMAND, [this](std::vector<std::string> args) {
	ChangeCurrentMode(new RecoveryMode{});
}, "", PERMISSION_ALL);

cvarManager->registerNotifier(PATHING_COMMAND, [this](std::vector<std::string> args) {
	ChangeCurrentMode(new PathingMode{});
	}, "", PERMISSION_ALL);

cvarManager->registerNotifier(GOALIE_COMMAND, [this](std::vector<std::string> args) {
	ChangeCurrentMode(new GoalieMode{});
	}, "", PERMISSION_ALL);

cvarManager->registerNotifier(POP_COMMAND, [this](std::vector<std::string> args) {
	ChangeCurrentMode(new PopMode{});
	}, "", PERMISSION_ALL);
}

void FreePlayTraining::RegisterEvents() {
	// Register game events
	gameWrapper->HookEvent(HOOK_ENGINE_TICK, [this](std::string eventName) {
		Run();
		});
	gameWrapper->HookEvent(HOOK_BALL_HIT, [this](std::string eventName) {
		OnBallHit();
		});
	gameWrapper->HookEvent(HOOK_PICKUP_BOOST, [this](std::string eventName) {
		OnCollectBoost();
		});
	gameWrapper->HookEvent(HOOK_GOAL_SCORED, [this](std::string eventName) {
		OnGoalScored();
		});
	gameWrapper->HookEvent(HOOK_GOAL_REPLAY_BEGIN, [this](std::string eventName) {
		OnReplayStart();
		});
	gameWrapper->HookEvent(HOOK_GOAL_REPLAY_END, [this](std::string eventName) {
		OnReplayEnd();
		});
	gameWrapper->HookEvent(HOOK_PLAYER_FREEPLAY_RESET, [this](std::string eventName) {
		OnResetTraining();
		});
	gameWrapper->HookEvent(HOOK_MATCH_QUIT, [this](std::string eventName) {
		OnQuitMatch();
		});
}

void FreePlayTraining::OnBallHit() {
	if(!GameInfo->IsValid()) { return; }
	if (!CurrentMode) { return; }
	CurrentMode->OnBallHit(GameInfo);
}

void FreePlayTraining::OnCollectBoost() {
	if (!GameInfo->IsValid()) { return; }
	if (!CurrentMode) { return; }
	CurrentMode->OnBoostPickUp(GameInfo);
}

void FreePlayTraining::OnGoalScored() {
	if (!GameInfo->IsValid()) { return; }
	if (!CurrentMode) { return; }
	CurrentMode->OnGoalScored(GameInfo);
}

void FreePlayTraining::OnReplayStart() {
	if (!GameInfo->IsValid()) { return; }
	if (!CurrentMode) { return; }
	CurrentMode->ReplayBegin(GameInfo);
}

void FreePlayTraining::OnReplayEnd() {
	if (!CurrentMode) { return; }
	CurrentMode->ReplayEnd();
}

void FreePlayTraining::OnResetTraining() {
	ResetMode();
}

void FreePlayTraining::OnQuitMatch() {
	ResetMode();
}