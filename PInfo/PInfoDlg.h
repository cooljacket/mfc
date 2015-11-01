
// PInfoDlg.h : 头文件
//

#pragma once


// CPInfoDlg 对话框
class CPInfoDlg : public CDialog
{
// 构造
public:
	CPInfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
