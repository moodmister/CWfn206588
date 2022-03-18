#include "pch.h"
#include "CMyRectangle.h"

CMyRectangle::CMyRectangle() : CFigure() {}
CMyRectangle::CMyRectangle(int startX, int startY, int endX, int endY) 
	: CFigure(startX, startY, endX, endY) {}

void CMyRectangle::draw(CDC* pDC) {
	pDC->Rectangle(this->startX, this->startY, this->endX, this->endY);
}

bool CMyRectangle::pointIsWithin3px(CPoint point) {
	return (point.x >= this->startX - 3 && point.x <= this->startX + 3
		|| point.x >= this->endX - 3 && point.x <= this->endX + 3
		|| point.y >= this->startY - 3 && point.y <= this->startY + 3
		|| point.y >= this->endY - 3 && point.y <= this->endY + 3);
}
