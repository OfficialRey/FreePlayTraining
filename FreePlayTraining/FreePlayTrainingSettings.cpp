#include "pch.h"

#include "FreePlayTraining.h"

#define PLUGIN_NAME "Enhanced Freeplay"

#define RECOVERY_MODE "Recovery Training"
#define RECOVERY_TOOLTIP "Show recovery training options"


void FreePlayTraining::RenderSettings() {
	RenderModeSelection();
}

void FreePlayTraining::RenderModeSelection() {
	if (ImGui::Button(RECOVERY_MODE)) {
		gameWrapper->Execute([this](GameWrapper* gw) {
			cvarManager->executeCommand(RECOVERY_COMMAND);
			});
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip(RECOVERY_TOOLTIP);
	}
}

std::string FreePlayTraining::GetPluginName() {
	return PLUGIN_NAME;
}

void FreePlayTraining::SetImGuiContext(uintptr_t) {

}