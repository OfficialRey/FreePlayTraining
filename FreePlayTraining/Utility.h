#pragma once

#include "pch.h"

// Field Values

#define FLOOR 0
#define CEILING 2044
#define HALF_CEILING (CEILING / 2)
#define QUARTER_CEILING (CEILING / 4)

#define CORNER 1152

#define SIDE_WALL 4096
#define BACK_WALL 5120

#define NO_CORNER_SIDE_WALL (SIDE_WALL - CORNER)
#define NO_CORNER_BACK_WALL (BACK_WALL - CORNER)

// Goal Values

#define GOAL_HEIGHT 642.775
#define GOAL_CENTER_HEIGHT (GOAL_HEIGHT / 2)

#define GOAL_DEPTH 880
#define BACK_GOAL (BACK_WALL + GOAL_DEPTH)

#define BLUE_GOAL Vector{0, -BACK_GOAL, GOAL_CENTER_HEIGHT}
#define ORANGE_GOAL Vector{0, BACK_GOAL, GOAL_CENTER_HEIGHT}

// Game Constants

#define MIN_ROTATION Vector{-16364, -32768, -32768}
#define MAX_ROTATION Vector{16340, 32764, 32764}
#define MAX_SPEED 2300
#define HALF_SPEED (MAX_SPEED / 2)
#define QUARTER_SPEED (MAX_SPEED / 4)

#define CAR_GROUND 17.01f
#define BALL_RADIUS 92.75f

#define FULL_BOOST 100
#define START_BOOST_AMOUNT 0.33f
#define SMALL_BOOST_AMOUNT 0.12f
#define BIG_BOOST_AMOUNT 1.0f
#define DEFAULT_BOOST_DECAY 33

#define DEFAULT_GRAVITY 650.0f

// Custom Values

#define MIN_RECOVERY_DISTANCE MAX_SPEED

#define BOOST_MULTIPLIER (2.0 / 7.0)
#define MILLI_SECONDS 1000.0

// Render Options

#define COLOR_WHITE LinearColor{255, 255, 255, 255}
#define COLOR_GREEN LinearColor{0, 255, 0, 255}
#define COLOR_YELLOW LinearColor{255, 255, 0, 255}
#define COLOR_RED LinearColor{255, 0, 0, 255}
#define FONT_SIZE_SMALL 4
#define FONT_SIZE_MEDIUM 6

// Event Hooks

#define HOOK_ENGINE_TICK "Function Engine.Interaction.Tick"
#define HOOK_BALL_HIT "Function TAGame.Ball_TA.OnCarTouch"
#define HOOK_PICKUP_BOOST "Function TAGame.VehiclePickup_Boost_TA.Pickup"
#define HOOK_GOAL_SCORED "Function TAGame.Ball_TA.OnHitGoal"
#define HOOK_GOAL_REPLAY_BEGIN "Function GameEvent_Soccar_TA.ReplayPlayback.BeginState"
#define HOOK_GOAL_REPLAY_END "Function GameEvent_Soccar_TA.ReplayPlayback.EndState"
#define HOOK_PLAYER_FREEPLAY_RESET "Function TAGame.GameInfo_TA.PlayerResetTraining"
#define HOOK_MATCH_QUIT "Function TAGame.GameEvent_Soccar_TA.Destroyed"

// Commands

#define COMMAND_UNLIMITED_BOOST "boost set unlimited"
#define COMMAND_LIMITED_BOOST "boost set limited"
#define COMMAND_SKIP_REPLAY "restart_players"

float GetRandomFieldX();

float GetRandomFieldY();

float GetRandomFieldZ();

Vector GetRandomCarSpeed();

Rotator GetRandomRotation();

double GetTimeSeconds();

double GetTimeMilliSeconds();

std::string GetScoreString(int, int);

std::string GetTimeString(double);

float CalculateCenterPosition(CanvasWrapper, std::string, float);

LinearColor GetColorBasedOnTime(float, int, int);

void RenderScore(CanvasWrapper, double, double);

void RenderTime(CanvasWrapper , double, int, int);