
// AutoTrader.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoTraderApp:
// �йش����ʵ�֣������ AutoTrader.cpp
//

class CAutoTraderApp : public CWinApp
{
public:
	CAutoTraderApp();

// ��д
public:
	virtual BOOL InitInstance();
	void updataApp(CString InputData);
	void MessageShow(CString InputData);
// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	CString m_AppPath;
};

extern CAutoTraderApp theApp;