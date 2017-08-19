
// AView.h : CAView ��Ľӿ�
//

#pragma once
#include"uniclass.h"
#include "stdafx.h"
#include"FA2013Doc.h"

class CAView : public CScrollView
{
protected: // �������л�����
	CAView();
	DECLARE_DYNCREATE(CAView)

// ����
public:
	CFA2013Doc* GetDocument() const;

// ����
public:
	int drawCom(CDC* m_DC);
	int drawMark(CDC* pDC,CPoint pPos, int up, int down);
	double getSampleRate(int SamplePoint,std::vector<SampleRate>& m_SampleRate);
	int drawAxis(CDC* pDC, CPoint pPos, int startSample, int endSample, CComtrade* pFile);

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
//	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnReset();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // AView.cpp �еĵ��԰汾
inline CFA2013Doc* CAView::GetDocument() const
   { return reinterpret_cast<CFA2013Doc*>(m_pDocument); }
#endif

