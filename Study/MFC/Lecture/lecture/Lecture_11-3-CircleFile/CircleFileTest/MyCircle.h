#pragma once

class CMyCircle
{
	public:
		CPoint m_pt;

	public:
		CMyCircle(void);
		~CMyCircle(void);
			
		void Draw(CDC *pDC)
		{
			pDC->Ellipse(m_pt.x-50,m_pt.y-50,m_pt.x+50,m_pt.y+50);
		}
};
