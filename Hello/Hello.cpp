// Hello.cpp
#include <afxwin.h> // MFCͷ�ļ�

class CHelloApp : public CWinApp { // Ӧ�ó�����
	virtual BOOL InitInstance(); // ��ʼ��ʵ���麯��
};

BOOL CHelloApp::InitInstance() { // ��ʼ��Ӧ�ó���ʵ���ĳ�Ա����
	CFrameWnd *pFrmWnd = new CFrameWnd(); // ������ܴ��ڶ���
	pFrmWnd->Create(NULL, L"Hello world!"); // ������ܴ���
	m_pMainWnd = pFrmWnd; // ���ÿ�ܴ�����ΪӦ�ó����������
	pFrmWnd->ShowWindow(m_nCmdShow); // ��ʾ������
	return TRUE;
}

CHelloApp theApp; // Ψһ��CSHelloAppȫ�ֶ���
				  // ? main ��������������أ���������￪ʼ�����أ�����˵������һ��CS app��������൱�����������أ�