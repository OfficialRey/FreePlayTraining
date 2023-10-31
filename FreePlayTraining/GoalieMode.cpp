#include "pch.h"

#include "GoalieMode.h"

void GoalieMode::CreateShot() {

	Vector ballLocation = Vector{ GetRandomFieldX() / 2, GetRandomFieldY() / 3, GetRandomFieldZ() / (float) 1.5 };
	Vector ballToGoal = (ORANGE_GOAL - ballLocation) * SHOT_FACTOR;
	float distance = ballToGoal.magnitude();

	Vector carLocation = ballLocation.clone();
	carLocation = carLocation + (ballToGoal * 0.3f);
	carLocation.Z = CAR_GROUND;
	carLocation.X *= 1.2f;
	Vector carVelocity = ballToGoal.clone();
	carVelocity.Z = 0;

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
	if (!IsBallSaved(gameInfo)) { return; }

	AddScore(1, 1);
	CreateShot();
}

bool GoalieMode::IsBallSaved(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;
	Vector ballToGoalDirection = ORANGE_GOAL - ball.GetLocation();
	Vector ballDirection = ball.GetVelocity();

	double angle = CalculateVectorAngle(ballToGoalDirection, ballDirection);

	// _globalCvarManager->log(std::to_string(angle));
	return angle > MIN_SAVE_ANGLE;
}

void GoalieMode::RunGame(GameInformation* gameInfo) {
	CheckSave(gameInfo);
}


void GoalieMode::EnableGame(GameInformation* gameInfo) {
	CreateShot();
}

void GoalieMode::OnDisable(GameInformation*) {

}

void GoalieMode::OnBallHit(GameInformation* gameInfo) {
}

void GoalieMode::OnGoalScored(GameInformation* gameInfo) {
	SkipGoalReplay();
	AddScore(0, 1);
}

void GoalieMode::OnReplayBegin(GameInformation*) {

}

void GoalieMode::OnReplayEnd() {
	CreateShot();
}

void GoalieMode::OnTimeRunOut(GameInformation*) {

}

void GoalieMode::OnBoostPickUp(GameInformation*) {

}

void GoalieMode::RenderGame(CanvasWrapper) {

}

void GoalieMode::RenderGameEnd(CanvasWrapper) {

}