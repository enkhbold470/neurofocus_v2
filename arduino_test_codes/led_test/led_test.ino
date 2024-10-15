int LED1 = 5;
int LED2 = 6;
int LED3 = 9;

void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    ledTest(200);
}

void ledTest(int delayTime)
{
    int leds[] = {LED1, LED2, LED3};

    for (int i = 0; i < 3; i++)
    {
        digitalWrite(leds[i], HIGH);
        delay(delayTime);
    }

    for (int i = 0; i < 3; i++)
    {
        digitalWrite(leds[i], LOW);
    }
}

void loop()
{
}