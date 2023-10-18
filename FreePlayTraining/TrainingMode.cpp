#include "pch.h"
#include "TrainingMode.h"

TrainingMode::TrainingMode() {

}

TrainingMode::TrainingMode(double greenTime, double yellowTime, bool autoReduceTime) : GreenTime(greenTime), YellowTime(yellowTime), AutoReduceTime(autoReduceTime) {
	
}

void TrainingMode::ExecutePreGameTimer(GameInformation* gameInfo) {
	if (PreGameTimer <= 0) { return; }
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

	PreGameTimer -= gameInfo->DeltaTime;
}

void TrainingMode::ExecutePostGameTimer(GameInformation* gameInfo) {
	if (!IsGameOver) { return; }
		EndGameTimer -= gameInfo->DeltaTime;
}


void TrainingMode::ExecuteGameLoop(GameInformation* gameInfo) {
	if (!IsActive()) { return; }
	RunGame(gameInfo);
}

void TrainingMode::ExecuteTimer(GameInformation* gameInfo) {
	if (!IsActive()) { return; }

	CurrentTime += gameInfo->DeltaTime;

	if (!AutoReduceTime) { return; }

	if (TimeRemaining > 0 && AutoReduceTime) {
		TimeRemaining -= gameInfo->DeltaTime;
		if (TimeRemaining < 0) {
			TimeRemaining = 0;
			OnTimeRunOut(gameInfo);
		}
	}
}

void TrainingMode::OnGameEnable(GameInformation* gameInfo) {
	if (!Running) {
		Running = true;
		EnableGame(gameInfo);
	}
}

void TrainingMode::RenderPreGameTimer(CanvasWrapper canvas) {
	// Render Timer
	canvas.SetPosition(Vector2F{ (float) canvas.GetSize().X / 2 - (FONT_SIZE_MEDIUM / 2), (float) canvas.GetSize().Y / 2 });
	canvas.SetColor(COLOR_WHITE);

	int timeLeft = (int) PreGameTimer + 1;

	canvas.DrawString(std::to_string(timeLeft), FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}

void TrainingMode::Reset() {
	CurrentScore = 0;
	PossibleScore = 0;
	TimeRemaining = 0;
	CurrentTime = 0;
}

void TrainingMode::EndGame() {
	TimeRemaining = 0;
	EndGameTimer = END_TIME;
}

bool TrainingMode::IsActive() {
	return Running || !IsGameOver;
}

void TrainingMode::Run(GameInformation* gameInfo) {
	// Pre Game
	OnGameEnable(gameInfo);
	ExecutePreGameTimer(gameInfo);

	// Mid Game
	ExecuteTimer(gameInfo);
	ExecuteGameLoop(gameInfo);

	// Post Game
	ExecutePostGameTimer(gameInfo);
}

void TrainingMode::OnEnable(GameInformation* gameInfo) {
	PreGameTimer = STARTING_TIME;
	IsGameOver = false;
}

void TrainingMode::Render(CanvasWrapper canvas) {
	if (IsGameOver) {
		if (EndGameTimer > 0) {
			RenderGameEnd(canvas);
		} else {
			Running = false;
		}
		return;
	}

	// PreGameTimer
	if (PreGameTimer > 0) {
		RenderPreGameTimer(canvas);
		return;
	}

	// Score and Time
	if (TimeRemaining > 0) { RenderTime(canvas, TimeRemaining, YellowTime, GreenTime); }
	if (PossibleScore > 0) { RenderScore(canvas, CurrentScore, PossibleScore); }

	RenderGame(canvas);
}