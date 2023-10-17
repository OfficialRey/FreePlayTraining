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
	return (double) (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000.0;
}