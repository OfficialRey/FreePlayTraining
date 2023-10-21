#pragma once

#include "pch.h"

#include "Utility.h"

struct GameInformation {

public:

	CarWrapper Car = 0;
	BallWrapper Ball = 0;

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

	bool IsValid() {
		return Car && Ball && DeltaTime >= 0;
	}

private:

	unsigned long long PreviousTime;

	void CalculateDeltaTime() {
		unsigned long long currentTime = (unsigned long long) GetTimeMilliSeconds();
		DeltaTime = (currentTime - PreviousTime) / MILLI_SECONDS;
		PreviousTime = currentTime;
	}
};