// LrcCalc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CLrcCalcApp:
// �йش����ʵ�֣������ LrcCalc.cpp
//

class CLrcCalcApp : public CWinApp
{
public:
	CLrcCalcApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLrcCalcApp theApp;
