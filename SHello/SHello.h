#include <afxwin.h> // MFC头文件

class CSHelloApp : public CWinApp { // 应用程序类
public:
	virtual BOOL InitInstance(); // 初始化实例虚函数
};

class CSHelloFrame : public CFrameWnd { // 框架窗口类
public:
	CSHelloFrame(); // 构造函数
protected:
	afx_msg void OnPaint(); // 绘图响应函数
							// 鼠标响应函数：
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP() // 声明消息映射
};