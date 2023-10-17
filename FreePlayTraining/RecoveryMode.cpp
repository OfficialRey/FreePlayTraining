#include "pch.h"
#include "Utility.h"
#include "RecoveryMode.h"

void RecoveryMode::SetTargetPosition(GameInformation gameInfo) {
	CarWrapper car = gameInfo.Car;
	BallWrapper ball = gameInfo.Ball;
	Vector position = {};
	Vector target = {};
	float distance = 0;

	while (distance < MIN_RECOVERY_DISTANCE) {
		// Recovery positions

		position = Vector{ GetRandomFieldX(),GetRandomFieldY(),GetRandomFieldZ() };
		target = Vector{ GetRandomFieldX(), GetRandomFieldY(), GetRandomFieldZ() };
		distance = (target.clone() - position.clone()).magnitude();
	}

	RecoveryPosition = position;
	RecoveryTarget = target;

	float boost = (float)((distance + position.Z / (float) 2) / MIN_RECOVERY_DISTANCE * BOOST_MULTIPLIER);

	Vector velocity = GetRandomCarSpeed();
	velocity.Z = (float)(QUARTER_SPEED + (rand() % QUARTER_SPEED));

	Rotator rotation = GetRandomRotation();

	car.SetLocation(RecoveryPosition);
	car.SetRotation(rotation);
	car.SetVelocity(velocity);
	_globalCvarManager->executeCommand("boost set limited");
	car.GetBoostComponent().SetCurrentBoostAmount(boost);

	ball.SetLocation(RecoveryTarget);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);
}

void RecoveryMode::CheckGameOver() {

}

void RecoveryMode::RunGame(GameInformation gameInfo) {
	BallWrapper ball = gameInfo.Ball;
	ball.SetLocation(RecoveryTarget);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

}

void RecoveryMode::EnableGame(GameInformation) {

}

void RecoveryMode::OnDisable(GameInformation) {

}

void RecoveryMode::OnBallHit(GameInformation gameInfo) {
	SetTargetPosition(gameInfo);
}


void RecoveryMode::OnBoostPickUp(GameInformation) {

}

void RecoveryMode::RenderGame(CanvasWrapper) {

}