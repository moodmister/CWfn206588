#include <string>
#pragma once
class CFigure {
public:
	std::string type;
	int startX, startY, endX, endY;
	CFigure(void);
	CFigure(int, int, int, int);

	virtual void draw(CDC *pDC) = 0;
	virtual bool pointIsWithin3px(CPoint) = 0;
};
