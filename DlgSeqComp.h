#pragma once

#include"FA2013Doc.h"
#include "afxwin.h"
#include "afxcmn.h"

class CFA2013Doc;
class CDlgSeqComp;
class CSeqPView;
class CSeqSView;
// CDlgSeqComp �Ի���

class CDlgSeqComp : public CDialog
{
	DECLARE_DYNAMIC(CDlgSeqComp)

public:
	CDlgSeqComp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSeqComp();

// �Ի�������
	enum { IDD = IDD_SeqComp };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFA2013Doc* pDoc;
	CSeqPView* m_pPView;
	CSeqSView* m_pSView;
	CComboBox ChanA;
	CComboBox ChanB;
	CComboBox ChanC;
	double Pps;   //����
	double Sps;   //����
	int m_Mode;   //��תģʽ
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeChana();
	afx_msg void OnCbnSelchangeChanb();
	afx_msg void OnCbnSelchangeChanc();
	CListCtrl PDList;
	CListCtrl SDList;
	afx_msg void OnBnClickedPinc();
	afx_msg void OnBnClickedPdec();
	afx_msg void OnBnClickedSinc();
	afx_msg void OnBnClickedSdec();
	afx_msg void OnBnClickedPini();
	afx_msg void OnBnClickedSini();
	afx_msg void OnBnClickedTurnmode();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};
#pragma once


// CSeqPView ��ͼ

class CSeqPView : public CView
{
	DECLARE_DYNCREATE(CSeqPView)

protected:
	CSeqPView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSeqPView();

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
	CDlgSeqComp* m_pDlg;
	int DrawP(CDC* pDC);
	int CursorNum1;
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


#pragma once


// CSeqSView ��ͼ

class CSeqSView : public CView
{
	DECLARE_DYNCREATE(CSeqSView)

protected:
	CSeqSView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSeqSView();

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
	CDlgSeqComp* m_pDlg;
	int DrawS(CDC* pDC);
	int CursorNum1;
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


