#include "pch.h"

#include "Utility.h"


float GetRandomFieldX() {
	return 2 * (float)(rand() % NO_CORNER_SIDE_WALL) - NO_CORNER_SIDE_WALL;
}

float GetRandomFieldY() {
	return  2 * (float)(rand() % NO_CORNER_BACK_WALL) - NO_CORNER_BACK_WALL;
}

float GetRandomFieldZ() {
	return BALL_RADIUS + (float)(rand() % (int)(CEILING - BALL_RADIUS));
}

Vector GetRandomCarSpeed() {
	return Vector{
	2 * (float)(rand() % MAX_SPEED) - MAX_SPEED,
	2 * (float)(rand() % MAX_SPEED) - MAX_SPEED,
	2 * (float)(rand() % MAX_SPEED) - MAX_SPEED
	};
}

Rotator GetRandomRotation() {
	return Rotator{
		(int)(MIN_ROTATION.X + rand() % (int)(MAX_ROTATION.X - MIN_ROTATION.X)),
		(int)(MIN_ROTATION.Y + rand() % (int)(MAX_ROTATION.Y - MIN_ROTATION.Y)),
		(int)(MIN_ROTATION.Z + rand() % (int)(MAX_ROTATION.Z - MIN_ROTATION.Z)),
	};
}

double GetTimeSeconds() {
	return (double)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / MILLI_SECONDS;
}

double GetTimeMilliSeconds() {
	return (double)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

std::string GetScoreString(int currentScore, int possibleScore) {
	return "Score: " + std::to_string(currentScore) + " / " + std::to_string(possibleScore);
}

std::string GetTimeString(double time) {
	float fractional, whole;

	fractional = std::modf(time, &whole);

	std::string seconds = std::to_string(int(whole));
	std::string milliseconds = std::to_string(int(fractional * 100));
	std::string result = seconds + "." + milliseconds;
	return result;
}

float CalculateCenterPosition(CanvasWrapper canvas, std::string text, float fontSize) {
	Vector2F size = canvas.GetStringSize(text, fontSize, fontSize);
	return (canvas.GetSize().X / 2) - (size.X / 2);
}

LinearColor GetColorBasedOnTime(float time, int yellow, int green) {
	LinearColor color = COLOR_RED;
	if (time > green) { color = COLOR_GREEN; }
	else if (time > yellow) { color = COLOR_YELLOW; }
	return color;
}

void RenderScore(CanvasWrapper canvas, double currentScore, double possibleScore) {
	int percentage = (currentScore / possibleScore) * 100.0;

	std::string result = "Score: " + std::to_string((int)currentScore) + " / " + std::to_string((int)possibleScore) + " (" + std::to_string(percentage) + "%)";
	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_SMALL), (float)(canvas.GetSize().Y * 0.05) });
	canvas.SetColor(COLOR_WHITE);
	canvas.DrawString(result, FONT_SIZE_SMALL, FONT_SIZE_SMALL, true);
}

void RenderTime(CanvasWrapper canvas, double time, int yellow, int green) {
	std::string result = GetTimeString(time);

	canvas.SetPosition(Vector2F{ CalculateCenterPosition(canvas, result, FONT_SIZE_MEDIUM), (float)(canvas.GetSize().Y * 0.2) });
	canvas.SetColor(GetColorBasedOnTime(time, yellow, green));
	canvas.DrawString(result, FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, true);
}

double RadiansToDegrees(double radians) {
	return radians * 180.0 / M_PI;
}

double CalculateVectorAngle(Vector a, Vector b) {
	double radians = acos(Vector::dot(a, b) / (a.magnitude() * b.magnitude()));
	return RadiansToDegrees(radians);
}