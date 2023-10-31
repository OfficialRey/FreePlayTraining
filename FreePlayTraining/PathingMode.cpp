#include "pch.h"
#include "Utility.h"
#include "PathingMode.h"

PathingMode::PathingMode() : PathingBaseTime(_globalCvarManager->getCvar(PATHING_BASE_TIME_TITLE).getFloatValue()),
	PathingBoostCollectionTime(_globalCvarManager->getCvar(PATHING_BOOST_COLLECTION_TITLE).getFloatValue()),
	PathingBallTouchTime(_globalCvarManager->getCvar(PATHING_BALL_TOUCH_TITLE).getFloatValue()),
	PathingBallHeightBoostBonus((double) _globalCvarManager->getCvar(PATHING_BALL_BONUS_TITLE).getIntValue() * BALL_HEIGHT_NORMALIZER),
	PathingRecoveryBonus(_globalCvarManager->getCvar(PATHING_RECOVERY_TITLE).getIntValue()),
	TrainingMode(
		PATHING_TIMER_GREEN,
		PATHING_TIMER_YELLOW,
		true,
		_globalCvarManager->getCvar(PATHING_BOOST_MAX_TITLE).getIntValue(),
		_globalCvarManager->getCvar(PATHING_BOOST_DECAY_TITLE).getIntValue()
	) {

}

void PathingMode::SetBallPosition(GameInformation* gameInfo) {
	BallPosition = Vector{ GetRandomFieldX(), GetRandomFieldY(), GetRandomFieldZ() / (float) 1.5};
}

void PathingMode::RunGame(GameInformation* gameInfo) {
	// Remove ball from field
	BallWrapper ball = gameInfo->Ball;
	ball.SetLocation(BallPosition);
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);
}

void PathingMode::EnableGame(GameInformation* gameInfo) {
	gameInfo->Car.GetBoostComponent().SetCurrentBoostAmount(FULL_BOOST);
	TimeRemaining = PathingBaseTime;
}

void PathingMode::OnDisable(GameInformation*) {
	
}

void PathingMode::OnBallHit(GameInformation* gameInfo) {
	BallWrapper ball = gameInfo->Ball;
	double increase = (ball.GetLocation().Z / MAX_SPEED);
	TimeRemaining += PathingBallTouchTime + increase;
	CarWrapper car = gameInfo->Car;
	Vector velocity = car.GetVelocity();
	velocity.Z -= PathingRecoveryBonus;
	car.SetVelocity(velocity);
	BoostWrapper boost = car.GetBoostComponent();
	boost.SetBoostAmount(boost.GetCurrentBoostAmount() + gameInfo->Ball.GetLocation().Z / PathingBallHeightBoostBonus);
	SetBallPosition(gameInfo);
}

void PathingMode::OnBoostPickUp(GameInformation* gameInfo) {
	TimeRemaining += PathingBoostCollectionTime;
}

void PathingMode::OnGoalScored(GameInformation*) {

}

void PathingMode::OnReplayBegin(GameInformation*) {

}

void PathingMode::OnReplayEnd() {

}

void PathingMode::OnTimeRunOut(GameInformation*) {
	EndGame();
}

void PathingMode::RenderGame(CanvasWrapper canvas) {

}

void PathingMode::RenderGameEnd(CanvasWrapper canvas) {
	std::string result = "Result: " + GetTimeString(CurrentTime);
	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM),  (float)(canvas.GetSize().Y * 0.2) });
	canvas.SetColor(COLOR_WHITE);
	canvas.DrawString(result, FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}