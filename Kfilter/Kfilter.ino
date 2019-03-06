//link reference:https://www.nxp.com/files-static/sensors/doc/app_note/AN3397.pdf
//author: Alan_di_bo ^^
//date: 4/3/2019 about 1 month before the Robo contest 2019 ^^
// Thank you for every one ^^
// I am feeling happy ....
// and I am missing U 
// command draw plot: {@Plot.MyFirstPlotWindow.Sensor.Green voltage}
// combo time: 
//unsigned long _tempTime = millis();
//Serial.println(millis() - _tempTime); 
//{@Plot.MyFirstPlotWindow.Accel.Green accel[0].x}{@Plot.MyFirstPlotWindow.Velocity.Blue veloc[0].velocityX}{@Plot.MyFirstPlotWindow.Position.Red position[0].positionX}
#include "kalman.h"
#include "BNO055_support.h"
#include <Wire.h>
#include"Configuration.h"
//*******************************************************
//Definition
//
//*******************************************************
//Kalman kal;
struct bno055_t myBNO;
struct bno055_accel myAccel;
// variable 
Accel accel[2]; // 2 value is value now and value past 
//****************
Velocity veloc[2];
//****************
Position position[2];
Accel cali;
unsigned long time = 0; 
//
void setup() //This code is executed once
{
	//Initialize I2C communication
	Wire.begin();

	//Initialization of the BNO055
	BNO_Init(&myBNO); //Assigning the structure to hold information about the device

	//Configuration to NDoF mode
	bno055_set_operation_mode(OPERATION_MODE_ACCONLY);
	Serial.begin(115200);
	//calibrate(&cali);
	/*unsigned long _tempTime = millis();
	calibrate(&cali);
	Serial.println(millis() - _tempTime);*/
}

void loop() //This code is looped forever
{
	//unsigned long _tempTime = millis();
	run();
	Serial.println(accel[0].x);
	//Serial.println(millis() - _tempTime);
}
void calibrate(Accel* ptr) {
	
	long sumAccelx = 0;
	long sumAccely = 0;
	for (size_t i = 0; i <= 1023; i++)
	{	
		bno055_read_accel_xyz(&myAccel);
		sumAccelx += myAccel.x;
		sumAccely += myAccel.y;
	}
	Serial.println((float)sumAccelx/1024.0f);
	Serial.println((float)sumAccely/1024.0f);
	ptr->x = sumAccelx / 1024; // keep number before the Dot (.) EX: 1.2 ->1|| 0.9999->0
	ptr->y = sumAccely / 1024;	//similar ^
}
void getSensor(unsigned char _sample,Accel* ptr) { // no check
	//ptr->reserValue();//reset value
	signed long tempX = 0;
	signed long tempY = 0;
	for (unsigned char i = 0; i <= _sample; i++)
	{
		bno055_read_accel_xyz(&myAccel);
		if (myAccel.x <= NON_MOVE_THRESHOLD_X && myAccel.x >= -NON_MOVE_THRESHOLD_X) {
			myAccel.x = 0;
		}
		if (myAccel.y <= NON_MOVE_THRESHOLD_Y && myAccel.y >= -NON_MOVE_THRESHOLD_Y) {
			myAccel.y = 0;
		}
		tempX += myAccel.x;
		tempY += myAccel.y;
	}
	ptr->x = tempX / _sample;
	ptr->y = tempY / _sample;
}
void run() {
	getSensor(1, &accel[1]); // good job
	//Serial.println(accel[0].x);
	veloc[1].velocityX = veloc[0].velocityX + accel[0].x + (accel[1].x - accel[0].x)>>1;
	veloc[1].velocityY = veloc[0].velocityY + accel[0].y + (accel[1].y - accel[0].y)>>1;
	//
	//position[1].positionX = position[0].positionX + veloc[0].velocityX*DELTA_T + ((veloc[1].velocityX - veloc[0].velocityX)*DELTA_T) / 2;
	//position[1].positionY = position[0].positionY + veloc[0].velocityY*DELTA_T + ((veloc[1].velocityY - veloc[0].velocityY)*DELTA_T) / 2;
	// update value
	position[1].positionX = position[0].positionX + veloc[0].velocityX + (veloc[1].velocityX - veloc[0].velocityX) >> 1;
	position[1].positionY = position[0].positionY + veloc[0].velocityY + (veloc[1].velocityY - veloc[0].velocityY) >> 1;
	accel[0] = accel[1];
	veloc[0] = veloc[1];
	position[0] = position[1];
	//hihi
}