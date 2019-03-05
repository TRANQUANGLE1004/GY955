/*
 Name:		Kalman.h
 Created:	12/11/2018 1:10:58 PM
 Author:	quang
 Editor:	http://www.visualmicro.com
*/
//Config Constance variance KarmanFilter
#define		Ft		1
#define		Bt		0
#define		Ut		0
#define		Qt		1 
#define		Ht		1 
#define		Rt		0
#define		x0		0
#define		p0		0
#define		v0		0
#define		potion0	0
//**************************
#ifndef _Kalman_h
#define _Kalman_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Kalman {

private:
	signed short xFirst;
	signed short pFirst;
	signed short xPredict;
	signed short pPredict;
	signed short xUpdate;
	signed short pUpdate;
	signed short Kt;
	signed short velocity;
	signed short potition;
public:
	Kalman(){
		this->xFirst = x0;
		this->pFirst = p0;
		this->xPredict = 0;
		this->pPredict = 0;
		this->xUpdate = 0;
		this->pUpdate = 0;
		this->Kt = 0;
		this->velocity = v0;
		this->potition = potion0;
	}
	//double* getUpdate();
	//double* getPredict();
	signed short getValue() {
		return this->xUpdate;
	}
	void kalman(signed short dataSensor);
};
class Accel {
public:
	signed short x;
	signed short y;
	Accel() {
		this->x = 0;
		this->y = 0;
	}
	/*signed short getX() { return this->x; }
	signed short getY() { return this->y; }
	void setX(signed short _val) { this->x = _val; }
	void setY(signed short _val) { this->y = _val; }*/
	Accel & operator=(Accel other) {
		this->x = other.x;
		this->y = other.y;
	}
	void reserValue() { this->x = 0; this->y = 0; }
};
class Position {
public:
	signed long positionX;
	signed long positionY;
	signed long positionSum; // =sqrt(x^2+y^2) ^^.
	Position() {
		this->positionX = 0;
		this->positionY = 0;
		this->positionSum = 0;
	}
	Position& operator=(Position other) {
		this->positionX = other.positionX;
		this->positionY = other.positionY;
		this->positionSum = other.positionSum;
	}
	/*signed long getPotitionX() { return this->positionX; }
	signed long getPotitionY() { return this->positionY; }
	signed long getPotitionSum() { return this->positionSum; }
	void getPositionX(signed long _val) { this->positionX = _val; }
	void getPositionY(signed long _val) { this->positionY = _val; }
	void getPositionSum(signed long _val) { this->positionSum = _val; }*/
};
class Velocity {
public:
	signed long velocityX;
	signed long velocityY;
	signed long velocitySum;
	Velocity() {
		this->velocityX = 0;
		this->velocityY = 0;
		this->velocitySum = 0;
	}
	Velocity& operator=(Velocity other) {
		this->velocityX = other.velocityX;
		this->velocityY = other.velocityY;
		this->velocitySum = other.velocitySum;
	}
	/*signed long getVeloX() { return this->velocityX; }
	signed long getVeloY() { return this->velocityY; }
	signed long getVeloSum() { return this->velocitySum; }
	void setVeloX(signed long _val) { this->getVeloX = _val; }
	void setVeloY(signed long _val) { this->getVeloY = _val; }
	void setVeloSum(signed long _val) { this->getVeloSum = _val; }*///why ???
};

#endif

