#include "pch.h"
#include "TrainingMode.h"

void TrainingMode::ExecuteTimer(GameInformation* gameInfo) {
	CarWrapper car = gameInfo->Car;
	BallWrapper ball = gameInfo->Ball;

	car.SetLocation(STARTING_LOCATION);
	car.SetVelocity(Vector{});
	car.SetRotation(DEFAULT_ROTATION);
	car.SetAngularVelocity(Vector{}, false);

	ball.SetLocation(Vector{ 0, 0, CAR_HEIGHT });
	ball.SetVelocity(Vector{});
	ball.SetRotation(Rotator{});
	ball.SetAngularVelocity(Vector{}, false);

	TimeRemaining -= gameInfo->DeltaTime;
}

void TrainingMode::RenderTimer(CanvasWrapper canvas) {
	// Render Timer
	canvas.SetPosition(Vector2F{ (float) canvas.GetSize().X / 2 - (FONT_SIZE_MEDIUM / 2), (float) canvas.GetSize().Y / 2 });
	canvas.SetColor(COLOR_WHITE);

	int timeLeft = (int) TimeRemaining + 1;

	canvas.DrawString(std::to_string(timeLeft), FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}

void TrainingMode::Run(GameInformation* gameInfo) {
	if (IsGameOver) {
		EndTime -= gameInfo->DeltaTime;
		return; 
	}
	if (TimeRemaining > 0) {
		ExecuteTimer(gameInfo);
		return;
	}
	if (!Running) {
		Running = true;
		EnableGame(gameInfo);
	}
	CheckGameOver();
	RunGame(gameInfo);
}

void TrainingMode::OnEnable(GameInformation* gameInfo) {
	TimeRemaining = STARTING_TIME;
	EndTime = END_TIME;
	IsGameOver = false;
}

void TrainingMode::Render(CanvasWrapper canvas) {
	if (IsGameOver) {
		if (EndTime > 0) {
			RenderGameEnd(canvas);
		}
		return;
	}
	if (TimeRemaining > 0) {
		RenderTimer(canvas);
		return;
	}
	RenderGame(canvas);
}