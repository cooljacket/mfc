
// ActivePainterView.cpp : CActivePainterView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CActivePainterView 构造/析构

CActivePainterView::CActivePainterView()
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown = FALSE;			// 设左鼠标键按下为假
	m_bDrawing = FALSE;				// 设正在画图为加
	m_bErase = FALSE;				// 设需要擦除为假
	lineColor = RGB(0, 255, 0);		// 默认线的颜色为绿色
	fillColor = RGB(255, 0, 0);		// 默认填充颜色为红色
	BK_Color = RGB(255, 0, 0);		// 默认背景颜色为白色
	penStyle = PS_SOLID;			// 默认线的种类为实线
	penSize = 1;					// 默认线的粗细

	pDotPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // 创建灰色点线笔
	pLinePen = new CPen(penStyle, penSize, lineColor); // 创建直线笔
	brush = new CBrush(fillColor);				// 创建默认的实心刷
	shape = LINE;	// 默认形状为画直线
	brushKind = 1;	// 默认条纹风格为实心
}

CActivePainterView::~CActivePainterView()
{
}

BOOL CActivePainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CActivePainterView 绘制

void CActivePainterView::OnDraw(CDC* pDC)
{
	CActivePainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->SetBkColor(BK_Color);
}


// CActivePainterView 打印

BOOL CActivePainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CActivePainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CActivePainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CActivePainterView 诊断

#ifdef _DEBUG
void CActivePainterView::AssertValid() const
{
	CView::AssertValid();
}

void CActivePainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CActivePainterDoc* CActivePainterView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CActivePainterDoc)));
	return (CActivePainterDoc*)m_pDocument;
}
#endif //_DEBUG


// CActivePainterView 消息处理程序


void CActivePainterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture(); // 设置鼠标捕获
	m_bLButtonDown = TRUE; // 设左鼠标键按下为真
	if (shape == CURVE || shape == POLYGEN)
		m_bDrawing = TRUE;	// 
	p0 = point; // 保存直线的起点
	pm = p0; // 让直线的终点等于起点

	CView::OnLButtonDown(nFlags, point);
}


void CActivePainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(LoadCursor(NULL, IDC_CROSS)); // 设置鼠标为十字
	CDC* pDC = GetDC();			// 获取设备上下文
	pDC->SelectObject(pDotPen); // 选取灰色点线笔
	pDC->SetROP2(R2_XORPEN);	// 设置为异或绘图方式
	pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
								 //pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
								 // 用于动态画封闭图形（如矩形、椭圆等）
	pDC->SelectObject(brush);	// 选取刷笔

	switch (shape) {
	case LINE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				//pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线
				DrawLine(pDC, p0, pm); // 擦除原直线
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真

			DrawLine(pDC, p0, pm = point);	// 绘制新直线，更新老终点
		}

	} break;
	case RECTANGLE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				DrawRectangle(pDC, p0, pm); // 擦除原矩形
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真

			DrawRectangle(pDC, p0, pm = point);	// 绘制新矩形，更新老的右下角的点
		}
	} break;
	case CURVE: 
	case POLYGEN: {
		if (m_bDrawing) {
			if (m_bErase) {// 需要擦除为真 
				DrawLine(pDC, p0, pm);
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真
			DrawLine(pDC, p0, pm = point);	// 绘制新直线，更新老终点
		}

	} break;
	case CIRCLE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				double x = pm.x - p0.x;
				double y = pm.y - p0.y;
				double r = sqrt(x*x + y*y);
				DrawCircle(pDC, p0, r); // 擦除原来的圆
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真

			double x = point.x - p0.x;
			double y = point.y - p0.y;
			double r = sqrt(x*x + y*y);
			DrawCircle(pDC, p0, r); // 绘制新的圆
			pm = point;
		}
	}break;
	case ELLIPSE: {
		if (m_bLButtonDown) {
			if (m_bErase) {
				DrawEllipse(pDC, p0, pm); // 擦除原来的椭圆
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真

			DrawEllipse(pDC, p0, pm=point); // 绘制新的椭圆
		}
	} break;
	default:
		break;
	}

	ReleaseDC(pDC); // 释放设备上下文

	// 设置状态条的显示信息
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture(); // 释放鼠标捕获
	if (m_bLButtonDown) { // 左鼠标键按下为真
		CDC* pDC = GetDC(); // 获取设备上下文
		pDC->SelectObject(pDotPen); // 选入灰色点线笔
		pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
									 // pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
									 // 用于动态画封闭图形（如矩形、椭圆等）
		pDC->SelectObject(brush);	// 选取刷笔

		//delete brush;
		//brush = new CBrush(fillColor);
		pDC->SelectObject(brush);	// 设置填充色

		switch (shape)
		{
		case LINE: {
			DrawLine(pDC, p0, pm);
			pDC->SelectObject(pLinePen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
			DrawLine(pDC, p0, pm = point);	// 绘制最终的直线
		} break;
		case RECTANGLE: {
			DrawRectangle(pDC, p0, pm);
			pDC->SelectObject(pLinePen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
			DrawRectangle(pDC, p0, pm = point);	// 绘制最终的矩形
		} break;
		case CURVE: 
		case POLYGEN: {
			size_t size = pointArray.size();
			if (size >= 1)
				DrawLine(pDC, pointArray[size-1], point);	// 擦除原直线
			pDC->SelectObject(pLinePen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
			pointArray.push_back(point);
			size = pointArray.size();
			if (size >= 2)
				DrawLine(pDC, pointArray[size - 2], pointArray[size - 1]);	// 绘制下一段直线
			else
				DrawLine(pDC, point, point);	// 绘制起点
		} break;
		case CIRCLE: {
			double x = pm.x - p0.x;
			double y = pm.y - p0.y;
			double r = sqrt(x*x + y*y);
			DrawCircle(pDC, p0, r);		// 擦除原来的圆
			pDC->SelectObject(pLinePen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN);	// 设置为覆盖绘图方式

			x = point.x - p0.x;
			y = point.y - p0.y;
			r = sqrt(x*x + y*y);
			DrawCircle(pDC, p0, r); // 绘制新的圆
		} break;
		case ELLIPSE: {
			DrawEllipse(pDC, p0, pm); // 擦除原来的椭圆
			pDC->SelectObject(pLinePen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
			DrawEllipse(pDC, p0, pm = point); // 绘制新的椭圆
		} break;
		default:
			break;
		}

		m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
		m_bErase = FALSE; // 重需要擦除为假
		ReleaseDC(pDC); // 释放设备上下文
	}

	CView::OnLButtonUp(nFlags, point);
}


void CActivePainterView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CActivePainterView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (shape == POLYGEN && pointArray.size() >= 2) {
		CDC* pDC = GetDC();			// 获取设备上下文
		pDC->SelectObject(pDotPen); // 选取灰色点线笔
		pDC->SelectObject(brush);	// 选取刷笔
		pDC->SetROP2(R2_XORPEN);	// 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式

		//delete brush;
		//brush = new CBrush(fillColor);
		pDC->SelectObject(brush);	// 设置填充色
		DrawLine(pDC, p0, pm);

		pDC->SelectObject(pLinePen); // 选择直线笔
		pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
		pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
		//DrawLine(pDC, pointArray[0], pointArray[pointArray.size() - 1]);	// 绘制最终的直线
		// 因为要填充，而自己画的那个不能填充，所以还是改回用Polygon函数来画
		pDC->Polygon(GetPointsArray(), pointArray.size());
		ReleaseDC(pDC); // 释放设备上下文
	}
	if (shape == CURVE) {
		CDC* pDC = GetDC(); // 获取设备上下文
		pDC->SelectObject(pDotPen); // 选入灰色点线笔
		pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
		DrawLine(pDC, p0, pm);
		ReleaseDC(pDC); // 释放设备上下文
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	shape = CURVE;
}


void CActivePainterView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	shape = LINE;
}


void CActivePainterView::OnPolygen()
{
	// TODO: 在此添加命令处理程序代码
	shape = POLYGEN;
}


void CActivePainterView::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	shape = RECTANGLE;
}


void CActivePainterView::OnCircle()
{
	// TODO: 在此添加命令处理程序代码
	shape = CIRCLE;
}


void CActivePainterView::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	shape = ELLIPSE;
}


void CActivePainterView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_SOLID);
}


void CActivePainterView::OnPsDash()
{
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_DASH);
}


void CActivePainterView::OnPsDot()
{
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_DOT);
}


void CActivePainterView::OnPsDashdot()
{
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_DASHDOT);
}


void CActivePainterView::OnPsDashdotdot()
{
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_DASHDOTDOT);
}


void CActivePainterView::OnPsNull()
{
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_NULL);
}


void CActivePainterView::OnPsInsideframe()
{
	// TODO: 在此添加命令处理程序代码
	SetPenStyle(PS_INSIDEFRAME);
}


void CActivePainterView::OnUpdatePsSolid(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	//Invalidate(); UpdateWindow( );
	RedrawWindow();
}

