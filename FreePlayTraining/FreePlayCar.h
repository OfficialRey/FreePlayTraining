#pragma once

#include "pch.h"

struct FreePlayCar
{
	CarWrapper Car;
	double BoostAmountPicked;
	bool PickedUpBoost;
	bool Jumped;
};