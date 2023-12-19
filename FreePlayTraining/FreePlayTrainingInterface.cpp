#include "pch.h"

#include "FreePlayTraining.h"

// Game Buttons

#define START_BUTTON_TITLE "Launch Training"
#define START_BUTTON_TOOLTIP "Launch training with current settings"

#define STOP_BUTTON_TITLE "Stop Training"
#define STOP_BUTTON_TOOLTIP "Stop current training"

#define RESET_BUTTON_TITLE "Reset Settings"
#define RESET_BUTTON_TOOLTIP "Reset parameter values"



#define POP_TITLE "Pop Control Training"
#define POP_TOOLTIP "Show pop control training options"

void FreePlayTraining::RenderSettings() {
	RenderModeSelection();
	RenderModeSettings();
	RenderGameSettings();
}

void FreePlayTraining::RenderModeSelection() {
	RenderButton(RECOVERY_TITLE, RECOVERY_TOOLTIP, [this]() {
		CurrentContext = RECOVERY;
		});
	ImGui::SameLine();
	RenderButton(PATHING_TITLE, PATHING_TOOLTIP, [this]() {
		CurrentContext = PATHING;
		});
	ImGui::SameLine();
	RenderButton(POP_TITLE, POP_TOOLTIP, [this]() {
		CurrentContext = POP;
		});
	ImGui::SameLine();
	RenderButton(GOALIE_TITLE, GOALIE_TOOLTIP, [this]() {
		CurrentContext = GOALIE;
		});
}

void FreePlayTraining::RenderModeSettings() {
	switch (CurrentContext)
	{
	case FreePlayTraining::RECOVERY:
		RenderRecoveryOptions();
		break;
	case FreePlayTraining::PATHING:
		RenderPathingOptions();
		break;
	case FreePlayTraining::POP:
		RenderPopOptions();
		break;
	case FreePlayTraining::GOALIE:
		RenderGoalieOptions();
		break;
	default:
		break;
	}
}

void FreePlayTraining::RenderGameSettings() {
	RenderButton(START_BUTTON_TITLE, START_BUTTON_TOOLTIP, [this]() {
		ChangeCurrentMode(GetCurrentGUIMode());
		});
	ImGui::SameLine();
	RenderButton(STOP_BUTTON_TITLE, STOP_BUTTON_TOOLTIP, [this]() {
		ResetMode();
		});
	ImGui::SameLine();
	RenderButton(RESET_BUTTON_TITLE, RESET_BUTTON_TOOLTIP, [this]() {
		ResetVariables();
		});
}

void FreePlayTraining::RenderRecoveryOptions() {
	RenderFloatSlider(RECOVERY_BASE_TIME_TITLE, RECOVERY_BASE_TIME_USER_TITLE, RECOVERY_BASE_TIME_USER_TOOLTIP, RECOVERY_BASE_MIN_TIME, RECOVERY_BASE_MAX_TIME);
	RenderFloatSlider(RECOVERY_BOOST_FACTOR_TITLE, RECOVERY_BOOST_FACTOR_USER_TITLE, RECOVERY_BOOST_FACTOR_USER_TOOLTIP, RECOVERY_BOOST_MIN_FACTOR, RECOVERY_BOOST_MAX_FACTOR);
	RenderFloatSlider(RECOVERY_TIME_FACTOR_TITLE, RECOVERY_TIME_FACTOR_USER_TITLE, RECOVERY_TIME_FACTOR_USER_TOOLTIP, RECOVERY_TIME_MIN_FACTOR, RECOVERY_TIME_MAX_FACTOR);
	RenderIntSlider(RECOVERY_BOOST_MAX_TITLE, RECOVERY_BOOST_MAX_USER_TITLE, RECOVERY_BOOST_MAX_USER_TOOLTIP, RECOVERY_BOOST_MIN_MAX, RECOVERY_BOOST_MAX_MAX);
	RenderIntSlider(RECOVERY_BOOST_DECAY_TITLE, RECOVERY_BOOST_DECAY_USER_TITLE, RECOVERY_BOOST_DECAY_USER_TOOLTIP, RECOVERY_BOOST_MIN_DECAY, RECOVERY_BOOST_MAX_DECAY);
}

void FreePlayTraining::RenderPathingOptions() {
	RenderFloatSlider(PATHING_BASE_TIME_TITLE, PATHING_BASE_TIME_USER_TITLE, PATHING_BASE_TIME_USER_TOOLTIP, PATHING_BASE_MIN_TIME, PATHING_BASE_MAX_TIME);
	RenderFloatSlider(PATHING_BOOST_COLLECTION_TITLE, PATHING_BOOST_COLLECTION_USER_TITLE, PATHING_BOOST_COLLECTION_USER_TOOLTIP, PATHING_BOOST_COLLECTION_MIN_TIME, PATHING_BOOST_COLLECTION_MAX_TIME);
	RenderFloatSlider(PATHING_BALL_TOUCH_TITLE, PATHING_BALL_TOUCH_USER_TITLE, PATHING_BALL_TOUCH_USER_TOOLTIP, PATHING_BALL_TOUCH_MIN_TIME, PATHING_BALL_TOUCH_MAX_TIME);
	RenderFloatSlider(PATHING_BALL_BONUS_TITLE, PATHING_BALL_BONUS_USER_TITLE, PATHING_BALL_BONUS_USER_TOOLTIP, PATHING_BALL_MIN_BONUS, PATHING_BALL_MAX_BONUS);
	RenderIntSlider(PATHING_RECOVERY_TITLE, PATHING_RECOVERY_USER_TITLE, PATHING_RECOVERY_USER_TOOLTIP, PATHING_MIN_RECOVERY, PATHING_MAX_RECOVERY);
	RenderIntSlider(PATHING_BOOST_MAX_TITLE, PATHING_BOOST_MAX_USER_TITLE, PATHING_BOOST_MAX_USER_TOOLTIP, PATHING_BOOST_MIN_MAX, PATHING_BOOST_MAX_MAX);
	RenderIntSlider(PATHING_BOOST_DECAY_TITLE, PATHING_BOOST_DECAY_USER_TITLE, PATHING_BOOST_DECAY_USER_TOOLTIP, PATHING_BOOST_MIN_DECAY, PATHING_BOOST_MAX_DECAY);
}

void FreePlayTraining::RenderPopOptions() {
	RenderFloatSlider(POP_BASE_TIME_TITLE, POP_BASE_TIME_USER_TITLE, PATHING_BASE_TIME_USER_TOOLTIP, POP_BASE_MIN_TIME, POP_BASE_MAX_TIME);
	RenderIntSlider(POP_BALL_HEIGHT_TITLE, POP_BALL_HEIGHT_USER_TITLE, POP_BALL_HEIGHT_USER_TOOLTIP, POP_BALL_MIN_HEIGHT, POP_BALL_MAX_HEIGHT);
	RenderFloatSlider(POP_GRAVITY_TITLE, POP_GRAVITY_USER_TITLE, POP_GRAVITY_USER_TOOLTIP, POP_MIN_GRAVITY, POP_MAX_GRAVITY);
	RenderIntSlider(POP_BOOST_MAX_TITLE, POP_BOOST_MAX_USER_TITLE, POP_BOOST_MAX_USER_TOOLTIP, POP_BOOST_MIN_MAX, POP_BOOST_MAX_MAX);
	RenderIntSlider(POP_BOOST_DECAY_TITLE, POP_BOOST_DECAY_USER_TITLE, POP_BOOST_DECAY_USER_TOOLTIP, POP_BOOST_MIN_DECAY, POP_BOOST_MAX_DECAY);
}

void FreePlayTraining::RenderGoalieOptions() {
	RenderFloatSlider(GOALIE_BALL_SPEED_TITLE, GOALIE_BALL_SPEED_USER_TITLE, GOALIE_BALL_SPEED_USER_TOOLTIP, GOALIE_BALL_SPEED_MIN_FACTOR, GOALIE_BALL_SPEED_MAX_FACTOR);
	RenderFloatSlider(GOALIE_BALL_PLACEMENT_TITLE, GOALIE_BALL_PLACEMENT_USER_TITLE, GOALIE_BALL_PLACEMENT_USER_TOOLTIP, GOALIE_BALL_MIN_PLACEMENT, GOALIE_BALL_MAX_PLACEMENT);
	RenderIntSlider(GOALIE_BOOST_MAX_TITLE, GOALIE_BOOST_USER_TITLE, GOALIE_BOOST_USER_TOOLTIP, GOALIE_BOOST_MIN_MAX, GOALIE_BOOST_MAX_MAX);
}

void FreePlayTraining::RenderButton(const char* title, const char* tooltip, std::function<void()> target) {
	if (ImGui::Button(title)) {
		target();
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip(tooltip);
	}
}

void FreePlayTraining::RenderFloatSlider(const char* variable,const char* title, const char* tooltip, float min, float max) {
	CVarWrapper customVariable = cvarManager->getCvar(variable);
	if (!customVariable) { return; }
	float value = customVariable.getFloatValue();
	if (ImGui::SliderFloat(title, &value, min, max)) {
		customVariable.setValue(ClampValue(value, min, max));
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip(tooltip);
	}
}

void FreePlayTraining::RenderIntSlider(const char* variable, const char* title, const char* tooltip, int min, int max) {
	CVarWrapper customVariable = cvarManager->getCvar(variable);
	if (!customVariable) { return; }
	int value = customVariable.getIntValue();
	if (ImGui::SliderInt(title, &value, min, max)) {
		customVariable.setValue(ClampValue((float) value, (float) min, (float) max));
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip(tooltip);
	}
}

float FreePlayTraining::ClampValue(float value, float min, float max) {
	if (value < min) { return min; }
	if (value > max) { return max; }
	return value;
}