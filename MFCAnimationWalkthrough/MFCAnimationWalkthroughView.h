
// MFCAnimationWalkthroughView.h : CMFCAnimationWalkthroughView ��Ľӿ�
//

#pragma once

// add 1
class CCustomAnimationController : public CAnimationController
{
public:
	CCustomAnimationController()
	{
	}

	virtual BOOL OnHasPriorityTrim(CAnimationGroup* pGroupScheduled, CAnimationGroup* pGroupNew, UI_ANIMATION_PRIORITY_EFFECT priorityEffect)
	{
		return TRUE;
	}
};


class CMFCAnimationWalkthroughView : public CView
{
protected: // �������л�����
	CMFCAnimationWalkthroughView();
	DECLARE_DYNCREATE(CMFCAnimationWalkthroughView)

// ����
public:
	CMFCAnimationWalkthroughDoc* GetDocument() const;

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
	virtual ~CMFCAnimationWalkthroughView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	
	void Animate(BOOL bDirection);		// add 2

public:
	afx_msg void OnAnimationStartbackward();
	afx_msg void OnAnimationStartforward();
	afx_msg void OnAnimationStop();

	// add 3
	CCustomAnimationController m_animationController;
	CAnimationColor m_animationColor; 
	CAnimationRect m_animationRect;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL m_bCurrentDirection;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // MFCAnimationWalkthroughView.cpp �еĵ��԰汾
inline CMFCAnimationWalkthroughDoc* CMFCAnimationWalkthroughView::GetDocument() const
   { return reinterpret_cast<CMFCAnimationWalkthroughDoc*>(m_pDocument); }
#endif

