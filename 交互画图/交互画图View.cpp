
// ������ͼView.cpp : C������ͼView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "������ͼ.h"
#endif

#include "������ͼDoc.h"
#include "������ͼView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C������ͼView

IMPLEMENT_DYNCREATE(C������ͼView, CView)

BEGIN_MESSAGE_MAP(C������ͼView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// C������ͼView ����/����

C������ͼView::C������ͼView()
{
	// TODO: �ڴ˴���ӹ������

}

C������ͼView::~C������ͼView()
{
}

BOOL C������ͼView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C������ͼView ����

void C������ͼView::OnDraw(CDC* /*pDC*/)
{
	C������ͼDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// C������ͼView ��ӡ

BOOL C������ͼView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C������ͼView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C������ͼView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// C������ͼView ���

#ifdef _DEBUG
void C������ͼView::AssertValid() const
{
	CView::AssertValid();
}

void C������ͼView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C������ͼDoc* C������ͼView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C������ͼDoc)));
	return (C������ͼDoc*)m_pDocument;
}
#endif //_DEBUG


// C������ͼView ��Ϣ�������
