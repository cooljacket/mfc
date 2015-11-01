
// MFCAnimationWalkthroughView.cpp : CMFCAnimationWalkthroughView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCAnimationWalkthrough.h"
#endif

#include "MFCAnimationWalkthroughDoc.h"
#include "MFCAnimationWalkthroughView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// add 1
static int nAnimationGroup = 0;
static int nInfoAreaHeight = 40;


// CMFCAnimationWalkthroughView

IMPLEMENT_DYNCREATE(CMFCAnimationWalkthroughView, CView)

BEGIN_MESSAGE_MAP(CMFCAnimationWalkthroughView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCAnimationWalkthroughView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ANIMATION_STARTBACKWARD, &CMFCAnimationWalkthroughView::OnAnimationStartbackward)
	ON_COMMAND(ID_ANIMATION_STARTFORWARD, &CMFCAnimationWalkthroughView::OnAnimationStartforward)
	ON_COMMAND(ID_ANIMATION_STOP, &CMFCAnimationWalkthroughView::OnAnimationStop)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCAnimationWalkthroughView 构造/析构

CMFCAnimationWalkthroughView::CMFCAnimationWalkthroughView()
{
	// TODO:  在此处添加构造代码 add 2
	m_bCurrentDirection = TRUE;

	m_animationController.EnableAnimationTimerEventHandler();
    m_animationController.EnablePriorityComparisonHandler(UI_ANIMATION_PHT_TRIM);

    m_animationColor = RGB(255, 255, 255);
    m_animationRect = CRect(0, 0, 0, 0);

    m_animationColor.SetID(-1, nAnimationGroup);
    m_animationRect.SetID(-1, nAnimationGroup);

    m_animationController.AddAnimationObject(&m_animationColor);
    m_animationController.AddAnimationObject(&m_animationRect);
}

CMFCAnimationWalkthroughView::~CMFCAnimationWalkthroughView()
{
}

BOOL CMFCAnimationWalkthroughView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	m_animationController.SetRelatedWnd(this);
	return CView::PreCreateWindow(cs);
}

// CMFCAnimationWalkthroughView 绘制

void CMFCAnimationWalkthroughView::OnDraw(CDC* pDC)
{
	CMFCAnimationWalkthroughDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CMemDC dcMem(*pDC, this);
	CDC& dc = dcMem.GetDC();

	CRect rect;
	GetClientRect(rect);

	dc.FillSolidRect(rect, GetSysColor(COLOR_WINDOW));

	CString strRGB;
	strRGB.Format(_T("Fill Color is: %d; %d; %d"), GetRValue(m_animationColor), GetGValue(m_animationColor), GetBValue(m_animationColor));

	dc.DrawText(strRGB, rect, DT_CENTER);
	rect.top += nInfoAreaHeight;

	CBrush br;

	br.CreateSolidBrush(m_animationColor);
	CBrush* pBrushOld = dc.SelectObject(&br);

	dc.Rectangle((CRect)m_animationRect);
	dc.SelectObject(pBrushOld);
}


// CMFCAnimationWalkthroughView 打印


void CMFCAnimationWalkthroughView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCAnimationWalkthroughView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCAnimationWalkthroughView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMFCAnimationWalkthroughView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CMFCAnimationWalkthroughView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCAnimationWalkthroughView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCAnimationWalkthroughView 诊断

#ifdef _DEBUG
void CMFCAnimationWalkthroughView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCAnimationWalkthroughView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCAnimationWalkthroughDoc* CMFCAnimationWalkthroughView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCAnimationWalkthroughDoc)));
	return (CMFCAnimationWalkthroughDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCAnimationWalkthroughView 消息处理程序


void CMFCAnimationWalkthroughView::OnAnimationStartbackward()
{
	// TODO:  在此添加命令处理程序代码
	Animate(FALSE);
}


void CMFCAnimationWalkthroughView::OnAnimationStartforward()
{
	// TODO:  在此添加命令处理程序代码
	Animate(TRUE);
}


void CMFCAnimationWalkthroughView::OnAnimationStop()
{
	// TODO:  在此添加命令处理程序代码
	IUIAnimationManager* pManager = m_animationController.GetUIAnimationManager();
	if (pManager != NULL)
	{
		pManager->AbandonAllStoryboards();
	}
}

void CMFCAnimationWalkthroughView::Animate(BOOL bDirection)
{
	m_bCurrentDirection = bDirection;
	static UI_ANIMATION_SECONDS duration = 3;
	static DOUBLE dblSpeed = 35.;
	static BYTE nStartColor = 50;
	static BYTE nEndColor = 255;

	BYTE nRedColorFinal = bDirection ? nStartColor : nEndColor;
	BYTE nGreenColorFinal = bDirection ? nStartColor : nEndColor;
	BYTE nBlueColorFinal = bDirection ? nStartColor : nEndColor;

	CLinearTransition* pRedTransition = new CLinearTransition(duration, (DOUBLE)nRedColorFinal);
	CSmoothStopTransition* pGreenTransition = new CSmoothStopTransition(duration, (DOUBLE)nGreenColorFinal);
	CLinearTransitionFromSpeed* pBlueTransition = new CLinearTransitionFromSpeed(dblSpeed, (DOUBLE)nBlueColorFinal);

	m_animationColor.AddTransition(pRedTransition, pGreenTransition, pBlueTransition);

	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.top += nInfoAreaHeight;

	int nLeftFinal = bDirection ? rectClient.left : rectClient.CenterPoint().x;
	int nTopFinal = bDirection ? rectClient.top : rectClient.CenterPoint().y;
	int nRightFinal = bDirection ? rectClient.right : rectClient.CenterPoint().x;
	int nBottomFinal = bDirection ? rectClient.bottom : rectClient.CenterPoint().y;

	CLinearTransition* pLeftTransition = new CLinearTransition(duration, nLeftFinal);
	CLinearTransition* pTopTransition = new CLinearTransition(duration, nTopFinal);
	CLinearTransition* pRightTransition = new CLinearTransition(duration, nRightFinal);
	CLinearTransition* pBottomTransition = new CLinearTransition(duration, nBottomFinal);

	m_animationRect.AddTransition(pLeftTransition, pTopTransition, pRightTransition, pBottomTransition);

	CBaseKeyFrame* pKeyframeStart = CAnimationController::GetKeyframeStoryboardStart();
	CKeyFrame* pKeyFrameEnd = m_animationController.CreateKeyframe(nAnimationGroup, pBlueTransition);

	pLeftTransition->SetKeyframes(pKeyframeStart, pKeyFrameEnd);
	pTopTransition->SetKeyframes(pKeyframeStart, pKeyFrameEnd);
	pRightTransition->SetKeyframes(pKeyframeStart, pKeyFrameEnd);
	pBottomTransition->SetKeyframes(pKeyframeStart, pKeyFrameEnd);

	m_animationController.AnimateGroup(nAnimationGroup);
}


BOOL CMFCAnimationWalkthroughView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}



void CMFCAnimationWalkthroughView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect);
	rect.top += nInfoAreaHeight;

	CRect rectAnim = m_animationRect;
	m_animationRect = CRect(CPoint(rect.CenterPoint().x - rectAnim.Width() / 2,
		rect.CenterPoint().y - rectAnim.Height() / 2),
		rectAnim.Size());

	if (m_animationController.IsAnimationInProgress())
	{
		Animate(m_bCurrentDirection);
	}
}

