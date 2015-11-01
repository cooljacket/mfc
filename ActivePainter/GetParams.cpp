// GetParams.cpp : 实现文件
//

#include "stdafx.h"
#include "ActivePainter.h"
#include "GetParams.h"
#include "afxdialogex.h"


// CGetParams 对话框

IMPLEMENT_DYNAMIC(CGetParams, CDialog)

CGetParams::CGetParams(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GET_PARAMS, pParent)
	, selectedShape(0)
	, penStyle(0)
	, penSize(0)
	, hatchStyle(0)
	, brushKind(1)
{
}

CGetParams::~CGetParams()
{
}

void CGetParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_GET_SHAPE, selectedShape);
	DDV_MinMaxInt(pDX, selectedShape, 0, 5);
	DDX_CBIndex(pDX, IDC_GET_PS, penStyle);
	DDV_MinMaxInt(pDX, penStyle, 0, 6);
	DDX_Text(pDX, IDC_PEN_SIZE, penSize);
	DDV_MinMaxInt(pDX, penSize, 0, 25);
	DDX_Radio(pDX, IDC_BRUSH_NULL, brushKind);
	DDX_CBIndex(pDX, IDC_GET_HATCH, hatchStyle);
	DDV_MinMaxInt(pDX, hatchStyle, 0, 5);
}


BEGIN_MESSAGE_MAP(CGetParams, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PEN_COLOR, &CGetParams::OnBnClickedPenColor)
	ON_BN_CLICKED(IDC_BRUSH_COLOR, &CGetParams::OnBnClickedBrushColor)
END_MESSAGE_MAP()


// CGetParams 消息处理程序


BOOL CGetParams::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_GET_SHAPE);
	pCB->AddString(L"直线");
	pCB->AddString(L"折线");
	pCB->AddString(L"矩形");
	pCB->AddString(L"圆");
	pCB->AddString(L"椭圆");
	pCB->AddString(L"多边形");
	pCB->SetCurSel(0);	//设置默认初始选中的项

	pCB = (CComboBox*)GetDlgItem(IDC_GET_PS);
	pCB->AddString(L"实线");
	pCB->AddString(L"虚线");
	pCB->AddString(L"点线");
	pCB->AddString(L"虚点线");
	pCB->AddString(L"虚点点线");
	pCB->AddString(L"空笔");
	pCB->AddString(L"框内");
	pCB->SetCurSel(0);	//设置默认初始选中的项

	pCB = (CComboBox*)GetDlgItem(IDC_GET_HATCH);
	pCB->AddString(L"水平线");
	pCB->AddString(L"垂直线");
	pCB->AddString(L"正斜线");
	pCB->AddString(L"反斜线");
	pCB->AddString(L"十字线");
	pCB->AddString(L"斜十字线");
	pCB->SetCurSel(0);	//设置默认初始选中的项

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGetParams::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()

	colorBtn(IDC_PEN_COLOR, penColor);
	colorBtn(IDC_BRUSH_COLOR, brushColor);
	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_GET_SHAPE);
	pCB->SetCurSel(selectedShape);	//设置默认初始选中的项
	pCB = (CComboBox*)GetDlgItem(IDC_GET_PS);
	pCB->SetCurSel(penStyle);
	pCB = (CComboBox*)GetDlgItem(IDC_GET_HATCH);
	pCB->SetCurSel(hatchStyle);

	CheckRadioButton(IDC_BRUSH_NULL, IDC_BRUSH_HATCH, IDC_BRUSH_NULL+brushKind);
}


void CGetParams::OnBnClickedPenColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(penColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		penColor = colDlg.GetColor();
		colorBtn(IDC_PEN_COLOR, penColor);
	}
}


void CGetParams::OnBnClickedBrushColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(brushColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		brushColor = colDlg.GetColor();
		colorBtn(IDC_BRUSH_COLOR, brushColor);
	}
}

void CGetParams::colorBtn(int ID, COLORREF color) {
	CWnd* pWnd = GetDlgItem(ID); // 获取控件的窗口对象
	CDC* pDC = pWnd->GetDC(); // 获取控件的DC对象
	CRect rect; // 定义矩形对象
	pWnd->GetClientRect(&rect); // 获取控件窗口（客户区的）矩形
	CBrush brush(color);  // 定义并创建刷对象(m_crCol为颜色型类变量)
	pWnd->Invalidate(); // 使控件窗口无效
	pWnd->UpdateWindow(); // 更新控件窗口 
	pDC->FillRect(&rect, &brush); // 在按钮控件上绘制填充矩形
}

//void CGetParams::colorBrushBtn() {
//	CWnd* pWnd = GetDlgItem(IDC_BRUSH_COLOR); // 获取控件的窗口对象
//	CDC* pDC = pWnd->GetDC(); // 获取控件的DC对象
//	CRect rect; // 定义矩形对象
//	pWnd->GetClientRect(&rect); // 获取控件窗口（客户区的）矩形
//	CBrush brush(brushColor);  // 定义并创建刷对象(m_crCol为颜色型类变量)
//	pWnd->Invalidate(); // 使控件窗口无效
//	pWnd->UpdateWindow(); // 更新控件窗口 
//	pDC->FillRect(&rect, &brush); // 在按钮控件上绘制填充矩形
//}