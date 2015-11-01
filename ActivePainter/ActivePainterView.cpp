
// ActivePainterView.cpp : CActivePainterView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ActivePainter.h"
#endif

#include "ActivePainterDoc.h"
#include "ActivePainterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <cmath>
#include "GetParams.h"
#include "resource.h"
#include "MainFrm.h"

// CActivePainterView

IMPLEMENT_DYNCREATE(CActivePainterView, CView)

BEGIN_MESSAGE_MAP(CActivePainterView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SETTING, &CActivePainterView::OnSetting)
	ON_COMMAND(ID_CURVE, &CActivePainterView::OnCurve)
	ON_COMMAND(ID_LINE, &CActivePainterView::OnLine)
	ON_COMMAND(ID_POLYGEN, &CActivePainterView::OnPolygen)
	ON_COMMAND(ID_RECTANGLE, &CActivePainterView::OnRectangle)
	ON_COMMAND(ID_CIRCLE, &CActivePainterView::OnCircle)
	ON_COMMAND(ID_ELLIPSE, &CActivePainterView::OnEllipse)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CActivePainterView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_CURVE, &CActivePainterView::OnUpdateCurve)
	ON_UPDATE_COMMAND_UI(ID_POLYGEN, &CActivePainterView::OnUpdatePolygen)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CActivePainterView::OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, &CActivePainterView::OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CActivePainterView::OnUpdateEllipse)
	ON_COMMAND(ID_PS_SOLID, &CActivePainterView::OnPsSolid)
	ON_COMMAND(ID_PS_DASH, &CActivePainterView::OnPsDash)
	ON_COMMAND(ID_PS_DOT, &CActivePainterView::OnPsDot)
	ON_COMMAND(ID_PS_DASHDOT, &CActivePainterView::OnPsDashdot)
	ON_COMMAND(ID_PS_DASHDOTDOT, &CActivePainterView::OnPsDashdotdot)
	ON_COMMAND(ID_PS_NULL, &CActivePainterView::OnPsNull)
	ON_COMMAND(ID_PS_INSIDEFRAME, &CActivePainterView::OnPsInsideframe)
	ON_UPDATE_COMMAND_UI(ID_PS_SOLID, &CActivePainterView::OnUpdatePsSolid)
	ON_UPDATE_COMMAND_UI(ID_PS_DASH, &CActivePainterView::OnUpdatePsDash)
	ON_UPDATE_COMMAND_UI(ID_PS_DOT, &CActivePainterView::OnUpdatePsDot)
	ON_UPDATE_COMMAND_UI(ID_PS_DASHDOT, &CActivePainterView::OnUpdatePsDashdot)
	ON_UPDATE_COMMAND_UI(ID_PS_DASHDOTDOT, &CActivePainterView::OnUpdatePsDashdotdot)
	ON_UPDATE_COMMAND_UI(ID_PS_NULL, &CActivePainterView::OnUpdatePsNull)
	ON_UPDATE_COMMAND_UI(ID_PS_INSIDEFRAME, &CActivePainterView::OnUpdatePsInsideframe)
	ON_COMMAND(ID_CLEAR, &CActivePainterView::OnClear)
END_MESSAGE_MAP()

// CActivePainterView ����/����

CActivePainterView::CActivePainterView()
{
	// TODO: �ڴ˴���ӹ������
	m_bLButtonDown = FALSE;			// ������������Ϊ��
	m_bDrawing = FALSE;				// �����ڻ�ͼΪ��
	m_bErase = FALSE;				// ����Ҫ����Ϊ��
	lineColor = RGB(0, 255, 0);		// Ĭ���ߵ���ɫΪ��ɫ
	fillColor = RGB(255, 0, 0);		// Ĭ�������ɫΪ��ɫ
	BK_Color = RGB(255, 0, 0);		// Ĭ�ϱ�����ɫΪ��ɫ
	penStyle = PS_SOLID;			// Ĭ���ߵ�����Ϊʵ��
	penSize = 1;					// Ĭ���ߵĴ�ϸ

	pDotPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // ������ɫ���߱�
	pLinePen = new CPen(penStyle, penSize, lineColor); // ����ֱ�߱�
	brush = new CBrush(fillColor);				// ����Ĭ�ϵ�ʵ��ˢ
	shape = LINE;	// Ĭ����״Ϊ��ֱ��
	brushKind = 1;	// Ĭ�����Ʒ��Ϊʵ��
}

CActivePainterView::~CActivePainterView()
{
}

BOOL CActivePainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CActivePainterView ����

void CActivePainterView::OnDraw(CDC* pDC)
{
	CActivePainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->SetBkColor(BK_Color);
}


// CActivePainterView ��ӡ

BOOL CActivePainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CActivePainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CActivePainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CActivePainterView ���

#ifdef _DEBUG
void CActivePainterView::AssertValid() const
{
	CView::AssertValid();
}

void CActivePainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CActivePainterDoc* CActivePainterView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CActivePainterDoc)));
	return (CActivePainterDoc*)m_pDocument;
}
#endif //_DEBUG


// CActivePainterView ��Ϣ�������


void CActivePainterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCapture(); // ������겶��
	m_bLButtonDown = TRUE; // ������������Ϊ��
	if (shape == CURVE || shape == POLYGEN)
		m_bDrawing = TRUE;	// 
	p0 = point; // ����ֱ�ߵ����
	pm = p0; // ��ֱ�ߵ��յ�������

	CView::OnLButtonDown(nFlags, point);
}


void CActivePainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCursor(LoadCursor(NULL, IDC_CROSS)); // �������Ϊʮ��
	CDC* pDC = GetDC();			// ��ȡ�豸������
	pDC->SelectObject(pDotPen); // ѡȡ��ɫ���߱�
	pDC->SetROP2(R2_XORPEN);	// ����Ϊ����ͼ��ʽ
	pDC->SetBkMode(TRANSPARENT); // ����͸������ģʽ
								 //pDC->SelectStockObject(NULL_BRUSH); // ѡ���ˢ
								 // ���ڶ�̬�����ͼ�Σ�����Ρ���Բ�ȣ�
	pDC->SelectObject(brush);	// ѡȡˢ��

	switch (shape) {
	case LINE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				//pDC->MoveTo(p0); pDC->LineTo(pm); // ����ԭֱ��
				DrawLine(pDC, p0, pm); // ����ԭֱ��
			}
			else // ��Ҫ����Ϊ��
				m_bErase = TRUE; // ����Ҫ����Ϊ��

			DrawLine(pDC, p0, pm = point);	// ������ֱ�ߣ��������յ�
		}

	} break;
	case RECTANGLE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				DrawRectangle(pDC, p0, pm); // ����ԭ����
			}
			else // ��Ҫ����Ϊ��
				m_bErase = TRUE; // ����Ҫ����Ϊ��

			DrawRectangle(pDC, p0, pm = point);	// �����¾��Σ������ϵ����½ǵĵ�
		}
	} break;
	case CURVE: 
	case POLYGEN: {
		if (m_bDrawing) {
			if (m_bErase) {// ��Ҫ����Ϊ�� 
				DrawLine(pDC, p0, pm);
			}
			else // ��Ҫ����Ϊ��
				m_bErase = TRUE; // ����Ҫ����Ϊ��
			DrawLine(pDC, p0, pm = point);	// ������ֱ�ߣ��������յ�
		}

	} break;
	case CIRCLE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				double x = pm.x - p0.x;
				double y = pm.y - p0.y;
				double r = sqrt(x*x + y*y);
				DrawCircle(pDC, p0, r); // ����ԭ����Բ
			}
			else // ��Ҫ����Ϊ��
				m_bErase = TRUE; // ����Ҫ����Ϊ��

			double x = point.x - p0.x;
			double y = point.y - p0.y;
			double r = sqrt(x*x + y*y);
			DrawCircle(pDC, p0, r); // �����µ�Բ
			pm = point;
		}
	}break;
	case ELLIPSE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				DrawEllipse(pDC, p0, pm); // ����ԭ������Բ
			}
			else // ��Ҫ����Ϊ��
				m_bErase = TRUE; // ����Ҫ����Ϊ��

			DrawEllipse(pDC, p0, pm=point); // �����µ���Բ
		}
	} break;
	default:
		break;
	}

	ReleaseDC(pDC); // �ͷ��豸������

	// ����״̬������ʾ��Ϣ
	wchar_t buf[20];
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	_itow_s(point.x, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->xVal, buf);
	_itow_s(point.y, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->yVal, buf);
	if (shape == RECTANGLE) {
		int area = abs(pm.x - p0.x) * abs(pm.y - p0.y);
		_itow_s(area, buf, 20, 10);
		pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->area, buf);
	}


	CView::OnMouseMove(nFlags, point);
}


void CActivePainterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ReleaseCapture(); // �ͷ���겶��
	if (m_bLButtonDown) { // ����������Ϊ��
		CDC* pDC = GetDC(); // ��ȡ�豸������
		pDC->SelectObject(pDotPen); // ѡ���ɫ���߱�
		pDC->SetROP2(R2_XORPEN); // ����Ϊ����ͼ��ʽ
		pDC->SetBkMode(TRANSPARENT); // ����͸������ģʽ
									 // pDC->SelectStockObject(NULL_BRUSH); // ѡ���ˢ
									 // ���ڶ�̬�����ͼ�Σ�����Ρ���Բ�ȣ�
		pDC->SelectObject(brush);	// ѡȡˢ��

		//delete brush;
		//brush = new CBrush(fillColor);
		pDC->SelectObject(brush);	// �������ɫ

		switch (shape)
		{
		case LINE: {
			DrawLine(pDC, p0, pm);
			pDC->SelectObject(pLinePen); // ѡ��ֱ�߱�
			pDC->SetROP2(R2_COPYPEN); // ����Ϊ���ǻ�ͼ��ʽ
			DrawLine(pDC, p0, pm = point);	// �������յ�ֱ��
		} break;
		case RECTANGLE: {
			DrawRectangle(pDC, p0, pm);
			pDC->SelectObject(pLinePen); // ѡ��ֱ�߱�
			pDC->SetROP2(R2_COPYPEN); // ����Ϊ���ǻ�ͼ��ʽ
			DrawRectangle(pDC, p0, pm = point);	// �������յľ���
		} break;
		case CURVE: 
		case POLYGEN: {
			size_t size = pointArray.size();
			if (size >= 1)
				DrawLine(pDC, pointArray[size-1], point);	// ����ԭֱ��
			pDC->SelectObject(pLinePen); // ѡ��ֱ�߱�
			pDC->SetROP2(R2_COPYPEN); // ����Ϊ���ǻ�ͼ��ʽ
			pointArray.push_back(point);
			size = pointArray.size();
			if (size >= 2)
				DrawLine(pDC, pointArray[size - 2], pointArray[size - 1]);	// ������һ��ֱ��
			else
				DrawLine(pDC, point, point);	// �������
		} break;
		case CIRCLE: {
			double x = pm.x - p0.x;
			double y = pm.y - p0.y;
			double r = sqrt(x*x + y*y);
			DrawCircle(pDC, p0, r);		// ����ԭ����Բ
			pDC->SelectObject(pLinePen); // ѡ��ֱ�߱�
			pDC->SetROP2(R2_COPYPEN);	// ����Ϊ���ǻ�ͼ��ʽ

			x = point.x - p0.x;
			y = point.y - p0.y;
			r = sqrt(x*x + y*y);
			DrawCircle(pDC, p0, r); // �����µ�Բ
		} break;
		case ELLIPSE: {
			DrawEllipse(pDC, p0, pm); // ����ԭ������Բ
			pDC->SelectObject(pLinePen); // ѡ��ֱ�߱�
			pDC->SetROP2(R2_COPYPEN); // ����Ϊ���ǻ�ͼ��ʽ
			DrawEllipse(pDC, p0, pm = point); // �����µ���Բ
		} break;
		default:
			break;
		}

		m_bLButtonDown = FALSE; // ��������������Ϊ��
		m_bErase = FALSE; // ����Ҫ����Ϊ��
		ReleaseDC(pDC); // �ͷ��豸������
	}

	CView::OnLButtonUp(nFlags, point);
}


void CActivePainterView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CActivePainterView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (shape == POLYGEN && pointArray.size() >= 2) {
		CDC* pDC = GetDC();			// ��ȡ�豸������
		pDC->SelectObject(pDotPen); // ѡȡ��ɫ���߱�
		pDC->SelectObject(brush);	// ѡȡˢ��
		pDC->SetROP2(R2_XORPEN);	// ����Ϊ����ͼ��ʽ
		pDC->SetBkMode(TRANSPARENT); // ����͸������ģʽ

		//delete brush;
		//brush = new CBrush(fillColor);
		pDC->SelectObject(brush);	// �������ɫ
		DrawLine(pDC, p0, pm);

		pDC->SelectObject(pLinePen); // ѡ��ֱ�߱�
		pDC->SetROP2(R2_COPYPEN); // ����Ϊ���ǻ�ͼ��ʽ
		pDC->SetBkMode(TRANSPARENT); // ����͸������ģʽ
		//DrawLine(pDC, pointArray[0], pointArray[pointArray.size() - 1]);	// �������յ�ֱ��
		// ��ΪҪ��䣬���Լ������Ǹ�������䣬���Ի��ǸĻ���Polygon��������
		pDC->Polygon(GetPointsArray(), pointArray.size());
		ReleaseDC(pDC); // �ͷ��豸������
	}
	if (shape == CURVE) {
		CDC* pDC = GetDC(); // ��ȡ�豸������
		pDC->SelectObject(pDotPen); // ѡ���ɫ���߱�
		pDC->SetROP2(R2_XORPEN); // ����Ϊ����ͼ��ʽ
		pDC->SetBkMode(TRANSPARENT); // ����͸������ģʽ
		DrawLine(pDC, p0, pm);
		ReleaseDC(pDC); // �ͷ��豸������
	}
	m_bDrawing = FALSE;
	pointArray.clear();
	CView::OnRButtonDown(nFlags, point);
}


BOOL CActivePainterView::DrawLine(CDC* pDC, const POINT& beg, const POINT& end) {
	pDC->MoveTo(beg);
	return pDC->LineTo(end);
}


BOOL CActivePainterView::DrawCircle(CDC* pDC, const POINT& origin, double r) {
	return pDC->Ellipse(origin.x - r, origin.y - r, origin.x + r, origin.y + r);
}


LPPOINT CActivePainterView::GetPointsArray() {
	LPPOINT points = new POINT[pointArray.size()];
	for (int i = 0; i < pointArray.size(); ++i)
		points[i] = pointArray[i];
	return points;
}


BOOL  CActivePainterView::DrawRectangle(CDC* pDC, const POINT& LeftTop, const POINT& RightButtom) {
	return pDC->Rectangle(LeftTop.x, LeftTop.y, RightButtom.x, RightButtom.y);
}


BOOL CActivePainterView::DrawEllipse(CDC* pDC, const POINT& LeftTop, const POINT& RightButtom) {
	return pDC->Ellipse(LeftTop.x, LeftTop.y, RightButtom.x, RightButtom.y);
}


void CActivePainterView::SetPenStyle(int pStyle) {
	penStyle = pStyle;
	pLinePen->DeleteObject();
	pLinePen->CreatePen(penStyle, penSize, lineColor);
}


void CActivePainterView::OnSetting()
{
	// TODO: �ڴ���������������
	CGetParams dlg;
	dlg.penColor = lineColor;
	dlg.brushColor = fillColor;
	dlg.penSize = penSize;

	dlg.selectedShape = shape;
	dlg.penStyle = penStyle;
	dlg.hatchStyle = hatchStyle;
	dlg.brushKind = brushKind;


	if (dlg.DoModal() == IDOK) {
		shape = Shape(dlg.selectedShape);
		penSize = dlg.penSize;
		lineColor = dlg.penColor;
		fillColor = dlg.brushColor;
		hatchStyle = dlg.hatchStyle;
		SetPenStyle(dlg.penStyle);
		
		//delete brush;
		brushKind = dlg.brushKind;
		if (brushKind == 0)
			brush = new CBrush();
		else if (brushKind == 1)
			brush = new CBrush(fillColor);
		else if (brushKind == 2)
			brush = new CBrush(hatchStyle, fillColor);
	}
}


void CActivePainterView::OnCurve()
{
	// TODO: �ڴ���������������
	shape = CURVE;
}


void CActivePainterView::OnLine()
{
	// TODO: �ڴ���������������
	shape = LINE;
}


void CActivePainterView::OnPolygen()
{
	// TODO: �ڴ���������������
	shape = POLYGEN;
}


void CActivePainterView::OnRectangle()
{
	// TODO: �ڴ���������������
	shape = RECTANGLE;
}


void CActivePainterView::OnCircle()
{
	// TODO: �ڴ���������������
	shape = CIRCLE;
}


void CActivePainterView::OnEllipse()
{
	// TODO: �ڴ���������������
	shape = ELLIPSE;
}


void CActivePainterView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (shape == LINE) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdateCurve(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (shape == CURVE) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePolygen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (shape == POLYGEN) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (shape == RECTANGLE) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdateCircle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (shape == CIRCLE) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (shape == ELLIPSE) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnPsSolid()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_SOLID);
}


void CActivePainterView::OnPsDash()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_DASH);
}


void CActivePainterView::OnPsDot()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_DOT);
}


void CActivePainterView::OnPsDashdot()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_DASHDOT);
}


void CActivePainterView::OnPsDashdotdot()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_DASHDOTDOT);
}


void CActivePainterView::OnPsNull()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_NULL);
}


void CActivePainterView::OnPsInsideframe()
{
	// TODO: �ڴ���������������
	SetPenStyle(PS_INSIDEFRAME);
}


void CActivePainterView::OnUpdatePsSolid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == PS_SOLID) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePsDash(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == PS_DASH) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePsDot(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == PS_DOT) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePsDashdot(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == PS_DASHDOT) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePsDashdotdot(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == ID_PS_DASHDOTDOT) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePsNull(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == PS_NULL) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnUpdatePsInsideframe(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (penStyle == PS_INSIDEFRAME) {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(0);
	}
}


void CActivePainterView::OnClear()
{
	// TODO: �ڴ���������������
	//Invalidate(); UpdateWindow( );
	RedrawWindow();
}

