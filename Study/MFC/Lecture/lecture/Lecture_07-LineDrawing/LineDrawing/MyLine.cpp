#include "StdAfx.h"		//	MFC �� ��� ��������� �� ���� ����
#include "MyLine.h"

CMyLine::CMyLine(void)
{
}

CMyLine::~CMyLine(void)
{
}

void CMyLine::Draw(CDC *pDC)
{
	pDC->MoveTo(m_start);
	pDC->LineTo(m_end);
	
}