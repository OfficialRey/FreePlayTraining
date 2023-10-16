#include "pch.h"

#include "FreePlayTraining.h"

#include "RecoveryMode.h"
#include "PathingMode.h"

#include "Utility.h"

BAKKESMOD_PLUGIN(FreePlayTraining, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void FreePlayTraining::onLoad()
{
	_globalCvarManager = cvarManager;

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

	// Register commands
	cvarManager->registerNotifier("Recovery", [this](std::vector<std::string> args) {
		ChangeCurrentMode(new RecoveryMode{});
		}, "", PERMISSION_ALL);	
	
	cvarManager->registerNotifier("Pathing", [this](std::vector<std::string> args) {
		ChangeCurrentMode(new PathingMode{});
		}, "", PERMISSION_ALL);
}

void FreePlayTraining::ChangeCurrentMode(TrainingMode* mode) {
	if (!CurrentMode) { 
		gameWrapper->UnregisterDrawables();
		delete CurrentMode; 
	}
	CurrentMode = mode;
	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
		CurrentMode->Render(canvas);
		});
}

void FreePlayTraining::CalculateDeltaTime() {
	float currentTime = GetTimeSeconds();
	DeltaTime = currentTime - OldTime;
	OldTime = currentTime;
}

GameInformation FreePlayTraining::BuildInfoPackage() {
	return GameInformation{ GetBall(), GetLocalCar(), cvarManager, DeltaTime };
}

// Loop

void FreePlayTraining::Run() {
	if (!CurrentMode) { return; }
	CurrentMode->Run(BuildInfoPackage());
}

// Events

void FreePlayTraining::OnBallHit() {
	if (!CurrentMode) { return; }
	CurrentMode->OnBallHit(BuildInfoPackage());
}

void FreePlayTraining::OnCollectBoost() {
	if (!CurrentMode) { return; }
	CurrentMode->onBoostPickUp(BuildInfoPackage());
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