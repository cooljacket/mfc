
// MouseKey.h : MouseKey Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMouseKeyApp:
// �йش����ʵ�֣������ MouseKey.cpp
//

class CMouseKeyApp : public CWinAppEx
{
public:
	CMouseKeyApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMouseKeyApp theApp;