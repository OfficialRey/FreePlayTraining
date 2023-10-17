#include "pch.h"
#include "Utility.h"
#include "PathingMode.h"

void PathingMode::StartMode(GameInformation gameInfo) {
	CarWrapper car = gameInfo.Car;
	BallWrapper ball = gameInfo.Ball;

	TimeLeft = STARTING_TIME;
	CurrentTime = 0;
}

void PathingMode::DecayBoost(GameInformation gameInfo) {
	CarWrapper car = gameInfo.Car;
	BoostWrapper boost = car.GetBoostComponent();

	double consumption = ((double)CUSTOM_BOOST_DECAY_PER_SECOND + car.GetInput().HoldingBoost * BOOST_DECAY_PER_SECOND) / 100 * gameInfo.DeltaTime;
	double targetBoost = boost.GetCurrentBoostAmount() - consumption;
	if (targetBoost < 0) { targetBoost = 0; }
	boost.SetCurrentBoostAmount(targetBoost);
}

void PathingMode::SetBallPosition(GameInformation gameInfo) {
	BallPosition = Vector{ GetRandomFieldX(), GetRandomFieldY(), GetRandomFieldZ() / (float) 1.5};
}

void PathingMode::CheckGameOver() {
	if (TimeLeft > 0) { return; }
	IsGameOver = true;
}

void PathingMode::RunGame(GameInformation gameInfo) {
	// Remove ball from field
	BallWrapper ball = gameInfo.Ball;
	ball.SetLocation(BallPosition);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

	// Tick clock
	TimeLeft -= gameInfo.DeltaTime;
	CurrentTime += gameInfo.DeltaTime;

	// Decay boost
	DecayBoost(gameInfo);
}

void PathingMode::EnableGame(GameInformation) {

}

void PathingMode::OnDisable(GameInformation) {
	
}

void PathingMode::OnBallHit(GameInformation gameInfo) {
	TimeLeft += BALL_TOUCH_TIME_INCREASE;
	CarWrapper car = gameInfo.Car;
	Vector velocity = car.GetVelocity();
	velocity.Z -= RECOVERY_BONUS;
	car.SetVelocity(velocity);
	BoostWrapper boost = car.GetBoostComponent();
	boost.SetBoostAmount(boost.GetCurrentBoostAmount() + gameInfo.Ball.GetLocation().Z / BALL_HEIGHT_BOOST_GAIN_FACTOR);
	SetBallPosition(gameInfo);
}

void PathingMode::OnBoostPickUp(GameInformation) {
	TimeLeft += BOOST_PICKUP_TIME_INCREASE;
}

void PathingMode::RenderGame(CanvasWrapper canvas) {
	float fractional, whole;

	fractional = std::modf(TimeLeft, &whole);

	std::string seconds = std::to_string(int(whole));
	std::string milliseconds = std::to_string(int(fractional * 100));
	std::string result = seconds + ":" + milliseconds;

	canvas.SetPosition(Vector2F{ 0, 0 });
	canvas.SetColor(Color);

	canvas.DrawString(result, FONT_SIZE_SMALL, FONT_SIZE_SMALL, true);
}