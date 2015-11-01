
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "ActivePainter.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR, 	// 提示 	nIndex = 0
	ID_SEPARATOR,	// "x:" 	nIndex = 1
	ID_SEPARATOR,	// x值		nIndex = 2
	ID_SEPARATOR, 	// "y:" 	nIndex = 3
	ID_SEPARATOR, 	// y值		nIndex = 4
	ID_SEPARATOR,	// "area:"	nIndex = 5
	ID_SEPARATOR	// 矩形的面积	nIndex = 6
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndStatusBar.SetPaneInfo(0, prompt, SBPS_STRETCH, 0); // 提示
	m_wndStatusBar.SetPaneInfo(1, xName, SBPS_NOBORDERS, 8); // "x:"
	m_wndStatusBar.SetPaneText(xName, L"x:");
	m_wndStatusBar.SetPaneInfo(2, xVal, SBPS_NORMAL, 24); // x值

	m_wndStatusBar.SetPaneInfo(3, yName, SBPS_NOBORDERS, 8); // "y:"
	m_wndStatusBar.SetPaneText(yName, L"y:");
	m_wndStatusBar.SetPaneInfo(4, yVal, SBPS_NORMAL, 24); // y值

	m_wndStatusBar.SetPaneInfo(5, sName, SBPS_NOBORDERS, 24); // "y:"
	m_wndStatusBar.SetPaneText(sName, L"Area:");
	m_wndStatusBar.SetPaneInfo(6, area, SBPS_NORMAL, 24); // y值

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

