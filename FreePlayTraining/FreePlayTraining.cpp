#include "pch.h"

#include "FreePlayTraining.h"

#include "Utility.h"

BAKKESMOD_PLUGIN(FreePlayTraining, "A plugin to help develop several abilities using freeplay", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

FreePlayTraining::~FreePlayTraining() {
	delete GameInfo;
	delete CurrentMode;
}

void FreePlayTraining::onLoad()
{
	_globalCvarManager = cvarManager;
	GameInfo = new GameInformation{ GetLocalCar(), GetBall()};

	// Register game loop
	gameWrapper->HookEvent(HOOK_ENGINE_TICK, [this](std::string eventName) {
		Run();
		});

	// Register game events
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

	// Register commands
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

	// Variables

	RegisterVariables();
}

void FreePlayTraining::ChangeCurrentMode(TrainingMode* mode) {
	// Free memory of old TrainingMode
	if (CurrentMode) { 
		if (!IsInFreeplay()) { cvarManager->executeCommand(FREEPLAY_COMMAND); }
		CurrentMode->OnDisable(GameInfo);
		gameWrapper->UnregisterDrawables();
		delete CurrentMode;
	}

	// Assign new TrainingMode
	CurrentMode = mode;
	if (!mode) { return; }
	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
		CurrentMode->Render(canvas);
		});
	CurrentMode->OnEnable(GameInfo);
}

void FreePlayTraining::CheckCurrentMode() {
	if (!CurrentMode) { return; }
	if (GameInfo->IsValid() && !CurrentMode->IsState(DONE) && IsInFreeplay()) { return; }
	ResetMode();
}

void FreePlayTraining::ResetMode() {
	ChangeCurrentMode(nullptr);
	cvarManager->executeCommand(COMMAND_UNLIMITED_BOOST);
}

void FreePlayTraining::UpdateInfoPackage() {
	GameInfo->Update(GetLocalCar(), GetBall());
}

// Loop

void FreePlayTraining::Run() {
	CheckCurrentMode();
	UpdateInfoPackage();
	if (!CurrentMode) { return; }
	CurrentMode->Run(GameInfo);
}