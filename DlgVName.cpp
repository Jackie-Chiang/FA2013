// DlgVName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgVName.h"
#include "afxdialogex.h"


// CDlgVName �Ի���

IMPLEMENT_DYNAMIC(CDlgVName, CDialog)

CDlgVName::CDlgVName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVName::IDD, pParent)
	, t_VName(_T(""))
{

}

CDlgVName::~CDlgVName()
{
}

void CDlgVName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VNAMEEDIT, VNameEdit);
}


BEGIN_MESSAGE_MAP(CDlgVName, CDialog)
END_MESSAGE_MAP()


// CDlgVName ��Ϣ�������


void CDlgVName::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	int len = VNameEdit.LineLength(VNameEdit.LineIndex(0));
	VNameEdit.GetLine(0,t_VName.GetBuffer(len), len);
	t_VName.ReleaseBuffer(len);
	CDialog::OnOK();
}
