#include "pch.h"

#include "FreePlayTraining.h"

#include "RecoveryMode.h"
#include "PathingMode.h"
#include "GoalieMode.h"

#include "Utility.h"

BAKKESMOD_PLUGIN(FreePlayTraining, "A plugin to help develop several abilities using freeplay", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

FreePlayTraining::~FreePlayTraining() {
	delete GameInfo;
}

void FreePlayTraining::onLoad()
{
	_globalCvarManager = cvarManager;
	GameInfo = new GameInformation{ GetLocalCar(), GetBall()};

	// Register game loop
	gameWrapper->HookEvent("Function Engine.Interaction.Tick", [this](std::string eventName) {
		Run();
		});

	// Register game events
	gameWrapper->HookEvent("Function TAGame.Ball_TA.OnCarTouch", [this](std::string eventName) {
		OnBallHit();
		});	
	gameWrapper->HookEvent("Function TAGame.VehiclePickup_Boost_TA.Pickup", [this](std::string eventName) {
		OnCollectBoost();
		});
	gameWrapper->HookEvent("Function TAGame.Ball_TA.OnHitGoal", [this](std::string eventName) {
		OnGoalScored();
		});
	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.ReplayPlayback.BeginState", [this](std::string eventName) {
		OnReplayStart();
		});
	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.ReplayPlayback.EndState", [this](std::string eventName) {
		OnReplayEnd();
		});

	// Register commands
	cvarManager->registerNotifier("Recovery", [this](std::vector<std::string> args) {
		ChangeCurrentMode(new RecoveryMode{});
		}, "", PERMISSION_ALL);	
	
	cvarManager->registerNotifier("Pathing", [this](std::vector<std::string> args) {
		ChangeCurrentMode(new PathingMode{});
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("Goalie", [this](std::vector<std::string> args) {
		ChangeCurrentMode(new GoalieMode{});
		}, "", PERMISSION_ALL);
}

void FreePlayTraining::ChangeCurrentMode(TrainingMode* mode) {
	// Free memory of old TrainingMode
	if (CurrentMode) { 
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

void FreePlayTraining::UpdateInfoPackage() {
	GameInfo->Update(GetLocalCar(), GetBall());
}

// Loop

void FreePlayTraining::Run() {
	UpdateInfoPackage();
	if (!IsInFreeplay()) { 
		ChangeCurrentMode(NULL);
		return; 
	}
	if (!CurrentMode || CurrentMode->IsGameOver) { return; }
	CurrentMode->Run(GameInfo);
}

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