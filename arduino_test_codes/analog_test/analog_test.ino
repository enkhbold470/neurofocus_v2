/*
  test_EEG_serial.ino
  Modified by ChatGPT

  This code:
   - Reads analog values from an EEG sensor connected to A0
   - Sends raw analog values to the Serial Monitor
*/

#define adc_input A0

void setup()
{
  Serial.begin(115200);
  pinMode(adc_input, INPUT);
}

void loop()
{
  int value = analogRead(adc_input);
  Serial.println(value);
  delay(100);  // Send data at 10 Hz
}
