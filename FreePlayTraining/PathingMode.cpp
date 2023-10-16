#include "pch.h"
#include "Utility.h"
#include "PathingMode.h"

void PathingMode::StartMode(GameInformation gameInfo) {
	CarWrapper car = gameInfo.Car;
	BallWrapper ball = gameInfo.Ball;

	CurrentTime = STARTING_TIME;
}

void PathingMode::Run(GameInformation gameInfo) {

	// Remove ball from field
	BallWrapper ball = gameInfo.Ball;
	ball.SetLocation(Vector{0,0, -100});
	ball.SetVelocity(Vector{});
	ball.SetAngularVelocity(Vector{}, false);

	// Tick clock
	TimeLeft -= gameInfo.DeltaTime;
}

void PathingMode::OnEnable(GameInformation) {
	Color.R = 255;
	Color.G = 255;
	Color.B = 255;
	Color.A = 255;
}

void PathingMode::OnDisable(GameInformation) {
	
}

void PathingMode::OnBallHit(GameInformation) {
	
}

void PathingMode::onBoostPickUp(GameInformation) {
	TimeLeft += TIME_INCREASE;
}

void PathingMode::Render(CanvasWrapper canvas) {
	canvas.SetColor(Color);
	canvas.SetPosition(Vector2F{ (float)(canvas.GetSize().X / 2), (float)(canvas.GetSize().Y * 0.2) });

	float fractional, whole;

	fractional = std::modf(TimeLeft, &whole);

	std::string seconds = std::to_string(whole);
	std::string milliseconds = std::to_string(fractional);
	std::string result = seconds + ":" + milliseconds;

	canvas.DrawString(result, 2.0, 2.0, true);
	_globalCvarManager->log("Ja");
}