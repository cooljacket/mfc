
// PInfoDlg.h : ͷ�ļ�
//

#pragma once


// CPInfoDlg �Ի���
class CPInfoDlg : public CDialog
{
// ����
public:
	CPInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGame();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedPlayIt();


public:
	CProgressCtrl *pch;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
