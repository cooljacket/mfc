
// MouseKeyView.cpp : CMouseKeyView ���ʵ��
//

#include "stdafx.h"
#include "MainFrm.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMouseKeyView ����/����

CMouseKeyView::CMouseKeyView()
{
	// TODO: �ڴ˴���ӹ������

}

CMouseKeyView::~CMouseKeyView()
{
}

BOOL CMouseKeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMouseKeyView ����

void CMouseKeyView::OnDraw(CDC* /*pDC*/)
{
	CMouseKeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMouseKeyView ��ӡ

BOOL CMouseKeyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMouseKeyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMouseKeyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMouseKeyView ���

#ifdef _DEBUG
void CMouseKeyView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseKeyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseKeyDoc* CMouseKeyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseKeyDoc)));
	return (CMouseKeyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseKeyView ��Ϣ�������


void CMouseKeyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POINT p; // �����ṹ����
	GetCursorPos(&p); // ��ȡ��ǰ���λ��
	int iStepLen = 1; // ���ó�ʼ����Ϊ1
	// Shift��������ʱ���ò���Ϊ5
	if(GetKeyState(VK_SHIFT) & 1<<15) iStepLen = 5;
	// Ctrl��������ʱ���ò���Ϊ10
	if(GetKeyState(VK_CONTROL) & 1<<15) iStepLen = 10;
	switch (nChar) { // �ж��û�����
	 case VK_UP: p.y -= iStepLen; break; // ��������һ������
	 case VK_DOWN: p.y += iStepLen; break; // ��������һ������
	 case VK_LEFT: p.x -= iStepLen; break; // ��������һ������
	 case VK_RIGHT: p.x += iStepLen; break; // ��������һ������
	}
	SetCursorPos(p.x, p.y); // �����¹��λ�ã���������ƶ��¼���

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMouseKeyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCursor(LoadCursor(NULL, IDC_CROSS)); // װ�벢����ʮ�ֹ��
	wchar_t buf[20];
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	_itow_s(point.x, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->xVal, buf);
	_itow_s(point.y, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->yVal, buf);

	CView::OnMouseMove(nFlags, point);
}
