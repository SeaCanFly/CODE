#include "StdAfx.h"		//	MFC 의 모든 헤더파일을 다 갖고 있음
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