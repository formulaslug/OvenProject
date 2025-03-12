#include "mbed.h"
// #include "OvenConfig.h"

DigitalOut relayControl(D9);

AnalogIn temperatureInput(A0);

uint8_t getTemperature();



int main()
{
    printf("Main\n");
    // ReSharper disable once CppDFAEndlessLoop
    while(true) {
        // relayControl.write(1);

        const uint16_t temperature = getTemperature();
        printf("Temperature: %u\n", temperature);

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