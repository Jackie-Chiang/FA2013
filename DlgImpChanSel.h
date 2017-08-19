#pragma once
#include "afxwin.h"
#include "FA2013Doc.h"

class CFA2013Doc;

// CDlgImpChanSel �Ի���

class CDlgImpChanSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImpChanSel)

public:
	CDlgImpChanSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImpChanSel();

// �Ի�������
	enum { IDD = IDD_ImpChanSel };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ChanUaS;
	CComboBox ChanUbS;
	CComboBox ChanUcS;
	CComboBox ChanIaS;
	CComboBox ChanIbS;
	CComboBox ChanIcS;

	int Ua,Ub,Uc,Ia,Ib,Ic; //ͨ����
	int SelFlag;
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	CFA2013Doc* pDoc;
	int Type;
	afx_msg void OnCbnSelchangeChanua();
	afx_msg void OnCbnSelchangeChanub();
	afx_msg void OnCbnSelchangeChanuc();
	afx_msg void OnCbnSelchangeChania();
	afx_msg void OnCbnSelchangeChanib();
	afx_msg void OnCbnSelchangeChanic();
	double R1;
	double X1;
	double R0;
	double X0;
};
