#include "pch.h"
#include "CFigure.h"


CFigure::CFigure(void) {
	this->startX = 0;
	this->startY = 0; 
	this->endX = 0;
	this->endY = 0;
}
CFigure::CFigure(int startX, int startY, int endX, int endY) {
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}
