#include <afxwin.h> // MFCͷ�ļ�

class CSHelloApp : public CWinApp { // Ӧ�ó�����
public:
	virtual BOOL InitInstance(); // ��ʼ��ʵ���麯��
};

class CSHelloFrame : public CFrameWnd { // ��ܴ�����
public:
	CSHelloFrame(); // ���캯��
protected:
	afx_msg void OnPaint(); // ��ͼ��Ӧ����
							// �����Ӧ������
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP() // ������Ϣӳ��
};