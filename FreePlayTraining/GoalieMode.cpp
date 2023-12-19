#include "pch.h"

#include "GoalieMode.h"

GoalieMode::GoalieMode() : 
	GoalieBallSpeedFactor(_globalCvarManager->getCvar(GOALIE_BALL_SPEED_TITLE).getFloatValue()),
	GoalieBallPlacementFactor(_globalCvarManager->getCvar(GOALIE_BALL_PLACEMENT_TITLE).getFloatValue()),
	TrainingMode(
		0,
		0,
		false,
		_globalCvarManager->getCvar(GOALIE_BOOST_MAX_TITLE).getIntValue(),
		0,
		false
	) {
}

void GoalieMode::CreateShot() {

	BallHitTimer = 0;

	// Calculate Ball Direction
	Vector ballLocation = Vector{ GetRandomFieldX() * 0.8f, GetRandomFieldY() / 3.0f, GetRandomFieldZ() / 1.5f };
	Vector ballToGoal = ORANGE_GOAL - ballLocation;
	float distance = ballToGoal.magnitude();

	// Adjust Ball Velocity to create difficult shot
	Vector ballVelocity = ballToGoal.getNormalized() * SHOT_MIN_SPEED;
	ballVelocity.Z = (CEILING - ballLocation.Z) * distance / (float) BACK_WALL * SHOT_HEIGHT_DISTANCE_FACTOR;
	ballVelocity.Z *= (SHOT_HEIGHT_ADJUSTMENT - SHOT_HEIGHT_ADJUSTMENT * ballLocation.Z / CEILING) * SHOT_HEIGHT_LOCATION_FACTOR; // Ball consistently overshoots when placed very high up

	// Add some x to hit corners
	ballVelocity.X += SHOT_OFFSET - rand() % SHOT_OFFSET * 2;

	Vector carLocation = ballLocation.clone();
	carLocation = carLocation + (ballToGoal * 0.3f);
	carLocation.Z = OCTANE_ELEVATION;
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
		ballVelocity,
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

	if (angle < MIN_SAVE_ANGLE) {
		BallHitTimer = 0;
		return false;
	}

	BallHitTimer += gameInfo->DeltaTime;

	return BallHitTimer > MIN_SHOT_SAVE_TIME;
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