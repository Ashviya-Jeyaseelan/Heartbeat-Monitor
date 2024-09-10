#define USE_ARDUINO_INTERRUPTS true


#include<LiquidCrystal.h> // LCD library 
#include <PulseSensorPlayground.h>  // Pulse Sensor Library


int const PULSE_SENSOR_PIN = 0; // A0 pin
int signal;
int threshold = 550; // Threshold for pulse sensor
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Object for LCD


PulseSensorPlayground pulseSensor; // Object for pulse sensor

void setup() {
  Serial.begin(9600); // Exchanges data at rate of 9600 bits per second
  lcd.begin(16, 2); // Defining LCD dimensions of 16 columns and 2 rows
  pulseSensor.analogInput(0); // Connects to pin A0
  pulseSensor.setThreshold(threshold); // Set threshold for pulse sensor
  pinMode(7, OUTPUT); // Connect to pin 7 for LED

  if (pulseSensor.begin()){ // Verify that pulse sensor libary works
		Serial.println("PulseSensor object created!");
	}
}


void loop() {
  int heartBPM = pulseSensor.getBeatsPerMinute();
  lcd.setCursor(0,0); // Text displayed starting from left side 
  measureHeartBeat(heartBPM); // Method to measure our heart rate

  if (heartBPM == 0){ // If no heart detection, notify user nothing is detected
    lcd.print("No heart beat detected.");
    }

  delay(5); // To allow for easier processing
}

void measureHeartBeat(int heartBPM)
{
  if (pulseSensor.sawStartOfBeat()) // Constantly test to see if a beat happened 
  {               
    delay(10); 
		Serial.println("♥  A HeartBeat Happened ! "); // Displays in console pulse detected
		Serial.print("BPM: " + String(heartBPM)); // Displays in console BPM
    lcd.print("Measured BPM:" + String(heartBPM)); // Displays the measured BPM on LCD
    digitalWrite(7, 1); // Turn on LED
    delay(100);
    digitalWrite(7, 0); // Turn off LED
  }
}
