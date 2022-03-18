#include "pch.h"
#include "CMyLine.h"
#include <vector>

CMyLine::CMyLine(void) : CFigure() {}

CMyLine::CMyLine(int startX, int startY, int endX, int endY) 
	: CFigure(startX, startY, endX, endY) {}

void CMyLine::draw(CDC* pDC) {
	pDC->MoveTo(this->startX, this->startY);
	pDC->LineTo(this->endX, this->endY);
}

bool CMyLine::pointIsWithin3px(CPoint point) {
	long xDiff = this->startX - this->endX >= 0,
		yDiff = this->startY - this->endY;
	if (xDiff != 0 && yDiff != 0) {
		double angle = ((double)yDiff / (double)xDiff);
		double coeff = this->startY - this->startX * angle;
		// Function is angle * x + coeff +/- 3 = y
		return (angle * point.x + coeff + 3 >= point.y
			&& angle * point.x + coeff - 3 <= point.y);
	}
	return (point.y >= startY - 3
		&& point.y <= endY + 3
		|| point.x >= startX - 3
		&& point.x <= endX + 3);
}
