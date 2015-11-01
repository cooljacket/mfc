
// 交互画图View.h : C交互画图View 类的接口
//

#pragma once


class C交互画图View : public CView
{
protected: // 仅从序列化创建
	C交互画图View();
	DECLARE_DYNCREATE(C交互画图View)

// 特性
public:
	C交互画图Doc* GetDocument() const;

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
	virtual ~C交互画图View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 交互画图View.cpp 中的调试版本
inline C交互画图Doc* C交互画图View::GetDocument() const
   { return reinterpret_cast<C交互画图Doc*>(m_pDocument); }
#endif

