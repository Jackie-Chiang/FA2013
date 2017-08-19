#pragma once
#include "afxwin.h"
#include "FA2013Doc.h"
#include<vector>
#include "afxcmn.h"

class CPhaseView;
class CFA2013Doc;
class CDlgPhase;
// CDlgPhase �Ի���

class CDlgPhase : public CDialog
{
	DECLARE_DYNAMIC(CDlgPhase)

public:
	CDlgPhase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPhase();


// �Ի�������
	enum { IDD = IDD_Phase };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CFA2013Doc* pDoc;
	CPhaseView* m_pView;
	CListBox WaitList;
	CListBox CurList;
	afx_msg void OnBnClickedInserttolist();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDeleteone();
	afx_msg void OnBnClickedDeleteall();
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	double Vps;
	double Ips;
	int m_Mode;
	afx_msg void OnBnClickedVinc();
	afx_msg void OnBnClickedIinc();
	afx_msg void OnBnClickedVdec();
	afx_msg void OnBnClickedIdec();
	afx_msg void OnBnClickedVini();
	afx_msg void OnBnClickedIini();
	afx_msg void OnBnClickedPhasemode();
	CButton ModeButton;
	CListCtrl PhaseList;
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};
#pragma once


// CPhaseView ��ͼ

class CPhaseView : public CView
{
	DECLARE_DYNCREATE(CPhaseView)

protected:
	CPhaseView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPhaseView();

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
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	int DrawPhase(CDC* pDC);
	int CursorNum1;
	CDlgPhase* m_pDlg;

};


