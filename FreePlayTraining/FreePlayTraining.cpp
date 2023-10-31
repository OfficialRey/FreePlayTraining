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
	RegisterCommands();
	RegisterEvents();
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

void FreePlayTraining::ResetMode() {
	ChangeCurrentMode(nullptr);
	cvarManager->executeCommand(COMMAND_UNLIMITED_BOOST);
}

void FreePlayTraining::UpdateInfoPackage() {
	GameInfo->Update(GetLocalCar(), GetBall());
}

// Loop

void FreePlayTraining::Run() {
	UpdateInfoPackage();
	if (!CurrentMode || !GameInfo->IsValid()) { return; }
	CurrentMode->Run(GameInfo);
}