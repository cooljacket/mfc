
// ActivePainter.h : ActivePainter Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CActivePainterApp:
// �йش����ʵ�֣������ ActivePainter.cpp
//

class CActivePainterApp : public CWinAppEx
{
public:
	CActivePainterApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CActivePainterApp theApp;
