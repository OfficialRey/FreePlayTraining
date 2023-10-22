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

struct GameState {

	Vector CarLocation = 0;
	Vector CarVelocity = 0;
	Vector CarAngularVelocity = 0;
	Rotator CarRotation = 0;
	float CarBoost = 0;

	Vector BallLocation = 0;
	Vector BallVelocity = 0;
	Vector BallAngularVelocity = 0;
	Rotator BallRotation = 0;

	bool IsValid = false;

	GameState(GameInformation* gameInfo) {
		if (!gameInfo->IsValid()) { return; }
		CarWrapper car = gameInfo->Car;
		BoostWrapper boost = car.GetBoostComponent();
		BallWrapper ball = gameInfo->Ball;

		CarLocation = car.GetLocation();
		CarVelocity = car.GetVelocity();
		CarAngularVelocity = car.GetAngularVelocity();
		CarRotation = car.GetRotation();
		CarBoost = boost.GetCurrentBoostAmount();

		BallLocation = ball.GetLocation();
		BallVelocity = ball.GetVelocity();
		BallAngularVelocity = ball.GetAngularVelocity();
		BallRotation = ball.GetRotation();

		IsValid = true;
	}
};