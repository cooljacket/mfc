#include "shello.h" // WHello头文件

CSHelloApp theApp; // 创建唯一的CSHelloApp全局对象

BOOL CSHelloApp::InitInstance() { // 初始化应用程序的实例
	m_pMainWnd = new CSHelloFrame(); // 创建应用程序主窗口对象
	m_pMainWnd->ShowWindow(m_nCmdShow); // 显示主窗口
	m_pMainWnd->UpdateWindow(); // 刷新主窗口
	return TRUE;
}

BEGIN_MESSAGE_MAP(CSHelloFrame, CFrameWnd) // 消息映射
	ON_WM_PAINT()		// 绘图消息
	ON_WM_LBUTTONUP() // 松开鼠标左键消息
END_MESSAGE_MAP()

CSHelloFrame::CSHelloFrame() { // 框架类的构造函数
							   // 窗口类名指针=NULL：使用CFrameWnd类的默认属性
	Create(NULL, L"SHello Application"); // 创建框架窗口
}

void CSHelloFrame::OnPaint() { // 绘图函数（响应PAINT消息）
	CPaintDC dc(this); // 创建绘图DC对象
	dc.TextOut(0, 0, "Hello, World!"); // 写文本串
}

// 鼠标响应函数（响应LBUTTONUP消息）
void CSHelloFrame::OnLButtonUp(UINT nFlags, CPoint point) {
	char buf[40]; // 定义字符串缓冲区
				  // 生成Hello文本和鼠标当前位置坐标的字符串：
	sprintf_s(buf, 40, "Hello! (%d, %d)", point.x, point.y);
	CDC *pDC = GetDC(); // 获得客户区DC对象
	pDC->TextOut(point.x, point.y, buf); // 输出字符串
	ReleaseDC(pDC); // 释放客户区DC对象
}
