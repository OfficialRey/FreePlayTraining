#pragma once

#include "pch.h"
#include "GameInformation.h"

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"

#include "RecoveryMode.h"
#include "PathingMode.h"
#include "GoalieMode.h"
#include "PopMode.h"

#define RECOVERY_COMMAND "load_recovery"
#define PATHING_COMMAND "load_boost_pathing"
#define POP_COMMAND "load_ball_pop"
#define GOALIE_COMMAND "load_ball_save"

#define FREEPLAY_COMMAND "load_freeplay"

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class FreePlayTraining : public BakkesMod::Plugin::BakkesModPlugin, public SettingsWindowBase
{

	enum MenuContext{RECOVERY, PATHING, POP, GOALIE};

private:
	MenuContext CurrentContext = RECOVERY;
	GameInformation* GameInfo = nullptr;
	TrainingMode* CurrentMode = nullptr;


	void ChangeCurrentMode(TrainingMode*);
	void CheckCurrentMode();
	void ResetMode();

	void UpdateInfoPackage();

	// GUI

	void RenderModeSelection();
	void RenderModeSettings();
	void RenderRecoveryOptions();
	void RenderPathingOptions();
	void RenderPopOptions();

	void RenderGameSettings();

	void RenderButton(const char*, const char*, std::function<void()>);
	void RenderIntSlider(const char*, const char*, const char*, int, int);
	void RenderFloatSlider(const char*, const char*, const char*, float, float);
	float ClampValue(float, float, float);

	// Variables

	void RegisterVariables();
	void RegisterVariable(std::string, float, float, float, std::shared_ptr<float>*);
	void ResetVariables();

	// Recovery

	std::shared_ptr<float> RecoveryBaseTime;
	std::shared_ptr<float> RecoveryBoostFactor;
	std::shared_ptr<float> RecoveryTimeFactor;
	std::shared_ptr<float> RecoveryMaxBoost;
	std::shared_ptr<float> RecoveryBoostDecay;

	// Pathing

	std::shared_ptr<float> PathingBaseTime;
	std::shared_ptr<float> PathingBoostCollectionTime;
	std::shared_ptr<float> PathingBallTouchTime;
	std::shared_ptr<float> PathingRecoveryBonus;
	std::shared_ptr<float> PathingBallBoostBonus;
	std::shared_ptr<float> PathingMaxBoost;
	std::shared_ptr<float> PathingBoostDecay;

	// Pop

	std::shared_ptr<float> PopBaseTime;
	std::shared_ptr<float> PopMinBallHeight;
	std::shared_ptr<float> PopGravity;
	std::shared_ptr<float> PopMaxBoost;
	std::shared_ptr<float> PopBoostDecay;

	// Goalie

	std::shared_ptr<float> GoalieBallSpeed;
	std::shared_ptr<float> GoalieBallPlacement;

	// Util

	TrainingMode* GetCurrentGUIMode();
	ServerWrapper GetServerWrapper();
	BallWrapper GetBall();
	CarWrapper GetLocalCar();
	CameraWrapper GetCamera();
	bool IsInFreeplay();

public:

	void onLoad() override;

	// GUI

	void RenderSettings() override;


	~FreePlayTraining();

	// Events

	void Run();
	void OnBallHit();
	void OnCollectBoost();
	void OnGoalScored();
	void OnReplayStart();
	void OnReplayEnd();
	void OnResetTraining();
	void OnQuitMatch();
};
