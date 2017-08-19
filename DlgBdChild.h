#pragma once
#include "afxwin.h"
#include "Boundry.h"
#include "DlgImp.h"

class CDlgImp;
class CDlgBoundry;

// CBdView ��ͼ

class CBdView : public CView
{
	DECLARE_DYNCREATE(CBdView)

protected:
	CBdView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBdView();

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
	CDlgImp* m_pDlg;
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};

// CDlgBdParam �Ի���

class CDlgBdParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBdParam)

public:
	CDlgBdParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBdParam();

// �Ի�������
	enum { IDD = IDD_BdParam };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CBdView* m_pView;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush bkgBr;
};
#pragma once


// CDlgBdPoly �Ի���

class CDlgBdPoly : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBdPoly)

public:
	CDlgBdPoly(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBdPoly();

// �Ի�������
	enum { IDD = IDD_BdPoly };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CBdView* m_pView;
	CBrush bkgBr;
	double Rset1;
	double Xset1;
	double Beta;
	double Alpha;
	double Theta;
	CDlgImp* m_pDlg;
	CDlgBoundry* outerDlg;
	afx_msg void OnBnClickedPrePoly();
	afx_msg void OnBnClickedInsPoly();
};
#pragma once




#pragma once


// CDlgBdLine �Ի���

class CDlgBdLine : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBdLine)

public:
	CDlgBdLine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBdLine();

// �Ի�������
	enum { IDD = IDD_BdLine };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush bkgBr;
	CBdView* m_pView;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedPreLine();
	double Rset1;
	double Xset1;
	double Beta;
	CDlgImp* m_pDlg;
	CDlgBoundry* outerDlg;
	afx_msg void OnBnClickedInsLine();
};
#pragma once


// CDlgBdCircle �Ի���

class CDlgBdCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBdCircle)

public:
	CDlgBdCircle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBdCircle();

// �Ի�������
	enum { IDD = IDD_BdCircle };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush bkgBr;
	CBdView* m_pView;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CDlgImp* m_pDlg;
	CDlgBoundry* outerDlg;
	double Rset1;
	double Xset1;
	double Alpha;
	afx_msg void OnBnClickedPreCircle();
	afx_msg void OnBnClickedInsCircle();
};
#pragma once


// CDlgBdRect �Ի���

class CDlgBdRect : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBdRect)

public:
	CDlgBdRect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBdRect();

// �Ի�������
	enum { IDD = IDD_BdRect };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush bkgBr;
	CBdView* m_pView;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	double Rset1;
	double Rset2;
	double Xset1;
	double Xset2;
	CDlgImp* m_pDlg;
	CDlgBoundry* outerDlg;
	afx_msg void OnBnClickedPreRect();
	afx_msg void OnBnClickedInsRect();
};
