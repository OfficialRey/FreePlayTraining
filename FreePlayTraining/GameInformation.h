#pragma once

#include "pch.h"

struct GameInformation {
	BallWrapper Ball;
	CarWrapper Car;
	std::shared_ptr<CVarManagerWrapper> CVarManager;
	double DeltaTime;
};