#pragma once
#include "afxwin.h"


// CDlgVName �Ի���

class CDlgVName : public CDialog
{
	DECLARE_DYNAMIC(CDlgVName)

public:
	CDlgVName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVName();

// �Ի�������
	enum { IDD = IDD_VNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit VNameEdit;
	CString t_VName;
};
