#include "stdafx.h"
#include "Shape.h"


Shape::Shape()
{
	mb_shape = 1;	
	p.x = -1; p.y = -1;
}


Shape::~Shape()
{
}
void Shape::fDraw(CDC* pdc)
{
	if (mb_shape)
	{
		CPen pen(PS_SOLID, 2, m_clr); 
		CPen* oldpen=pdc->SelectObject(&pen);
		//pdc->Rectangle(p.x - 20, p.y - 20, p.x + 20, p.y + 20);
		pdc->Rectangle(x - 20, y - 20, x + 20, y + 20);

		this->m_clr = RGB(0, 0, 0);
		pdc->SelectObject(oldpen);
	}
	else
	{
		CPen pen(PS_SOLID, 2, m_clr);
		CPen* oldpen = pdc->SelectObject(&pen);;
		//pdc->Ellipse(p.x - 20, p.y - 20, p.x + 20, p.y + 20);
		pdc->Ellipse(x - 20, y - 20, x + 20, y + 20);
		this->m_clr = RGB(0, 0, 0);
		pdc->SelectObject(oldpen);
	}
}
