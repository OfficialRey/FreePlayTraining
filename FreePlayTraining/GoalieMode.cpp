#include "pch.h"
#include "GoalieMode.h"

void GoalieMode::StartMode(GameInformation gameInfo) {
	CarWrapper car = gameInfo.Car;
	BallWrapper ball = gameInfo.Ball;

	Vector ballPosition = Vector{ GetRandomFieldX() / 2, GetRandomFieldY() / 3, GetRandomFieldZ() / (float) 1.5 };
	Vector ballToGoal = (ORANGE_GOAL - ballPosition) * SHOT_FACTOR;
	float distance = ballToGoal.magnitude();

	Vector carPosition = ballPosition.clone();
	carPosition = carPosition + (ballToGoal * 0.3);
	carPosition.Z = CAR_HEIGHT;
	Vector carVelocity = ballToGoal.clone();
	carVelocity.Z = 0;

	// TODO: Rotation

	car.SetLocation(carPosition);
	car.SetVelocity(carVelocity);

	ball.SetLocation(ballPosition);
	ball.SetVelocity(ballToGoal);
	ball.SetAngularVelocity(GetRandomCarSpeed(), false);
}

void GoalieMode::CheckGameOver() {

}

void GoalieMode::RunGame(GameInformation gameInfo) {

}


void GoalieMode::EnableGame(GameInformation) {

}

void GoalieMode::OnDisable(GameInformation) {

}

void GoalieMode::OnBallHit(GameInformation gameInfo) {
	StartMode(gameInfo);
}

void GoalieMode::OnGoalScored(GameInformation gameInfo) {
	_globalCvarManager->log("Scored Goal!");
	StartMode(gameInfo);
}

void GoalieMode::OnBoostPickUp(GameInformation) {

}

void GoalieMode::RenderGame(CanvasWrapper canvas) {

}