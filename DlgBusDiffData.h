#pragma once


// CDlgBusDiffData �Ի���

class CDlgBusDiffData : public CDialog
{
	DECLARE_DYNAMIC(CDlgBusDiffData)

public:
	CDlgBusDiffData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBusDiffData();

// �Ի�������
	enum { IDD = IDD_BusDiffData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double Im;
	double Iop;
	double Iopres;
	double Kres;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
