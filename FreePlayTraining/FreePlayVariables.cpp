#include "pch.h"

#include "FreePlayTraining.h"

void FreePlayTraining::RegisterVariables() {
	// Recovery
	RegisterVariable(RECOVERY_BASE_TIME_TITLE, RECOVERY_BASE_DEFAULT_TIME, RECOVERY_BASE_MIN_TIME, RECOVERY_BASE_MAX_TIME, &RecoveryBaseTime);
	RegisterVariable(RECOVERY_BOOST_FACTOR_TITLE, RECOVERY_BOOST_DEFAULT_FACTOR, RECOVERY_BOOST_MIN_FACTOR, RECOVERY_BOOST_MAX_FACTOR, &RecoveryBoostFactor);
	RegisterVariable(RECOVERY_TIME_FACTOR_TITLE, RECOVERY_TIME_DEFAULT_FACTOR, RECOVERY_TIME_MIN_FACTOR, RECOVERY_TIME_MAX_FACTOR, &RecoveryTimeFactor);
	RegisterVariable(RECOVERY_BOOST_MAX_TITLE, RECOVERY_BOOST_DEFAULT_MAX, RECOVERY_BOOST_MIN_MAX, RECOVERY_BOOST_MAX_MAX, &RecoveryMaxBoost);
	RegisterVariable(RECOVERY_BOOST_DECAY_TITLE, RECOVERY_BOOST_DEFAULT_DECAY, RECOVERY_BOOST_MIN_DECAY, RECOVERY_BOOST_MAX_DECAY, &RecoveryBoostDecay);

	// Pathing
	RegisterVariable(PATHING_BASE_TIME_TITLE, PATHING_BASE_DEFAULT_TIME, PATHING_BASE_MIN_TIME, PATHING_BASE_MAX_TIME, &PathingBaseTime);
	RegisterVariable(PATHING_BOOST_COLLECTION_TITLE, PATHING_BOOST_COLLECTION_DEFAULT_TIME, PATHING_BOOST_COLLECTION_MIN_TIME, PATHING_BOOST_COLLECTION_MAX_TIME, &PathingBoostCollectionTime);
	RegisterVariable(PATHING_BALL_TOUCH_TITLE, PATHING_BALL_TOUCH_DEFAULT_TIME, PATHING_BALL_TOUCH_MIN_TIME, PATHING_BALL_TOUCH_MAX_TIME, &PathingBallTouchTime);
	RegisterVariable(PATHING_BALL_BONUS_TITLE, PATHING_BALL_DEFAULT_BONUS, PATHING_BALL_MIN_BONUS, PATHING_BALL_MAX_BONUS, &PathingBallBoostBonus);
	RegisterVariable(PATHING_RECOVERY_TITLE, PATHING_DEFAULT_RECOVERY, PATHING_MIN_RECOVERY, PATHING_MAX_RECOVERY, &PathingRecoveryBonus);
	RegisterVariable(PATHING_BOOST_MAX_TITLE, PATHING_BOOST_DEFAULT_MAX, PATHING_BOOST_MIN_MAX, PATHING_BOOST_MAX_MAX, &PathingMaxBoost);
	RegisterVariable(PATHING_BOOST_DECAY_TITLE, PATHING_BOOST_DEFAULT_DECAY, PATHING_BOOST_MIN_DECAY, PATHING_BOOST_MAX_DECAY, &PathingBoostDecay);

	// Pop
	RegisterVariable(POP_BASE_TIME_TITLE, POP_BASE_DEFAULT_TIME, POP_BASE_MIN_TIME, POP_BASE_MAX_TIME, &PopBaseTime);
	RegisterVariable(POP_BALL_HEIGHT_TITLE, POP_BALL_DEFAULT_HEIGHT, POP_BALL_MIN_HEIGHT, POP_BALL_MAX_HEIGHT, &PopMinBallHeight);
	RegisterVariable(POP_GRAVITY_TITLE, POP_DEFAULT_GRAVITY, POP_MIN_GRAVITY, POP_MAX_GRAVITY, &PopGravity);
	RegisterVariable(POP_BOOST_MAX_TITLE, POP_BOOST_DEFAULT_MAX, POP_BOOST_MIN_MAX, POP_BOOST_MAX_MAX, &PopMaxBoost);
	RegisterVariable(POP_BOOST_DECAY_TITLE, POP_BOOST_DEFAULT_DECAY, POP_BOOST_MIN_DECAY, POP_BOOST_MAX_DECAY, &PopBoostDecay);
}

void FreePlayTraining::RegisterVariable(std::string variable, float defaultValue, float min, float max, std::shared_ptr<float> *ptr) {
	*ptr = std::make_shared<float>(0);
	cvarManager->registerCvar(variable, std::to_string(defaultValue), "", true, true, min, true, max, false).bindTo(*ptr);
	}

void FreePlayTraining::ResetVariables() {
	switch (CurrentContext) {
	case FreePlayTraining::RECOVERY:
		// Reset Recovery Parameters
		cvarManager->getCvar(RECOVERY_BASE_TIME_TITLE).ResetToDefault();
		cvarManager->getCvar(RECOVERY_BOOST_FACTOR_TITLE).ResetToDefault();
		cvarManager->getCvar(RECOVERY_TIME_FACTOR_TITLE).ResetToDefault();
		cvarManager->getCvar(RECOVERY_BOOST_MAX_TITLE).ResetToDefault();
		cvarManager->getCvar(RECOVERY_BOOST_DECAY_TITLE).ResetToDefault();
		break;
	case FreePlayTraining::PATHING:
		// Reset Pathing Parameters
		cvarManager->getCvar(PATHING_BASE_TIME_TITLE).ResetToDefault();
		cvarManager->getCvar(PATHING_BOOST_COLLECTION_TITLE).ResetToDefault();
		cvarManager->getCvar(PATHING_BALL_TOUCH_TITLE).ResetToDefault();
		cvarManager->getCvar(PATHING_BALL_BONUS_TITLE).ResetToDefault();
		cvarManager->getCvar(PATHING_RECOVERY_TITLE).ResetToDefault();
		cvarManager->getCvar(PATHING_BOOST_MAX_TITLE).ResetToDefault();
		cvarManager->getCvar(PATHING_BOOST_DECAY_TITLE).ResetToDefault();
		break;
	case FreePlayTraining::POP:
		break;
	case FreePlayTraining::GOALIE:
		break;
	default:
		break;
	}
}