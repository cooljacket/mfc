#pragma once


// CGetParams 对话框

class CGetParams : public CDialog
{
	DECLARE_DYNAMIC(CGetParams)

public:
	CGetParams(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetParams();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GET_PARAMS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int selectedShape;
	virtual BOOL OnInitDialog();
	int penStyle, brushKind, hatchStyle;
	int penSize;
	COLORREF penColor, brushColor;

	afx_msg void OnPaint();
	afx_msg void OnBnClickedPenColor();
	afx_msg void OnBnClickedBrushColor();

public:
	void colorBtn(int ID, COLORREF color);
	//void colorBrushBtn();
};
