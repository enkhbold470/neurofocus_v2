const int triggerPin = 4;         // the number of the LED pin
int batteryState = LOW;           // batteryState used to set the LED
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 5000;       // interval at which to blink (milliseconds)

void setup()
{
    pinMode(triggerPin, OUTPUT);
}

void loop()
{
    batteryTrigger();
}

void batteryTrigger()
{

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        // save the last time you blinked the LED
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (batteryState == LOW)
        {
            batteryState = HIGH;
        }
        else
        {
            batteryState = LOW;
        }

        // set the LED with the batteryState of the variable:
        digitalWrite(triggerPin, batteryState);
    }
}