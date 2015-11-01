// Hello.cpp
#include <afxwin.h> // MFC头文件

class CHelloApp : public CWinApp { // 应用程序类
	virtual BOOL InitInstance(); // 初始化实例虚函数
};

BOOL CHelloApp::InitInstance() { // 初始化应用程序实例的成员函数
	CFrameWnd *pFrmWnd = new CFrameWnd(); // 创建框架窗口对象
	pFrmWnd->Create(NULL, L"Hello world!"); // 创建框架窗口
	m_pMainWnd = pFrmWnd; // 将该框架窗口作为应用程序的主窗口
	pFrmWnd->ShowWindow(m_nCmdShow); // 显示主窗口
	return TRUE;
}

CHelloApp theApp; // 唯一的CSHelloApp全局对象
				  // ? main 函数入口在哪里呢？程序从哪里开始运行呢？还是说创建了一个CS app对象就是相当于在运行了呢？