#include "pch.h"
#include "PopMode.h"

PopMode::PopMode() : PopBaseTime(_globalCvarManager->getCvar(POP_BASE_TIME_TITLE).getFloatValue()),
	PopMinBallHeight(_globalCvarManager->getCvar(POP_BALL_HEIGHT_TITLE).getIntValue()),
	PopGravity(_globalCvarManager->getCvar(POP_GRAVITY_TITLE).getFloatValue()),
	TrainingMode(
		POP_TIMER_GREEN,
		POP_TIMER_YELLOW,
		false,
		_globalCvarManager->getCvar(POP_BOOST_MAX_TITLE).getIntValue(),
		_globalCvarManager->getCvar(POP_BOOST_DECAY_TITLE).getIntValue()
	) {

}

void PopMode::EnhanceGravity(GameInformation* gameInfo) {
	if (PopGravity == POP_DEFAULT_GRAVITY) { return; }
	BallWrapper ball = gameInfo->Ball;
	Vector velocity = ball.GetVelocity();
	velocity.Z -= (DEFAULT_GRAVITY * (PopGravity - POP_DEFAULT_GRAVITY)) * gameInfo->DeltaTime;
	ball.SetVelocity(velocity);
}

void PopMode::DecayTime(GameInformation* gameInfo) {
	CurrentTime += gameInfo->DeltaTime;
	BallWrapper ball = gameInfo->Ball;
	if (ball.GetLocation().Z > PopMinBallHeight) { return; }
	TimeRemaining -= gameInfo->DeltaTime;
}

void PopMode::CheckGameOver() {
	if (TimeRemaining > 0) { return; }
	IsGameOver = true;
}

void PopMode::RunGame(GameInformation* gameInfo) {
	DecayTime(gameInfo);
	EnhanceGravity(gameInfo);
}

void PopMode::EnableGame(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;

	ball.SetLocation(START_POSITION);
	ball.SetVelocity(START_VELOCITY);
	ball.SetAngularVelocity(Vector{}, false);

	CarWrapper car = gameInfo->Car;

	car.GetBoostComponent().SetCurrentBoostAmount(FULL_BOOST);

	CurrentTime = 0;
	TimeRemaining = PopBaseTime;
}

void PopMode::OnDisable(GameInformation*) {

}

 void PopMode::OnBallHit(GameInformation*) {

}
 void PopMode::OnBoostPickUp(GameInformation*) {

}
 void PopMode::OnGoalScored(GameInformation*) {

}
 void PopMode::OnReplayBegin(GameInformation*) {

}
 void PopMode::OnReplayEnd(GameInformation*) {

}

 void PopMode::OnTimeRunOut(GameInformation*) {
	 IsGameOver = true;
 }

 void PopMode::RenderGame(CanvasWrapper canvas) {

}
 void PopMode::RenderGameEnd(CanvasWrapper canvas) {
	 std::string result = "Result: " + GetTimeString(CurrentTime);
	 canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM),  (float)(canvas.GetSize().Y * 0.2) });
	 canvas.SetColor(COLOR_WHITE);
	 canvas.DrawString(result, FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}