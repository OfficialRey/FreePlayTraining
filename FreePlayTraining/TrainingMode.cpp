#include "pch.h"
#include "TrainingMode.h"

void TrainingMode::ExecuteTimer(GameInformation gameInfo) {
	CarWrapper car = gameInfo.Car;
	BallWrapper ball = gameInfo.Ball;

	car.SetLocation(STARTING_LOCATION);
	car.SetVelocity(Vector{});
	car.SetAngularVelocity(Vector{}, false);

	ball.SetLocation(Vector{ 0, 0, 100 });
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

	TimeRemaining -= gameInfo.DeltaTime;
}

void TrainingMode::RenderTimer(CanvasWrapper canvas) {
	// Render Timer
	canvas.SetPosition(Vector2F{ (float) canvas.GetSize().X / 2, (float) canvas.GetSize().Y / 2 });
	canvas.SetColor(COLOR_WHITE);

	int timeLeft = (int) TimeRemaining + 1;

	canvas.DrawString(std::to_string(timeLeft), 5.0, 5.0, true);
}

void TrainingMode::Run(GameInformation gameInfo) {
	if (TimeRemaining > 0) {
		ExecuteTimer(gameInfo);
		return;
	}
	RunGame(gameInfo);
}

void TrainingMode::OnEnable(GameInformation gameInfo) {
	TimeRemaining = STARTING_TIME;
}

void TrainingMode::Render(CanvasWrapper canvas) {
	if (TimeRemaining > 0) {
		RenderTimer(canvas);
		return;
	}
	RenderGame(canvas);
}