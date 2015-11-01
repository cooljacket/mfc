
// MouseKeyView.cpp : CMouseKeyView 类的实现
//

#include "stdafx.h"
#include "MainFrm.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MouseKey.h"
#endif

#include "MouseKeyDoc.h"
#include "MouseKeyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseKeyView

IMPLEMENT_DYNCREATE(CMouseKeyView, CView)

BEGIN_MESSAGE_MAP(CMouseKeyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMouseKeyView 构造/析构

CMouseKeyView::CMouseKeyView()
{
	// TODO: 在此处添加构造代码

}

CMouseKeyView::~CMouseKeyView()
{
}

BOOL CMouseKeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMouseKeyView 绘制

void CMouseKeyView::OnDraw(CDC* /*pDC*/)
{
	CMouseKeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMouseKeyView 打印

BOOL CMouseKeyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMouseKeyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMouseKeyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMouseKeyView 诊断

#ifdef _DEBUG
void CMouseKeyView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseKeyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseKeyDoc* CMouseKeyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseKeyDoc)));
	return (CMouseKeyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseKeyView 消息处理程序


void CMouseKeyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	POINT p; // 定义点结构变量
	GetCursorPos(&p); // 获取当前光标位置
	int iStepLen = 1; // 设置初始步长为1
	// Shift键被按下时设置步长为5
	if(GetKeyState(VK_SHIFT) & 1<<15) iStepLen = 5;
	// Ctrl键被按下时设置步长为10
	if(GetKeyState(VK_CONTROL) & 1<<15) iStepLen = 10;
	switch (nChar) { // 判断用户按键
	 case VK_UP: p.y -= iStepLen; break; // ↑：上移一个步长
	 case VK_DOWN: p.y += iStepLen; break; // ↓：下移一个步长
	 case VK_LEFT: p.x -= iStepLen; break; // ←：左移一个步长
	 case VK_RIGHT: p.x += iStepLen; break; // →：右移一个步长
	}
	SetCursorPos(p.x, p.y); // 设置新光标位置（触发鼠标移动事件）

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMouseKeyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(LoadCursor(NULL, IDC_CROSS)); // 装入并设置十字光标
	wchar_t buf[20];
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	_itow_s(point.x, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->xVal, buf);
	_itow_s(point.y, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->yVal, buf);

	CView::OnMouseMove(nFlags, point);
}
