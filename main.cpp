#include "mbed.h"
#include "OvenConfig.h"
#include "PIDController.h"

PwmOut relayControl(D9);

AnalogIn temperatureInput(A0);

DigitalOut led(LED1);

uint8_t getTemperature();


typedef enum {
    STARTUP,
    PREHEAT,
    PREHEAT_HOLD,
    CURE,
    CURE_HOLD,
    DWELL,
    DWELL_HOLD,
    FINISH
} OvenState;

OvenState ovenState;

PIDController* pidController;

Timer* timer;

int main()
{
    printf("Main\n");
    ovenState = STARTUP;
    relayControl.period_ms(10000); // 10 second period
    relayControl.write(0.0f);

    led.write(0);

    pidController = new PIDController(PID_KP, PID_KI, PID_KD);

    timer = new Timer();

    // ReSharper disable once CppDFAEndlessLoop
    while(true) {
        const uint16_t temperature = getTemperature();
        printf("Temperature: %u\n", temperature);

        printf("State: %u\n", ovenState);

        switch (ovenState) {
            case STARTUP:
                relayControl.write(0);
                pidController->resetIntegral();
                pidController->SetSP(PREHEAT_TEMP);
                ovenState = PREHEAT;
                break;
            case PREHEAT:
                relayControl.write(pidController->Compute(temperature));
                if (pidController->atSetPoint(temperature, PID_DELTA)) {
                    ovenState = PREHEAT_HOLD;
                    timer->reset();
                    timer->start();
                }
                break;
            case PREHEAT_HOLD:
                relayControl.write(pidController->Compute(temperature));
                if (timer->elapsed_time() >= std::chrono::minutes(PREHEAT_TIME)) {
                    pidController->resetIntegral();
                    pidController->SetSP(CURE_TEMP);
                    ovenState = CURE;
                }
                break;
            case CURE:
                relayControl.write(pidController->Compute(temperature));
                if (pidController->atSetPoint(temperature, PID_DELTA)) {
                    ovenState = CURE_HOLD;
                    timer->reset();
                    timer->start();
                }
                break;
            case CURE_HOLD:
                relayControl.write(pidController->Compute(temperature));
                if (timer->elapsed_time() >= std::chrono::minutes(CURE_TIME)) {
                    pidController->resetIntegral();
                    pidController->SetSP(DWELL_TEMP);
                    ovenState = DWELL;
                }
                break;
            case DWELL:
                relayControl.write(pidController->Compute(temperature));
                if (pidController->atSetPoint(temperature, PID_DELTA)) {
                    ovenState = DWELL_HOLD;
                    timer->reset();
                    timer->start();
                }
                break;
            case DWELL_HOLD:
                relayControl.write(pidController->Compute(temperature));
                if (timer->elapsed_time() >= std::chrono::minutes(DWELL_TIME)) {
                    ovenState = FINISH;
                }
                break;
            case FINISH:
                relayControl.write(0);
                led.write(1);
                break;
            default:
                relayControl.write(0);
                break;
        }

        printf("Output: %f\n", relayControl.read());

        ThisThread::sleep_for(1000ms);
    }

    // main() is expected to loop forever.
    // If main() actually returns the processor will halt
    return 0;
}

uint8_t getTemperature() {
    const float temperatureVolts = temperatureInput.read() * 3.3f;
    // printf("Temperature: %f\n", temperatureVolts);

    return static_cast<uint8_t>(2.28 + (36.3 * temperatureVolts) + (18.8 * temperatureVolts * temperatureVolts));
}