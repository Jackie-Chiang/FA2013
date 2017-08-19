#pragma once
#include "afxwin.h"
#include "Comtrade.h"
#include "FA2013Doc.h"

// CDlgHarmo �Ի���
class CHarmoView;
class CFA2013Doc;
class CDlgHarmo : public CDialog
{
	DECLARE_DYNAMIC(CDlgHarmo)

public:
	CDlgHarmo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHarmo();

// �Ի�������
	enum { IDD = IDD_Harmonics };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox Alist;
	CFA2013Doc* pDoc;
	afx_msg void OnLbnSelchangeAlist();
	CHarmoView* m_pView;
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};
#pragma once


// CHarmoView ��ͼ

class CHarmoView : public CView
{
	DECLARE_DYNCREATE(CHarmoView)

protected:
	CHarmoView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHarmoView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CFA2013Doc* pDoc;
	int CursorNum1;
	int ChanNum1;
	int DrawHarmo(CDC* pDC);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


