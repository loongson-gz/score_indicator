
// score_indicator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cscore_indicatorApp: 
// �йش����ʵ�֣������ score_indicator.cpp
//

class Cscore_indicatorApp : public CWinApp
{
public:
	Cscore_indicatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cscore_indicatorApp theApp;