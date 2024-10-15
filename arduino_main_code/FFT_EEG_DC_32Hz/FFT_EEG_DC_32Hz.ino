/*
  FFT_EEG_DC_32Hz.ino
  Original code by LINGIB
  Modified to remove TFT display functionality

  This code:
   - Extracts frequencies in the range DC-32Hz from a complex waveform
   - Displays their bin[] amplitudes via Serial output
   - Each of the 32 bins is 1Hz wide
   - The DC offset is automatically removed from bin[0]

  Library required:
   - fix_fft.h (you need to have this library installed)

*/

#include "fix_fft.h"

// ----- Analog input
#define adc_input A0

// ----- FFT parameters
// change sample_freq to hz you want to sample like 64, 128, 256, 512, 1024, 2048, 4096
const unsigned long sample_freq = 1024;                    // Hz (Nyquist freq = 1024Hz)
const short n = 64;                                        // Number of data points (must be power of 2)
const unsigned long sample_period = 1000000 / sample_freq; // Microseconds
const short m = (short(log10(n) / log10(2)));              // Equivalent to m=log2(n), where 2^m = n
char data[n];                                              // Real values
char im[n];                                                // Imaginary values
short dc_offset;
short dc_counter = 5;
bool data_valid = false;

// ----- Timers
unsigned long display_time = 1000000L;
unsigned long Timer1;
unsigned long Timer2;

void setup()
{
    Serial.begin(115200);
    pinMode(adc_input, INPUT);

    // ----- Start timers
    Timer1 = micros() + sample_period; // Set loop() timer
    Timer2 = micros() + display_time;  // Print results every second
}

void loop()
{
    // ----- Locals
    static short i = 0; // Sample counter

    // ----- Loop control
    while (micros() < Timer1)
        ;                    // Wait until next sample is due
    Timer1 += sample_period; // Reset loop timer

    if (i < n)
    {
        ////////////////////////
        //  Acquire the data  //
        ////////////////////////

        // ----- Take 'n' samples
        short value = analogRead(adc_input);
        data[i] = map(value, 0, 1023, 0, 255);
        im[i] = 0;
        i++;
    }
    else
    {
        ////////////////////////////////
        //  Process and Display Data  //
        ////////////////////////////////

        // ----- Display data once per second
        if (micros() > Timer2)
        {
            Timer2 += display_time;

            // ----- Process data
            fix_fft(data, im, m, 0);

            // ----- Calculate amplitus
            for (short i = 0; i < n / 2; i++)
            { // Ignore image data beyond n/2
                data[i] = sqrt(data[i] * data[i] + im[i] * im[i]);
            }

            // ----- Capture DC offset
            if (!data_valid && (dc_counter > 0))
            {
                dc_counter--;
                if (dc_counter < 1)
                {
                    data_valid = true;
                    dc_offset = data[0];
                }
            }

            // ----- Display the data
            if (data_valid)
            {
                // ----- Remove DC offset
                data[0] -= dc_offset;

                // ----- Send all bins to Serial Monitor
                String message = "";
                for (short i = 0; i < n / 2 - 1; i++)
                {
                    message += (short)data[i];
                    message += ',';
                }
                message += (short)data[n / 2 - 1];
                Serial.println(message);
            }
        }

        /////////////////////////////////////////////////
        //  Prepare for next sample acquisition
        /////////////////////////////////////////////////

        i = 0; // Reset data acquisition
    }
}
