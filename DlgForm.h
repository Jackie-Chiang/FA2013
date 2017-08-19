#pragma once
#include "afxwin.h"
#include "Comtrade.h"
#include "FA2013Doc.h"
#include "afxcmn.h"
#include <vector>
#include <map>

// DlgForm �Ի���
class CVView;
class CFA2013Doc;

class CDlgForm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForm)

public:
	CDlgForm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgForm();

// �Ի�������
	enum { IDD = IDD_Formula };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CFA2013Doc* pDoc;
	CListCtrl AList;
	CListCtrl VList;
	CListCtrl ConstList;
	CListCtrl FxList;

	CEdit Input;
	CEdit Status;

	afx_msg void OnNMDblclkChanlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkConlist(NMHDR *pNMHDR, LRESULT *pResult);
	CVView* m_pView;
	int initConst(std::map<CString, double>* con);
	afx_msg void OnBnClickedGen();
	AChannel* t_VChannel;
	int initFunc(std::map<CString,CString>* fx,std::map<CString,CString>* des);
	afx_msg void OnBnClickedInsert();
	CString t_VName;
	afx_msg void OnNMDblclkFunlist(NMHDR *pNMHDR, LRESULT *pResult);
	int refresh_VList(void);
	afx_msg void OnNMClickVlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusVlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMHoverFunlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickFunlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusFunlist(NMHDR *pNMHDR, LRESULT *pResult);
};
#pragma once



// CVView ��ͼ

class CVView : public CScrollView
{
	DECLARE_DYNCREATE(CVView)

protected:
	CVView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CVView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

	DECLARE_MESSAGE_MAP()

public:
	CFA2013Doc* pDoc;
	int DrawVirtual(CDC* pDC);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CDlgForm* m_pDlg;
};


