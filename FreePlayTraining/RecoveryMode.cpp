#include "pch.h"
#include "Utility.h"
#include "RecoveryMode.h"

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

	RecoveryTime = BASE_RECOVERY_TIME + (distance / MAX_SPEED) + (RecoveryPosition.Z / MAX_SPEED) - (1.5 * angle * distance / MAX_SPEED);
}

void RecoveryMode::TickClock(GameInformation* gameInfo) {
	RecoveryTime -= gameInfo->DeltaTime;

	if (RecoveryTime > 0) { return; }

	LoseRound(gameInfo);
}

void RecoveryMode::LoseRound(GameInformation* gameInfo) {
	RecoveriesGeneral += 1;
	SetTargetPosition(gameInfo);
}

void RecoveryMode::WinRound(GameInformation* gameInfo) {
	RecoveriesSucceeded += 1;
	RecoveriesGeneral += 1;
	SetTargetPosition(gameInfo);
}

void RecoveryMode::CheckGameOver() {

}

void RecoveryMode::RunGame(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;
	ball.SetLocation(RecoveryTarget);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

	TickClock(gameInfo);

}

void RecoveryMode::EnableGame(GameInformation*) {

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

void RecoveryMode::RenderGame(CanvasWrapper canvas) {
	std::string result = GetTimeString(RecoveryTime);

	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM), (float)(canvas.GetSize().Y * 0.2) });
	canvas.SetColor(GetColorBasedOnTime(RecoveryTime, TIMER_YELLOW, TIMER_GREEN));
	canvas.DrawString(GetTimeString(RecoveryTime), FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);


	int percentage = (RecoveriesSucceeded / RecoveriesGeneral) * 100.0;

	result = "Score: " + std::to_string((int) RecoveriesSucceeded) + " / " + std::to_string((int) RecoveriesGeneral) + " (" + std::to_string(percentage) + "%)";
	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_SMALL), (float)(canvas.GetSize().Y * 0.05) });
	canvas.SetColor(COLOR_WHITE);
	canvas.DrawString(result, FONT_SIZE_SMALL, FONT_SIZE_SMALL, true);
}

void RecoveryMode::RenderGameEnd(CanvasWrapper canvas) {

}