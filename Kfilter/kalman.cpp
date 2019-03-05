/*
 Name:		Kalman.cpp
 Created:	12/11/2018 1:10:58 PM
 Author:	quang
 Editor:	http://www.visualmicro.com
*/

#include "Kalman.h"

void Kalman::kalman(signed short dataSensor){
	this->xPredict = Ft * xFirst + Bt * Ut;
	this->pPredict = Ft * pFirst* Ft + Qt;
	//Update
	this->Kt = pPredict*Ht / (Ht*pPredict*Ht+ Rt);
	this->xUpdate = xPredict + Kt*(dataSensor - Ht * xPredict);
	this->pUpdate = (1 - Kt * Ht)*pPredict;
	this->xFirst = this->xUpdate;
	this->pFirst = this->pUpdate;
}
