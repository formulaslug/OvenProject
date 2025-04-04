//
// Created by coles on 3/11/2025.
//

#include "PIDController.h"

#include <algorithm>

void PIDController::SetSP(const float setPoint) {
    this->setPoint = setPoint;
}

float PIDController::Compute(const float input) {
    const float error = this->setPoint - input;

    const float p = error * this->kP;

    this->integral += error;
    const float i = this->integral * this->kI;

    const float d = (error - this->lastError) * this->kD;
    this->lastError = error;

    return std::max(0.0f, std::min(p + d + i, 0.8f));
}

void PIDController::resetIntegral() {
    this->integral = 0;
}

bool PIDController::atSetPoint(float input, float delta) {
    return (input + delta >= this->setPoint) && (input - delta <= this->setPoint);
}
