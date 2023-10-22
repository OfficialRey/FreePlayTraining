#include "pch.h"

#include "GoalieMode.h"

void GoalieMode::StartMode(GameInformation* gameInfo) {
	CarWrapper car = gameInfo->Car;
	BallWrapper ball = gameInfo->Ball;

	Vector ballLocation = Vector{ GetRandomFieldX() / 2, GetRandomFieldY() / 3, GetRandomFieldZ() / (float) 1.5 };
	Vector ballToGoal = (ORANGE_GOAL - ballLocation) * SHOT_FACTOR;
	float distance = ballToGoal.magnitude();

	Vector carLocation = ballLocation.clone();
	carLocation = carLocation + (ballToGoal * 0.3f);
	carLocation.Z = CAR_GROUND;
	carLocation.X *= 1.2f;
	Vector carVelocity = ballToGoal.clone();
	carVelocity.Z = 0;

	car.SetLocation(carLocation);
	car.SetVelocity(carVelocity);
	car.SetAngularVelocity(Vector{}, false);
	car.SetRotation(VectorToRotator(carVelocity));

	ball.SetLocation(ballLocation);
	ball.SetVelocity(ballToGoal);
	ball.SetAngularVelocity(GetRandomCarSpeed(), false);

	GameState* gameState = new GameState{
		// Car
		carLocation,
		carVelocity,
		Vector{},
		VectorToRotator(carVelocity),
		100.0f,
		// Ball
		ballLocation,
		ballToGoal,
		GetRandomCarSpeed(),
		Rotator{}
	};

	StallGame(gameState, STALL_TIME);
}

void GoalieMode::CheckSave(GameInformation* gameInfo) {

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