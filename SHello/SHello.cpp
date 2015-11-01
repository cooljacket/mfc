#include "shello.h" // WHelloͷ�ļ�

CSHelloApp theApp; // ����Ψһ��CSHelloAppȫ�ֶ���

BOOL CSHelloApp::InitInstance() { // ��ʼ��Ӧ�ó����ʵ��
	m_pMainWnd = new CSHelloFrame(); // ����Ӧ�ó��������ڶ���
	m_pMainWnd->ShowWindow(m_nCmdShow); // ��ʾ������
	m_pMainWnd->UpdateWindow(); // ˢ��������
	return TRUE;
}

BEGIN_MESSAGE_MAP(CSHelloFrame, CFrameWnd) // ��Ϣӳ��
	ON_WM_PAINT()		// ��ͼ��Ϣ
	ON_WM_LBUTTONUP() // �ɿ���������Ϣ
END_MESSAGE_MAP()

CSHelloFrame::CSHelloFrame() { // �����Ĺ��캯��
							   // ��������ָ��=NULL��ʹ��CFrameWnd���Ĭ������
	Create(NULL, L"SHello Application"); // ������ܴ���
}

void CSHelloFrame::OnPaint() { // ��ͼ��������ӦPAINT��Ϣ��
	CPaintDC dc(this); // ������ͼDC����
	dc.TextOut(0, 0, "Hello, World!"); // д�ı���
}

// �����Ӧ��������ӦLBUTTONUP��Ϣ��
void CSHelloFrame::OnLButtonUp(UINT nFlags, CPoint point) {
	char buf[40]; // �����ַ���������
				  // ����Hello�ı�����굱ǰλ��������ַ�����
	sprintf_s(buf, 40, "Hello! (%d, %d)", point.x, point.y);
	CDC *pDC = GetDC(); // ��ÿͻ���DC����
	pDC->TextOut(point.x, point.y, buf); // ����ַ���
	ReleaseDC(pDC); // �ͷſͻ���DC����
}
