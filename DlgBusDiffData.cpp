// DlgBusDiffData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgBusDiffData.h"
#include "afxdialogex.h"


// CDlgBusDiffData �Ի���

IMPLEMENT_DYNAMIC(CDlgBusDiffData, CDialog)

CDlgBusDiffData::CDlgBusDiffData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBusDiffData::IDD, pParent)
	, Im(0)
	, Iop(0)
	, Iopres(0)
	, Kres(0)
{

}

CDlgBusDiffData::~CDlgBusDiffData()
{
}

void CDlgBusDiffData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Im, Im);
	DDX_Text(pDX, IDC_Iop, Iop);
	DDX_Text(pDX, IDC_Iresop, Iopres);
	DDX_Text(pDX, IDC_Kres, Kres);
}


BEGIN_MESSAGE_MAP(CDlgBusDiffData, CDialog)
END_MESSAGE_MAP()


// CDlgBusDiffData ��Ϣ�������


BOOL CDlgBusDiffData::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Im=8;
	Iop=0.3;
	Iopres=1.2;
	Kres =0.8;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgBusDiffData::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(true);
	CDialog::OnOK();
}
