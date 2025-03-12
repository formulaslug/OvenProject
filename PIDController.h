//
// Created by coles on 3/11/2025.
//

#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H



class PIDController {
public:
    PIDController(const float kP, const float kI, const float kD): kP(kP), kI(kI), kD(kD), setPoint(0), lastError(0),
                                                                   integral(0) {
    }

    void SetSP(const float setPoint);

    float Compute(float input); // should be run regularly
private:
    const float kP;
    const float kI;
    const float kD;

    float setPoint;

    float lastError;
    float integral;
};



#endif //PIDCONTROLLER_H
