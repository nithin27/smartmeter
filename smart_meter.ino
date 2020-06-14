/*
 * Integrate a signal read on analog input 0.
 * Print the result every 2 seconds on the serial port.
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(13,12); // RX, TX

unsigned long last_time_sampled = 0;
unsigned long last_time_printed = 0;

// The integral is in units of DN*us, 1 DN being the ADC step.
float integral = 0;
float integral1 = 0;
float integral2 = 0;
float integral3 = 0;

float sample = 0;
float sample1 = 0;
float sample2 = 0;
float sample3 = 0;

float power = 0;
float power1 = 0;
float power2 = 0;
float power3 = 0;

float energy = 0;
float energy1 = 0;
float energy2 = 0;
float energy3 = 0;

float cost = 0;
float cost1 = 0;
float cost2 = 0;
float cost3 = 0;

int line1=0;
int line2=0;
int i=0; 

// Convert from DN*us to V*s, assuming a 5 V reference.
const float conversion = 5.0 / 1024 * 1e-6;

void setup()
{
    Serial.begin(9600);
     mySerial.begin(9600);
     pinMode(8, INPUT);
     pinMode(9, INPUT);
}

void loop()
{
    
    unsigned long now = micros();

    // Approximate the signal as a constant equal to the current sample
    // from the time of the previous sample until now.
    //integral += sample ;//* (now - last_time_sampled);
    //last_time_sampled = now;

    // Print the results every 2 seconds.
    if (now - last_time_printed >= 1000000) {
        sample = analogRead(A5)*.0016;
        delay(10);
        sample = analogRead(A5)*.0016;
        delay(10);
        sample1 = analogRead(A4)*.0016;
        delay(10);
        sample1 = analogRead(A4)*.0016;
        delay(10);
        sample2 = analogRead(A3)*.0016;
        delay(10);
        sample2 = analogRead(A3)*.0016;
        delay(10);
        sample3 = analogRead(A0)*.0016;
        delay(10);
        sample3 = analogRead(A0)*.0016;
        delay(10);
        integral += sample ;
        integral1 += sample1 ;
        integral2 += sample2 ;
        integral3 += sample3 ;

        power = integral*230;
        power1 = integral1*230;
        power2 = integral2*230;
        power3 = integral3*230;

        energy = power/3600000;
        energy1 = power1/3600000;
        energy2 = power2/3600000;
        energy3 = power3/3600000;

        cost = power*10/3600000;
        cost1 = power1*10/3600000;
        cost2 = power2*10/3600000;
        cost3 = power3*10/3600000;
        
        Serial.print("input = ");
        Serial.print(sample);
        Serial.print(", output = ");
        Serial.print(power); //* conversion);
        Serial.print(", kwh = ");
        Serial.print(energy); //* conversion);
        Serial.print(", cost = ");
        Serial.println(cost); //* conversion);
        
        
         Serial.print("input1 = ");
        Serial.print(sample1);
        Serial.print(", output1 = ");
        Serial.print(power1); //* conversion);
        Serial.print(", kwh = ");
        Serial.print(energy1); //* conversion);
        Serial.print(", cost1 = ");
        Serial.println(cost1); //* conversion);

          Serial.print("input2 = ");
        Serial.print(sample2);
        Serial.print(", output2 = ");
        Serial.print(power2); //* conversion);
        Serial.print(", kwh = ");
        Serial.print(energy2); //* conversion);
        Serial.print(", cost2 = ");
        Serial.println(cost2); //* conversion);

          Serial.print("input3 = ");
        Serial.print(sample3);
        Serial.print(", output3 = ");
        Serial.print(power3); //* conversion);
        Serial.print(", kwh = ");
        Serial.print(energy3); //* conversion);
        Serial.print(", cost3 = ");
        Serial.println(cost3); //* conversion);
        if (digitalRead(8) == HIGH) {
          line1=100;
        }
        else
        {
          line1=200;
        }
        
         if (digitalRead(9) == HIGH) {
          line2=100;
        }
        else
        {
          line2=200;
        }
        Serial.println(line1); //* conversion);
        Serial.println(line2); //* conversion);
        i=i+1;
       // mySerial.println(power);
       if(i==10)
       {
        mySerial.print('|');
        mySerial.print(power);
        mySerial.print('|');
        mySerial.print(power1);
        mySerial.print('|');
        mySerial.print(power2);
        mySerial.print('|');
        mySerial.print(power3);
        mySerial.print('|');
        mySerial.print(cost);
        mySerial.print('|');
        mySerial.print(cost1);
        mySerial.print('|');
        mySerial.print(cost2);
        mySerial.print('|');
        mySerial.print(cost3);
        mySerial.print('|');
        mySerial.print(line1);
        mySerial.print('|');
        mySerial.print(line2);
        mySerial.print('|');
        mySerial.println();
        i=0;
       }
//        mySerial.println(power2);
//        mySerial.println(power3);
         Serial.println();
         Serial.println();
        last_time_printed = now;
    }

    // Limit the sampling rate to no more than 1000/s.
    delay(1);
}
