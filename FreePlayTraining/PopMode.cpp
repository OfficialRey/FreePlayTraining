#include "pch.h"
#include "PopMode.h"

PopMode::PopMode() : TrainingMode(TIMER_GREEN, TIMER_YELLOW, false) {

}


void PopMode::DecayTime(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;
	if (ball.GetLocation().Z < MIN_BALL_HEIGHT) {
		TimeRemaining -= gameInfo->DeltaTime;
	}

	CurrentTime += gameInfo->DeltaTime;
}

void PopMode::CheckGameOver() {
	if (TimeRemaining > 0) { return; }
	IsGameOver = true;
}

void PopMode::RunGame(GameInformation* gameInfo) {
	DecayTime(gameInfo);
}

void PopMode::EnableGame(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;

	ball.SetLocation(START_POSITION);
	ball.SetVelocity(START_VELOCITY);
	ball.SetAngularVelocity(Vector{}, false);

	CarWrapper car = gameInfo->Car;

	car.GetBoostComponent().SetCurrentBoostAmount(FULL_BOOST);

	CurrentTime = 0;
	TimeRemaining = START_TIME;
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