
// StudentView.h : CStudentView 类的接口
//

#pragma once


class CStudentView : public CView
{
protected: // 仅从序列化创建
	CStudentView();
	DECLARE_DYNCREATE(CStudentView)

// 特性
public:
	CStudentDoc* GetDocument() const;
	bool m_bTBar, m_bZs;

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
	virtual ~CStudentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnNameLs();
	afx_msg void OnNameZs();
	afx_msg void OnNameWw();
	afx_msg void OnTest();
	afx_msg void OnUpdateNaneWw(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewChangeTb();
	afx_msg void OnUpdateNameZs(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // StudentView.cpp 中的调试版本
inline CStudentDoc* CStudentView::GetDocument() const
   { return reinterpret_cast<CStudentDoc*>(m_pDocument); }
#endif

