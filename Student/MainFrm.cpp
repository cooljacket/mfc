
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Student.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	/*ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,*/

	ID_SEPARATOR, 	// ��ʾ 	nIndex = 0
	ID_SEPARATOR,	// "x:" 	nIndex = 1
	ID_SEPARATOR,	// xֵ		nIndex = 2
	ID_SEPARATOR, 	// "y:" 	nIndex = 3
	ID_SEPARATOR, 	// yֵ		nIndex = 4

};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ����ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	// ������װ���¹�����
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS |
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBar.LoadToolBar(IDR_MYTB))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}


	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// ͣ���¹�����
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar);

	// ����״̬��
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	m_wndStatusBar.SetPaneInfo(0, prompt, SBPS_STRETCH, 0); // ��ʾ
	m_wndStatusBar.SetPaneInfo(1, xName, SBPS_NOBORDERS, 8); // "x:"
	m_wndStatusBar.SetPaneText(xName, L"x:");
	m_wndStatusBar.SetPaneInfo(2, xVal, SBPS_NORMAL, 24); // xֵ
	m_wndStatusBar.SetPaneInfo(3, yName, SBPS_NOBORDERS, 8); // "y:"
	m_wndStatusBar.SetPaneText(yName, L"y:");
	m_wndStatusBar.SetPaneInfo(4, yVal, SBPS_NORMAL, 24); // yֵ


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ��������
