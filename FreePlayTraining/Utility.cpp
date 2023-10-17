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