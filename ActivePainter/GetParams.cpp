// GetParams.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ActivePainter.h"
#include "GetParams.h"
#include "afxdialogex.h"


// CGetParams �Ի���

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


// CGetParams ��Ϣ�������


BOOL CGetParams::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_GET_SHAPE);
	pCB->AddString(L"ֱ��");
	pCB->AddString(L"����");
	pCB->AddString(L"����");
	pCB->AddString(L"Բ");
	pCB->AddString(L"��Բ");
	pCB->AddString(L"�����");
	pCB->SetCurSel(0);	//����Ĭ�ϳ�ʼѡ�е���

	pCB = (CComboBox*)GetDlgItem(IDC_GET_PS);
	pCB->AddString(L"ʵ��");
	pCB->AddString(L"����");
	pCB->AddString(L"����");
	pCB->AddString(L"�����");
	pCB->AddString(L"������");
	pCB->AddString(L"�ձ�");
	pCB->AddString(L"����");
	pCB->SetCurSel(0);	//����Ĭ�ϳ�ʼѡ�е���

	pCB = (CComboBox*)GetDlgItem(IDC_GET_HATCH);
	pCB->AddString(L"ˮƽ��");
	pCB->AddString(L"��ֱ��");
	pCB->AddString(L"��б��");
	pCB->AddString(L"��б��");
	pCB->AddString(L"ʮ����");
	pCB->AddString(L"бʮ����");
	pCB->SetCurSel(0);	//����Ĭ�ϳ�ʼѡ�е���

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGetParams::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	colorBtn(IDC_PEN_COLOR, penColor);
	colorBtn(IDC_BRUSH_COLOR, brushColor);
	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_GET_SHAPE);
	pCB->SetCurSel(selectedShape);	//����Ĭ�ϳ�ʼѡ�е���
	pCB = (CComboBox*)GetDlgItem(IDC_GET_PS);
	pCB->SetCurSel(penStyle);
	pCB = (CComboBox*)GetDlgItem(IDC_GET_HATCH);
	pCB->SetCurSel(hatchStyle);

	CheckRadioButton(IDC_BRUSH_NULL, IDC_BRUSH_HATCH, IDC_BRUSH_NULL+brushKind);
}


void CGetParams::OnBnClickedPenColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog colDlg(penColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		penColor = colDlg.GetColor();
		colorBtn(IDC_PEN_COLOR, penColor);
	}
}


void CGetParams::OnBnClickedBrushColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog colDlg(brushColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		brushColor = colDlg.GetColor();
		colorBtn(IDC_BRUSH_COLOR, brushColor);
	}
}

void CGetParams::colorBtn(int ID, COLORREF color) {
	CWnd* pWnd = GetDlgItem(ID); // ��ȡ�ؼ��Ĵ��ڶ���
	CDC* pDC = pWnd->GetDC(); // ��ȡ�ؼ���DC����
	CRect rect; // ������ζ���
	pWnd->GetClientRect(&rect); // ��ȡ�ؼ����ڣ��ͻ����ģ�����
	CBrush brush(color);  // ���岢����ˢ����(m_crColΪ��ɫ�������)
	pWnd->Invalidate(); // ʹ�ؼ�������Ч
	pWnd->UpdateWindow(); // ���¿ؼ����� 
	pDC->FillRect(&rect, &brush); // �ڰ�ť�ؼ��ϻ���������
}

//void CGetParams::colorBrushBtn() {
//	CWnd* pWnd = GetDlgItem(IDC_BRUSH_COLOR); // ��ȡ�ؼ��Ĵ��ڶ���
//	CDC* pDC = pWnd->GetDC(); // ��ȡ�ؼ���DC����
//	CRect rect; // ������ζ���
//	pWnd->GetClientRect(&rect); // ��ȡ�ؼ����ڣ��ͻ����ģ�����
//	CBrush brush(brushColor);  // ���岢����ˢ����(m_crColΪ��ɫ�������)
//	pWnd->Invalidate(); // ʹ�ؼ�������Ч
//	pWnd->UpdateWindow(); // ���¿ؼ����� 
//	pDC->FillRect(&rect, &brush); // �ڰ�ť�ؼ��ϻ���������
//}