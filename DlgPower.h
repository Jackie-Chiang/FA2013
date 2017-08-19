#pragma once
#include "afxwin.h"
#include "FA2013Doc.h"
class CFA2013Doc;

// CDlgPower �Ի���

class CDlgPower : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPower)

public:
	CDlgPower(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPower();

// �Ի�������
	enum { IDD = IDD_Power };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ChanUa;
	CComboBox ChanUb;
	CComboBox ChanUc;
	CComboBox ChanIa;
	CComboBox ChanIb;
	CComboBox ChanIc;
	CFA2013Doc* pDoc;
	virtual BOOL OnInitDialog();
	int Ua,Ub,Uc,Ia,Ib,Ic;
	afx_msg void OnCbnSelchangePua();
	afx_msg void OnCbnSelchangePub();
	afx_msg void OnCbnSelchangePuc();
	afx_msg void OnCbnSelchangePia();
	afx_msg void OnCbnSelchangePib();
	afx_msg void OnCbnSelchangePic();
};
