#pragma once

#include "pch.h"

struct GameInformation {
	BallWrapper Ball;
	CarWrapper Car;
	std::shared_ptr<CVarManagerWrapper> CVarManager;
	double DeltaTime;

	bool IsValid() {
		return Ball && Car && CVarManager;
	}
};