#include <Arduino.h>

#define LED_RED 12
#define LED_YELLOW 11
#define LED_GREEN 10
#define LED_PEDESTRIAN_GREEN 9
#define LED_PEDESTRIAN_RED 8

const long ledRedHighInterval = 4000;
const long ledYellowHighInterval = 2000;
const long ledGreenHighInterval = 6000;
const long ledPedestrianGreenHighInterval = 6000;
const long ledPedestrianRedHighInterval = 6000;

const long ledRedLowInterval = 8000;
const long ledYellowLowInterval = 6000;
const long ledGreenLowInterval = 6000;
const long ledPedestrianGreenLowInterval = 6000;
const long ledPedestrianRedLowInterval = 6000;

unsigned long ledRedLastMillis;
unsigned long ledYellowLastMillis;
unsigned long ledGreenLastMillis;
unsigned long ledPedestrianGreenLastMillis = 0;
unsigned long ledPedestrianRedLastMillis = 0;

unsigned long ledLoop(uint8_t pin, long lowInterval, long highInterval, unsigned long currentMillis, unsigned long lastMillis) {
    if (LOW == digitalRead(pin)) {
        if (currentMillis - lastMillis >= lowInterval) {
            digitalWrite(pin, HIGH);
            return currentMillis;
        }
    } else if (currentMillis - lastMillis >= highInterval) {
        digitalWrite(pin, LOW);
        return currentMillis;
    }
    return lastMillis;
}

void ledRedLoop(unsigned long currentMillis) {
    ledRedLastMillis = ledLoop(LED_RED, ledRedLowInterval, ledRedHighInterval, currentMillis, ledRedLastMillis);
}

void ledYellowLoop(unsigned long currentMillis) {
    ledYellowLastMillis = ledLoop(LED_YELLOW, ledYellowLowInterval, ledYellowHighInterval, currentMillis, ledYellowLastMillis);
}

void ledGreenLoop(unsigned long currentMillis) {
    ledGreenLastMillis = ledLoop(LED_GREEN, ledGreenLowInterval, ledGreenHighInterval, currentMillis, ledGreenLastMillis);
}

void setup() {

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_PEDESTRIAN_GREEN, OUTPUT);
    pinMode(LED_PEDESTRIAN_RED, OUTPUT);

    unsigned long currentMillis = millis();
    ledRedLastMillis = currentMillis;
    ledYellowLastMillis = currentMillis;
    ledGreenLastMillis = currentMillis;

    digitalWrite(LED_GREEN, HIGH);

}

void loop() {

    unsigned long currentMillis = millis();
    ledRedLoop(currentMillis);
    ledYellowLoop(currentMillis);
    ledGreenLoop(currentMillis);

}
