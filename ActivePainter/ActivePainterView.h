
// ActivePainterView.h : CActivePainterView 类的接口
//

#pragma once
#include <vector>
using namespace std;

class CActivePainterView : public CView
{
protected: // 仅从序列化创建
	CActivePainterView();
	DECLARE_DYNCREATE(CActivePainterView)

// 特性
public:
	CActivePainterDoc* GetDocument() const;
	BOOL m_bLButtonDown, // 判断是否按下左鼠标键
		m_bErase, // 是否需要擦除图形
		m_bDrawing;	// 是否正在绘画状态中，供画曲线，多边形等使用
	CPoint p0, pm; // 记录直线起点和动态终点
	CPen *pDotPen, *pLinePen; // 定义灰色和直线笔的对象指针
	CBrush* brush;
	vector<POINT> pointArray;

	// 以下为绘图的各种参数
	enum Shape
	{
		LINE, CURVE, RECTANGLE, CIRCLE, ELLIPSE, POLYGEN
	} shape;
	COLORREF lineColor, fillColor, BK_Color;
	int penStyle, penSize, brushKind, hatchStyle;
	/*enum BrushKind
	{
		NONE, SOLID, HATCH
	} brushKind;*/

// 操作
public:
	BOOL DrawLine(CDC* pDC, const POINT& beg, const POINT& end);
	BOOL DrawCircle(CDC* pDC, const POINT& center, double r);
	BOOL DrawRectangle(CDC* pDC, const POINT& LeftTop, const POINT& RightButtom);
	BOOL DrawEllipse(CDC* pDC, const POINT& LeftTop, const POINT& RightButtom);
	LPPOINT GetPointsArray();
	void SetPenStyle(int pStyle);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CActivePainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetting();
	afx_msg void OnCurve();
	afx_msg void OnLine();
	afx_msg void OnPolygen();
	afx_msg void OnRectangle();
	afx_msg void OnCircle();
	afx_msg void OnEllipse();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCurve(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePolygen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnPsSolid();
	afx_msg void OnPsDash();
	afx_msg void OnPsDot();
	afx_msg void OnPsDashdot();
	afx_msg void OnPsDashdotdot();
	afx_msg void OnPsNull();
	afx_msg void OnPsInsideframe();
	afx_msg void OnUpdatePsSolid(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDash(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDot(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDashdot(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDashdotdot(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsNull(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsInsideframe(CCmdUI *pCmdUI);
	afx_msg void OnClear();
};

#ifndef _DEBUG  // ActivePainterView.cpp 中的调试版本
inline CActivePainterDoc* CActivePainterView::GetDocument() const
   { return reinterpret_cast<CActivePainterDoc*>(m_pDocument); }
#endif

