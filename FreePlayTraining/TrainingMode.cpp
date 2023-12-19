#include "pch.h"
#include "TrainingMode.h"

TrainingMode::TrainingMode(double greenTime, double yellowTime, bool autoReduceTime, unsigned int maxBoost, float boostDecay, bool disableGoal) : GreenTime(greenTime), YellowTime(yellowTime), AutoReduceTime(autoReduceTime), MaxBoost((double) maxBoost / 100), BoostDecay(boostDecay), DisableGoal(disableGoal) {
	Reset();
}

void TrainingMode::ExecuteGameStall(GameInformation* gameInfo) {
	if (CurrentTrainingState != STALLED) { return; }

	// Apply ball and car states
	CarWrapper car = gameInfo->Car;
	BoostWrapper boost = car.GetBoostComponent();

	car.SetLocation(StallState->CarLocation);
	car.SetVelocity(StallState->CarVelocity);
	car.SetAngularVelocity(StallState->CarAngularVelocity, false);
	car.SetRotation(StallState->CarRotation);
	boost.SetCurrentBoostAmount(StallState->CarBoost);

	BallWrapper ball = gameInfo->Ball;
	ball.SetLocation(StallState->BallLocation);
	ball.SetVelocity(StallState->BallVelocity);
	ball.SetAngularVelocity(StallState->BallAngularVelocity, false);
	ball.SetRotation(StallState->BallRotation);
		
	StallTime -= gameInfo->DeltaTime;

	if (StallTime > 0) { return; }

	CurrentTrainingState = RUNNING;
}

void TrainingMode::ExecutePreGameTimer(GameInformation* gameInfo) {
	if (CurrentTrainingState != PRE_GAME) { return; }
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

	if (PreGameTimer <= 0) {
		CurrentTrainingState = RUNNING;
		_globalCvarManager->executeCommand(COMMAND_LIMITED_BOOST);
		EnableGame(gameInfo);
	}
}

void TrainingMode::ExecutePostGameTimer(GameInformation* gameInfo) {
	if (CurrentTrainingState != POST_GAME) { return; }
		PostGameTimer -= gameInfo->DeltaTime;
		if (PostGameTimer > 0) { return; }
		CurrentTrainingState = DONE;
		OnDisable(gameInfo);
}


void TrainingMode::ExecuteGameLoop(GameInformation* gameInfo) {
	if (CurrentTrainingState != RUNNING) { return; }
	RunGame(gameInfo);
}

void TrainingMode::ExecuteTimer(GameInformation* gameInfo) {
	if (CurrentTrainingState != RUNNING) { return; }

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

void TrainingMode::RenderPreGameTimer(CanvasWrapper canvas) {
	if (CurrentTrainingState != PRE_GAME) { return; }
	// Render Timer
	canvas.SetPosition(Vector2F{ (float) canvas.GetSize().X / 2 - (FONT_SIZE_MEDIUM / 2), (float) canvas.GetSize().Y / 2 });
	canvas.SetColor(COLOR_WHITE);

	int timeLeft = (int) PreGameTimer + 1;

	canvas.DrawString(std::to_string(timeLeft), FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}

void TrainingMode::RenderGameResult(CanvasWrapper canvas) {
	if (CurrentTrainingState != POST_GAME) { return; }
	std::string result;

	if (PossibleScore > 0) {
		result = "Result: " + GetScoreString((int) CurrentScore, (int) PossibleScore);
	} else if(CurrentTime > 0) {
		result = "Result: " + GetTimeString(CurrentTime);
	}

	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM),  (float)(canvas.GetSize().Y * 0.2) });
	canvas.SetColor(COLOR_WHITE);
	canvas.DrawString(result, FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);

}

void TrainingMode::LimitBoost(GameInformation* gameInfo) {
	if (CurrentTrainingState != RUNNING) { return; }
	BoostWrapper boost = gameInfo->Car.GetBoostComponent();
	if (boost.GetCurrentBoostAmount() > MaxBoost) {
		boost.SetCurrentBoostAmount(MaxBoost);
	}
}

void TrainingMode::DecayBoost(GameInformation* gameInfo) {
	if (CurrentTrainingState != RUNNING) { return; }
	CarWrapper car = gameInfo->Car;
	BoostWrapper boost = car.GetBoostComponent();

	double consumption = ((double) BoostDecay + (car.GetInput().HoldingBoost / 2) * DEFAULT_BOOST_DECAY) / 100 * gameInfo->DeltaTime;
	double targetBoost = boost.GetCurrentBoostAmount() - consumption;
	if (targetBoost < 0) { targetBoost = 0; }
	boost.SetCurrentBoostAmount(targetBoost);
}

void TrainingMode::DisableGoals(GameInformation* gameInfo) {
	if (!DisableGoal) { return; }
	BallWrapper ball = gameInfo->Ball;
	Vector ballLocation = ball.GetLocation();

	// Ensure Ball is on the goal line
	if (ballLocation.Y > -BACK_WALL && ballLocation.Y < BACK_WALL) {
		return;
	}

	// Ensure Ball is below crossbar
	if (ballLocation.Z > GOAL_HEIGHT - BALL_RADIUS) {
		return;
	}

	// Ensure ball is between both goal posts
	if (ballLocation.X < -GOAL_CENTER_TO_POST + BALL_RADIUS && ballLocation.X > GOAL_CENTER_TO_POST - BALL_RADIUS) {
		return;
	}

	// Ensure ball is moving towards the net
	Vector ballVelocity = ball.GetVelocity();
	if (Sign(ballVelocity.Y) != Sign(ballLocation.Y)) {
		return;
	}

	Vector ballAngularVelocity = ball.GetAngularVelocity();

	// Modify ball direction and apply restitution to create realistic bounce
	double magnitude = ballVelocity.magnitude();
	ballVelocity.Y *= -1;
	ballVelocity *= BALL_RESTITUTION_FACTOR;
	ballAngularVelocity.Y *= -1;
	ballAngularVelocity *= BALL_RESTITUTION_FACTOR;

	//Apply changes
	ball.SetVelocity(ballVelocity);
}

void TrainingMode::Reset() {
	CurrentScore = 0;
	PossibleScore = 0;
	TimeRemaining = 0;
	CurrentTime = 0;
}

void TrainingMode::EndGame() {
	TimeRemaining = 0;
	PostGameTimer = END_GAME_TIMER;
	CurrentTrainingState = POST_GAME;
}

void TrainingMode::StallGame(GameState* gameState, double time) {
	StallTime = time;
	if (StallState) { delete StallState; }
	StallState = gameState;
	CurrentTrainingState = STALLED;
}

void TrainingMode::AddScore(int score, int possibleScore) {
	CurrentScore += score;
	PossibleScore += possibleScore;
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

void TrainingMode::Run(GameInformation* gameInfo) {

	// Pre Game
	ExecutePreGameTimer(gameInfo);

	// Mid Game
	ExecuteGameStall(gameInfo);
	LimitBoost(gameInfo);
	DecayBoost(gameInfo);
	ExecuteTimer(gameInfo);
	ExecuteGameLoop(gameInfo);
	DisableGoals(gameInfo);

	// Post Game
	ExecutePostGameTimer(gameInfo);
}

void TrainingMode::OnEnable(GameInformation* gameInfo) {
	PreGameTimer = PRE_GAME_TIMER;
	CurrentTrainingState = PRE_GAME;
}

void TrainingMode::ReplayBegin(GameInformation* gameInfo) {
	CurrentTrainingState = REPLAY;
	OnReplayBegin(gameInfo);
}

void TrainingMode::ReplayEnd() {
	OnReplayEnd();
}

void TrainingMode::Render(CanvasWrapper canvas) {
	if (CurrentTrainingState == POST_GAME) { RenderGameEnd(canvas); }

	// PreGameTimer
	RenderPreGameTimer(canvas);
	RenderGameResult(canvas);

	// Score and Time
	RenderStats(canvas);
	RenderGame(canvas);
}

void TrainingMode::RenderStats(CanvasWrapper canvas) {
	if (CurrentTrainingState != RUNNING && CurrentTrainingState != STALLED) { return; }
	if (TimeRemaining > 0) { RenderTime(canvas, TimeRemaining, YellowTime, GreenTime); }
	if (PossibleScore > 0) { RenderScore(canvas, CurrentScore, PossibleScore); }
}

bool TrainingMode::IsState(TrainingState state) {
	return CurrentTrainingState == state;
}