// classic bluetooth test arduino code
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX
const int analogPin = A0;      // Pin connected to the output of AD620

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    mySerial.println("Transmit Started...");
}

void loop()
{
    int sensorValue = analogRead(analogPin); // Read the analog input
    Serial.println(sensorValue);             // Print the voltage value to the Serial Plotter
    mySerial.println(sensorValue);
    delay(100);
}
