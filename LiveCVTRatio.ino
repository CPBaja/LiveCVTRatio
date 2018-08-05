/*
	LiveSpeed.ino - Main code to display live CVT ratio.
	Created by Rahul Goyal and Tyler Davis, February 15, 2018.
	Released to Cal Poly Baja SAE. ;)
*/

#include "LiveDisplay.h"
#include "WheelSpeed.h"

const byte E_PORT = 2;
const byte R_PORT = 3;

const float GEAR_RATIO = 6.579;

const byte CHARS = 3;

// Instantiate front wheel speed
WheelSpeed rWheel = WheelSpeed(12);
WheelSpeed engine = WheelSpeed(4);



void setup() {

	// // Open serial communications and wait for port to open:
	// Serial.begin(9600);
	// while (!Serial) {
	// 	;	// Wait for serial port to connect. Needed for native USB port only.
	// }

	// Set up engine
	const byte engineInterrupt = digitalPinToInterrupt(E_PORT);
	attachInterrupt(engineInterrupt, engineISR, RISING);
	// Set up rear wheel
	const byte rWheelInterrupt = digitalPinToInterrupt(R_PORT);
	attachInterrupt(rWheelInterrupt, rWheelISR, RISING);

	// Set up display
	myDisplay.begin();

}



void loop() {

	float engineSpeed = engine.getRPS();
	float rWheelSpeed = rWheel.getRPS();

	// Update display
	myDisplay.clear();
	myDisplay.title(" CVT Ratio");
	// Calculate CVT ratio
	if (rWheelSpeed) {
    Serial.println(engineSpeed / (GEAR_RATIO * rWheelSpeed));
		myDisplay.write(engineSpeed / (GEAR_RATIO * rWheelSpeed), CHARS);
	} else {
		myDisplay.write("---", CHARS);
	}

}



void rWheelISR() {
	rWheel.calcRPS();
}



void engineISR() {
	engine.calcRPS();
}
