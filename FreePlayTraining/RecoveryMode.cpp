#include "pch.h"
#include "Utility.h"
#include "RecoveryMode.h"

RecoveryMode::RecoveryMode() : TrainingMode(TIMER_GREEN, TIMER_YELLOW, true) {

}

void RecoveryMode::SetTargetPosition(GameInformation* gameInfo) {
	CarWrapper car = gameInfo->Car;
	BallWrapper ball = gameInfo->Ball;
	Vector position = {};
	Vector target = {};
	float distance = 0;

	while (distance < MIN_RECOVERY_DISTANCE) {
		// Calculate recovery positions
		position = Vector{ GetRandomFieldX(),GetRandomFieldY(),GetRandomFieldZ() };
		target = Vector{ GetRandomFieldX(), GetRandomFieldY(), GetRandomFieldZ() };
		distance = (target.clone() - position.clone()).magnitude();
	}

	// Update class parameters
	RecoveryPosition = position;
	RecoveryTarget = target;

	// Calculate car values
	float boost = (float) ((distance + position.Z / (float) 2) / MIN_RECOVERY_DISTANCE * BOOST_MULTIPLIER);

	Vector velocity = GetRandomCarSpeed();
	velocity.Z = (float)(QUARTER_SPEED + (rand() % QUARTER_SPEED));

	Rotator rotation = GetRandomRotation();

	// Set car values
	car.SetLocation(RecoveryPosition);
	car.SetRotation(rotation);
	car.SetVelocity(velocity);
	_globalCvarManager->executeCommand("boost set limited");
	car.GetBoostComponent().SetCurrentBoostAmount(boost);


	// Set ball values
	ball.SetLocation(RecoveryTarget);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

	// Set Timer
	Vector playerToBall = (RecoveryTarget - RecoveryPosition).getNormalized();
	Vector playerDirection = velocity.getNormalized();
	float angle = Vector::dot(playerToBall, playerDirection);

	TimeRemaining = BASE_RECOVERY_TIME + ((distance + RecoveryPosition.Z + RecoveryTarget.Z+ velocity.magnitude()) - (1.5 * angle * distance)) / MAX_SPEED;
}

void RecoveryMode::LoseRound(GameInformation* gameInfo) {
	PossibleScore += 1;
	SetTargetPosition(gameInfo);
}

void RecoveryMode::WinRound(GameInformation* gameInfo) {
	CurrentScore += 1;
	PossibleScore += 1;
	SetTargetPosition(gameInfo);
}

void RecoveryMode::CheckGameOver() {

}

void RecoveryMode::RunGame(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;
	ball.SetLocation(RecoveryTarget);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);
}

void RecoveryMode::EnableGame(GameInformation*) {
	TimeRemaining = BASE_RECOVERY_TIME;
}

void RecoveryMode::OnDisable(GameInformation*) {

}

void RecoveryMode::OnBallHit(GameInformation* gameInfo) {
	WinRound(gameInfo);
}


void RecoveryMode::OnBoostPickUp(GameInformation*) {

}

void RecoveryMode::OnGoalScored(GameInformation*) {

}

void RecoveryMode::OnReplayBegin(GameInformation*) {

}

void RecoveryMode::OnReplayEnd(GameInformation*) {

}

void RecoveryMode::OnTimeRunOut(GameInformation* gameInfo) {
	LoseRound(gameInfo);
}

void RecoveryMode::RenderGame(CanvasWrapper canvas) {

}

void RecoveryMode::RenderGameEnd(CanvasWrapper canvas) {

}