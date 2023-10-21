#include "pch.h"
#include "TrainingMode.h"

TrainingMode::TrainingMode() {

}

TrainingMode::TrainingMode(double greenTime, double yellowTime, bool autoReduceTime) : GreenTime(greenTime), YellowTime(yellowTime), AutoReduceTime(autoReduceTime) {
	Reset();
}

void TrainingMode::ExecuteGameStall(GameInformation* gameInfo) {
	if (!IsStalled()) { return; }

	// Apply ball and car states

	CarWrapper oldCar = gameInfo->Car;
	CarWrapper newCar = StallState->Car;

	BoostWrapper oldBoost = oldCar.GetBoostComponent();
	BoostWrapper newBoost = newCar.GetBoostComponent();

	oldCar.SetVelocity(newCar.GetVelocity());
	oldCar.SetLocation(newCar.GetLocation());
	oldCar.SetAngularVelocity(newCar.GetAngularVelocity(), false);
	oldCar.SetRotation(newCar.GetRotation());
	oldBoost.SetCurrentBoostAmount(newBoost.GetCurrentBoostAmount());

	BallWrapper oldBall = gameInfo->Ball;
	BallWrapper newBall = StallState->Ball;

	oldBall.SetVelocity(newBall.GetVelocity());
	oldBall.SetLocation(newBall.GetLocation());
	oldBall.SetAngularVelocity(newBall.GetAngularVelocity(), false);
	oldBall.SetRotation(newBall.GetRotation());
		
	StallTime -= gameInfo->DeltaTime;
}

void TrainingMode::ExecutePreGameTimer(GameInformation* gameInfo) {
	if (PreGameTimer <= 0) { return; }
	CarWrapper car = gameInfo->Car;
	BallWrapper ball = gameInfo->Ball;

	car.SetLocation(STARTING_LOCATION);
	car.SetVelocity(Vector{});
	car.SetRotation(DEFAULT_ROTATION);
	car.SetAngularVelocity(Vector{}, false);
	car.GetBoostComponent().SetCurrentBoostAmount(FULL_BOOST);

	ball.SetLocation(Vector{ 0, 0, BALL_RADIUS * 2 });
	ball.SetVelocity(Vector{});
	ball.SetRotation(Rotator{});
	ball.SetAngularVelocity(Vector{}, false);

	PreGameTimer -= gameInfo->DeltaTime;
}

void TrainingMode::ExecutePostGameTimer(GameInformation* gameInfo) {
	if (!IsGameOver || IsStalled()) { return; }
		EndGameTimer -= gameInfo->DeltaTime;
}


void TrainingMode::ExecuteGameLoop(GameInformation* gameInfo) {
	if (!IsActive() || IsStalled()) { return; }
	RunGame(gameInfo);
}

void TrainingMode::ExecuteTimer(GameInformation* gameInfo) {
	if (!IsActive() || IsStalled()) { return; }

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
		_globalCvarManager->executeCommand(COMMAND_LIMITED_BOOST);
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

void TrainingMode::StallGame(GameInformation* gameInfo, double time) {
	StallTime = time;
	StallState = gameInfo;
}

void TrainingMode::SetBoostLimitation(bool value) {
	if (value) {
		_globalCvarManager->executeCommand(COMMAND_LIMITED_BOOST);
	}
	else {
		_globalCvarManager->executeCommand(COMMAND_UNLIMITED_BOOST);
	}
}

void TrainingMode::SkipGoalReplay() {

}

bool TrainingMode::IsStalled() {
	return StallTime > 0;
}

bool TrainingMode::IsActive() {
	return (Running || !IsGameOver);
}

void TrainingMode::Run(GameInformation* gameInfo) {
	// Pre Game
	OnGameEnable(gameInfo);
	ExecutePreGameTimer(gameInfo);

	// Mid Game
	ExecuteGameStall(gameInfo);
	ExecuteTimer(gameInfo);
	ExecuteGameLoop(gameInfo);

	// Post Game
	ExecutePostGameTimer(gameInfo);
}

void TrainingMode::OnEnable(GameInformation* gameInfo) {
	PreGameTimer = PRE_GAME_TIMER;
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