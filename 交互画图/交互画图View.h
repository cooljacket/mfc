
// ������ͼView.h : C������ͼView ��Ľӿ�
//

#pragma once


class C������ͼView : public CView
{
protected: // �������л�����
	C������ͼView();
	DECLARE_DYNCREATE(C������ͼView)

// ����
public:
	C������ͼDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~C������ͼView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ������ͼView.cpp �еĵ��԰汾
inline C������ͼDoc* C������ͼView::GetDocument() const
   { return reinterpret_cast<C������ͼDoc*>(m_pDocument); }
#endif

