
// MFCAnimationWalkthroughView.h : CMFCAnimationWalkthroughView 类的接口
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
protected: // 仅从序列化创建
	CMFCAnimationWalkthroughView();
	DECLARE_DYNCREATE(CMFCAnimationWalkthroughView)

// 特性
public:
	CMFCAnimationWalkthroughDoc* GetDocument() const;

// 操作
public:

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
	virtual ~CMFCAnimationWalkthroughView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MFCAnimationWalkthroughView.cpp 中的调试版本
inline CMFCAnimationWalkthroughDoc* CMFCAnimationWalkthroughView::GetDocument() const
   { return reinterpret_cast<CMFCAnimationWalkthroughDoc*>(m_pDocument); }
#endif

