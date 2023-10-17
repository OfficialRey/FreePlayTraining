#pragma once

#include "pch.h"

#include "Utility.h"

#include "FreePlayCar.h"

struct GameInformation {

public:

	CarWrapper Car = 0;
	BallWrapper Ball = 0;
	std::shared_ptr<CVarManagerWrapper> CVarManager;

	double DeltaTime;

	GameInformation(CarWrapper car, BallWrapper ball) {
		Car = car;
		Ball = ball;
	}

	void Update(CarWrapper car, BallWrapper ball) {
		Car = car;
		Ball = ball;

		CalculateDeltaTime();
	}

private:

	unsigned long long PreviousTime;

	void CalculateDeltaTime() {
		unsigned long long currentTime = GetTimeMilliSeconds();
		DeltaTime = (currentTime - PreviousTime) / MILLI_SECONDS;
		PreviousTime = currentTime;
	}
};