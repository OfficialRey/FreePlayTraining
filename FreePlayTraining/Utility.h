#pragma once

#include "pch.h"

#define FLOOR 0
#define BALL_RADIUS 92.75
#define CEILING 2044
#define HALF_CEILING (CEILING / 2)
#define QUARTER_CEILING (CEILING / 4)

#define CORNER 1152


#define SIDE_WALL 4096
#define BACK_WALL 5120

#define NO_CORNER_SIDE_WALL (SIDE_WALL - CORNER)
#define NO_CORNER_BACK_WALL (BACK_WALL - CORNER)

#define MIN_ROTATION Vector{-16364, -32768, -32768}
#define MAX_ROTATION Vector{16340, 32764, 32764}
#define MAX_SPEED 2300
#define HALF_SPEED (MAX_SPEED / 2)
#define QUARTER_SPEED (MAX_SPEED / 4)

#define MIN_RECOVERY_DISTANCE MAX_SPEED

#define BOOST_MULTIPLIER (2.0 / 7.0)

#define COLOR_WHITE LinearColor{255, 255, 255, 255}

float GetRandomFieldX();

float GetRandomFieldY();

float GetRandomFieldZ();

Vector GetRandomCarSpeed();

Rotator GetRandomRotation();

double GetTimeSeconds();