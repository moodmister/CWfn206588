#include "CFigure.h"
#include <string>
#pragma once
class CMyLine : public CFigure {
public:
	std::string type = "CMyLine";
	CMyLine(void);
	CMyLine(int startX, int startY, int endX, int endY);

	void draw(CDC*);
	bool pointIsWithin3px(CPoint);
};

