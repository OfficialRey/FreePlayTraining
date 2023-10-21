#include "pch.h"

#include "FreePlayTraining.h"

void FreePlayTraining::RegisterVariables() {
	RegisterVariable(RECOVERY_BASE_TIME_TITLE, RECOVERY_BASE_DEFAULT_TIME, RECOVERY_BASE_MIN_TIME, RECOVERY_BASE_MAX_TIME, &RecoveryBaseTime);
	RegisterVariable(RECOVERY_BOOST_FACTOR_TITLE, RECOVERY_BOOST_DEFAULT_FACTOR, RECOVERY_BOOST_MIN_FACTOR, RECOVERY_BOOST_MAX_FACTOR, &RecoveryBoostFactor);
	RegisterVariable(RECOVERY_TIME_FACTOR_TITLE, RECOVERY_TIME_DEFAULT_FACTOR, RECOVERY_TIME_MIN_FACTOR, RECOVERY_TIME_MAX_FACTOR, &RecoveryTimeFactor);
	}

void FreePlayTraining::RegisterVariable(std::string variable, float defaultValue, float min, float max, std::shared_ptr<float> *ptr) {
	*ptr = std::make_shared<float>(0);
	cvarManager->registerCvar(variable, std::to_string(defaultValue), "", true, true, min, true, max, false).bindTo(*ptr);
	}