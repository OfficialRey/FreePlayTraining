#include "pch.h"
#include "Utility.h"
#include "PathingMode.h"

void PathingMode::StartMode(GameInformation* gameInfo) {
	CarWrapper car = gameInfo->Car;
	BallWrapper ball = gameInfo->Ball;

	TimeLeft = STARTING_TIME;
	CurrentTime = 0;
}

void PathingMode::DecayBoost(GameInformation* gameInfo) {
	CarWrapper car = gameInfo->Car;
	BoostWrapper boost = car.GetBoostComponent();

	double consumption = ((double) CUSTOM_BOOST_DECAY_PER_SECOND + car.GetInput().HoldingBoost * BOOST_DECAY_PER_SECOND) / 100 * gameInfo->DeltaTime;
	double targetBoost = boost.GetCurrentBoostAmount() - consumption;
	if (targetBoost < 0) { targetBoost = 0; }
	boost.SetCurrentBoostAmount(targetBoost);
}

void PathingMode::SetBallPosition(GameInformation* gameInfo) {
	BallPosition = Vector{ GetRandomFieldX(), GetRandomFieldY(), GetRandomFieldZ() / (float) 1.5};
}

void PathingMode::LimitBoost(GameInformation* gameInfo) {
	BoostWrapper boost = gameInfo->Car.GetBoostComponent();
	if (boost.GetCurrentBoostAmount() > MAX_BOOST) {
		boost.SetCurrentBoostAmount(MAX_BOOST);
	}
}

void PathingMode::CheckGameOver() {
	if (TimeLeft > 0) { return; }
	IsGameOver = true;
}

void PathingMode::RunGame(GameInformation* gameInfo) {
	// Remove ball from field
	BallWrapper ball = gameInfo->Ball;
	ball.SetLocation(BallPosition);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

	// Tick clock
	TimeLeft -= gameInfo->DeltaTime;
	CurrentTime += gameInfo->DeltaTime;

	// Decay boost
	DecayBoost(gameInfo);

	// Limit boost
	LimitBoost(gameInfo);
}

void PathingMode::EnableGame(GameInformation* gameInfo) {
	gameInfo->Car.GetBoostComponent().SetCurrentBoostAmount(MAX_BOOST);
}

void PathingMode::OnDisable(GameInformation*) {
	
}

void PathingMode::OnBallHit(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;
	double increase = (ball.GetLocation().Z / MAX_SPEED);
	TimeLeft += BALL_TOUCH_TIME_INCREASE + increase;
	CarWrapper car = gameInfo->Car;
	Vector velocity = car.GetVelocity();
	velocity.Z -= RECOVERY_BONUS;
	car.SetVelocity(velocity);
	BoostWrapper boost = car.GetBoostComponent();
	boost.SetBoostAmount(boost.GetCurrentBoostAmount() + gameInfo->Ball.GetLocation().Z / BALL_HEIGHT_BOOST_GAIN_FACTOR);
	SetBallPosition(gameInfo);
}

void PathingMode::OnBoostPickUp(GameInformation* gameInfo) {
	TimeLeft += BOOST_PICKUP_TIME_INCREASE;
}

void PathingMode::OnGoalScored(GameInformation*) {

}

void PathingMode::OnReplayBegin(GameInformation*) {

}

void PathingMode::OnReplayEnd(GameInformation*) {

}

void PathingMode::RenderGame(CanvasWrapper canvas) {
	std::string result = GetTimeString(TimeLeft);
	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM), (float) (canvas.GetSize().Y * 0.2)});
	canvas.SetColor(GetColorBasedOnTime(TimeLeft, TIMER_YELLOW, TIMER_GREEN));
	canvas.DrawString(GetTimeString(TimeLeft), FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}

void PathingMode::RenderGameEnd(CanvasWrapper canvas) {
	std::string result = "Result: " + GetTimeString(CurrentTime);
	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM),  (float)(canvas.GetSize().Y * 0.2) });
	canvas.SetColor(COLOR_WHITE);
	canvas.DrawString(result, FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}