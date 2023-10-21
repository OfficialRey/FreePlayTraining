#include "pch.h"

#include "GoalieMode.h"

void GoalieMode::StartMode(GameInformation* gameInfo) {
	CarWrapper car = gameInfo->Car;
	BallWrapper ball = gameInfo->Ball;

	Vector ballPosition = Vector{ GetRandomFieldX() / 2, GetRandomFieldY() / 3, GetRandomFieldZ() / (float) 1.5 };
	Vector ballToGoal = (ORANGE_GOAL - ballPosition) * SHOT_FACTOR;
	float distance = ballToGoal.magnitude();

	Vector carPosition = ballPosition.clone();
	carPosition = carPosition + (ballToGoal * 0.3f);
	carPosition.Z = CAR_HEIGHT;
	carPosition.X *= 1.2f;
	Vector carVelocity = ballToGoal.clone();
	carVelocity.Z = 0;

	// TODO: Rotation

	car.SetLocation(carPosition);
	car.SetVelocity(carVelocity);
	car.SetAngularVelocity(Vector{}, false);
	car.SetRotation(VectorToRotator(carVelocity));

	ball.SetLocation(ballPosition);
	ball.SetVelocity(ballToGoal);
	ball.SetAngularVelocity(GetRandomCarSpeed(), false);

	StallGame(gameInfo, STALL_TIME);
	_globalCvarManager->log("Created shot!");
}

void GoalieMode::RunGame(GameInformation*) {

}


void GoalieMode::EnableGame(GameInformation* gameInfo) {
	StartMode(gameInfo);
}

void GoalieMode::OnDisable(GameInformation*) {

}

void GoalieMode::OnBallHit(GameInformation* gameInfo) {
	StartMode(gameInfo);
}

void GoalieMode::OnGoalScored(GameInformation* gameInfo) {
	SkipGoalReplay();
}

void GoalieMode::OnReplayBegin(GameInformation*) {

}

void GoalieMode::OnReplayEnd(GameInformation* gameInfo) {
	StartMode(gameInfo);
}

void GoalieMode::OnTimeRunOut(GameInformation*) {

}

void GoalieMode::OnBoostPickUp(GameInformation*) {

}

void GoalieMode::RenderGame(CanvasWrapper) {

}

void GoalieMode::RenderGameEnd(CanvasWrapper) {

}