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

	GameState(Vector carLocation, Vector carVelocity, Vector carAngularVelocity, Rotator carRotation, float carBoost, Vector ballLocation, Vector ballVelocity, Vector ballAngularVelocity, Rotator ballRotation) : CarLocation(carLocation), CarVelocity(carVelocity), CarAngularVelocity(carAngularVelocity), CarRotation(carRotation), CarBoost(carBoost), BallLocation(ballLocation), BallVelocity(ballVelocity), BallAngularVelocity(ballAngularVelocity), BallRotation(ballRotation) {
	}
};