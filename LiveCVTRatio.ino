/*
	LiveSpeed.ino - Main code to display live CVT ratio.
	Created by Rahul Goyal and Tyler Davis, March 31, 2018.
	Released to Cal Poly Baja SAE. ;)
*/

#include "LiveDisplay.h"
#include "WheelSpeed.h"

const int R_PORT = 2;
const int E_PORT = 3;

const float GEARRATIO = 6.221;

const int CHARS = 3;

// Instantiate front wheel speed
WheelSpeed rWheel = WheelSpeed(12);
WheelSpeed engine = WheelSpeed(4);



void setup() {

	// // Open serial communications and wait for port to open:
	// Serial.begin(9600);
	// while (!Serial) {
	// 	;	// Wait for serial port to connect. Needed for native USB port only.
	// }

	// Set up rear wheel
	const int rWheelInterrupt = digitalPinToInterrupt(R_PORT);
	attachInterrupt(rWheelInterrupt, rWheelISR, RISING);
	// Set up engine
	const int engineInterrupt = digitalPinToInterrupt(E_PORT);
	attachInterrupt(engineInterrupt, engineISR, RISING);

	// Set up display
	myDisplay.begin();

}



void loop() {

	float engineSpeed = engine.getRPS();
	float rWheelSpeed = rWheel.getRPS();

	// Calculate CVT ratio
	if (rWheelSpeed != 0) {
		float cvtRatio = engineSpeed / (rWheelSpeed * GEARRATIO);
		// Update display
		myDisplay.clear();
		myDisplay.title(" CVT Ratio");
		myDisplay.write(cvtRatio, CHARS);
	} else {
		String cvtRatio = "-----";
		// Update display
		myDisplay.clear();
		myDisplay.title(" CVT Ratio");
		myDisplay.write(cvtRatio, CHARS);
	}

}



void rWheelISR() {
	rWheel.calcRPS();
}



void engineISR() {
	engine.calcRPS();
}