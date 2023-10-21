#include "GuiUtility.h"

void RenderButton(const char* title, const char* tooltip, std::function<void()> functionToRun) {
	if (ImGui::Button(title)) {
		gameWrapper->Execute([this](GameWrapper*) {
			cvarManager->executeCommand(RECOVERY_COMMAND);
			});
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip(RECOVERY_TOOLTIP);
	}
}