#pragma once

class CMyLine
{
	public:
		CMyLine(void);
		~CMyLine(void);

		CPoint m_start;
		CPoint m_end;

		void Draw(CDC *pDC);
};
