#pragma once

#include "pch.h"
#include "GameInformation.h"

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"

#include "TrainingMode.h"

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);




class FreePlayTraining : public BakkesMod::Plugin::BakkesModPlugin
{

private:
	double OldTime;
	double DeltaTime;
	TrainingMode* CurrentMode;

	void onLoad() override;
	void ChangeCurrentMode(TrainingMode*);
	void CalculateDeltaTime();

	GameInformation BuildInfoPackage();

public:
	void Run();
	void OnBallHit();
	void OnCollectBoost();
	void OnGoalScored();

	ServerWrapper GetServerWrapper();
	BallWrapper GetBall();
	CarWrapper GetLocalCar();
	CameraWrapper GetCamera();
	bool IsInFreeplay();

};
