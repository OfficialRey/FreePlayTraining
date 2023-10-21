#include "pch.h"

#include "FreePlayTraining.h"

// Game Buttons

#define START_BUTTON_TITLE "Launch Training"
#define START_BUTTON_TOOLTIP "Launch training with current settings"

#define STOP_BUTTON_TITLE "Stop Training"
#define STOP_BUTTON_TOOLTIP "Stop current training"

#define RESET_BUTTON_TITLE "Reset Settings"
#define RESET_BUTTON_TOOLTIP "Reset parameter values"

#define PATHING_TITLE "Pathing Training"
#define PATHING_TOOLTIP "Show pathing training options"

#define POP_TITLE "Pop Control Training"
#define POP_TOOLTIP "Show pop control training options"

#define GOALIE_TITLE "Goalie Training"
#define GOALIE_TOOLTIP "Show goalie training options"

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
		break;
	case FreePlayTraining::POP:
		break;
	case FreePlayTraining::GOALIE:
		break;
	default:
		break;
	}
}

void FreePlayTraining::RenderGameSettings() {
	RenderButton(START_BUTTON_TITLE, START_BUTTON_TOOLTIP, [this]() {
		ChangeCurrentMode(GetCurrentGUIMode());
		});
}

void FreePlayTraining::RenderRecoveryOptions() {
	RenderFloatSlider(RECOVERY_BASE_TIME_TITLE, RECOVERY_BASE_TIME_USER_TITLE, RECOVERY_BASE_TIME_USER_TOOLTIP, RECOVERY_BASE_MIN_TIME, RECOVERY_BASE_MAX_TIME);
	RenderFloatSlider(RECOVERY_BOOST_FACTOR_TITLE, RECOVERY_BOOST_FACTOR_USER_TITLE, RECOVERY_BOOST_FACTOR_USER_TOOLTIP, RECOVERY_BOOST_MIN_FACTOR, RECOVERY_BOOST_MAX_FACTOR);
	RenderFloatSlider(RECOVERY_TIME_FACTOR_TITLE, RECOVERY_TIME_FACTOR_USER_TITLE, RECOVERY_TIME_FACTOR_USER_TOOLTIP, RECOVERY_TIME_MIN_FACTOR, RECOVERY_TIME_MAX_FACTOR);
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
	if (!customVariable) { 
		cvarManager->log("Variable was null");
		return; }
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