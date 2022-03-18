#include "CFigure.h"
#include <string>
#pragma once
class CMyRectangle : public CFigure {
private:
public:
	std::string type = "CMyRectangle";
	CMyRectangle(void);
	CMyRectangle(int, int, int, int);

	void draw(CDC* pDC);
	bool pointIsWithin3px(CPoint point);
};
