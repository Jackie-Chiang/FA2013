// DlgSeqComp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgSeqComp.h"
#include "afxdialogex.h"
#include"splab_vector.h"

// CDlgSeqComp �Ի���

IMPLEMENT_DYNAMIC(CDlgSeqComp, CDialog)

CDlgSeqComp::CDlgSeqComp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSeqComp::IDD, pParent)
	, Pps(1.0)
	, Sps(1.0)
	, m_Mode(0)
{

}

CDlgSeqComp::~CDlgSeqComp()
{
}

void CDlgSeqComp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChanA, ChanA);
	DDX_Control(pDX, IDC_ChanB, ChanB);
	DDX_Control(pDX, IDC_ChanC, ChanC);
	DDX_Control(pDX, IDC_PhaseDataList, PDList);
	DDX_Control(pDX, IDC_SeqCompList, SDList);
}


BEGIN_MESSAGE_MAP(CDlgSeqComp, CDialog)
	ON_CBN_SELCHANGE(IDC_ChanA, &CDlgSeqComp::OnCbnSelchangeChana)
	ON_CBN_SELCHANGE(IDC_ChanB, &CDlgSeqComp::OnCbnSelchangeChanb)
	ON_CBN_SELCHANGE(IDC_ChanC, &CDlgSeqComp::OnCbnSelchangeChanc)
	ON_BN_CLICKED(IDC_Pinc, &CDlgSeqComp::OnBnClickedPinc)
	ON_BN_CLICKED(IDC_Pdec, &CDlgSeqComp::OnBnClickedPdec)
	ON_BN_CLICKED(IDC_Sinc, &CDlgSeqComp::OnBnClickedSinc)
	ON_BN_CLICKED(IDC_Sdec, &CDlgSeqComp::OnBnClickedSdec)
	ON_BN_CLICKED(IDC_Pini, &CDlgSeqComp::OnBnClickedPini)
	ON_BN_CLICKED(IDC_Sini, &CDlgSeqComp::OnBnClickedSini)
	ON_BN_CLICKED(IDC_TurnMode, &CDlgSeqComp::OnBnClickedTurnmode)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgSeqComp ��Ϣ�������


BOOL CDlgSeqComp::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int iA,iB,iC;
	iA=iB=iC=0;
	for(int i=0; i<pDoc->pFile->m_ANumber;i++)
	{
		CString tempCS;
		tempCS.Format(_T("%d:"),i+1);
		tempCS += pDoc->pFile->AVector[i]->name;
		if ((pDoc->pFile->AVector[i]->ph == _T("A"))||(pDoc->pFile->AVector[i]->ph == _T("a")))
			ChanA.InsertString(iA++,tempCS);
		else if ((pDoc->pFile->AVector[i]->ph == _T("B"))||(pDoc->pFile->AVector[i]->ph == _T("b")))
			ChanB.InsertString(iB++,tempCS);
		else if ((pDoc->pFile->AVector[i]->ph == _T("C"))||(pDoc->pFile->AVector[i]->ph == _T("c")))
			ChanC.InsertString(iC++,tempCS);
	}
	ChanA.SetCurSel(0);
	ChanB.SetCurSel(0);
	ChanC.SetCurSel(0);
	CString temp = pDoc->pFile->AVector[0]->ccbm;
	if ((pDoc->pFile->AVector[1]->ccbm == temp)&&(pDoc->pFile->AVector[1]->ccbm == temp))
	{
		CWnd* pWnd = GetDlgItem(IDC_ChanStatus);
		pWnd->SetWindowTextW(_T("��ѡ��\n")+temp);
	}
	//List
	PDList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	PDList.InsertColumn(0,_T("���"),2,100,0);
	PDList.InsertColumn(1,_T("��ֵ"),2,100,1);
	PDList.InsertColumn(2,_T("��λ"),2,100,2);
	SDList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	SDList.InsertColumn(0,_T("���"),2,100,0);
	SDList.InsertColumn(1,_T("��ֵ"),2,100,1);
	SDList.InsertColumn(2,_T("��λ"),2,100,2);
	UpdateData(TRUE);

	//P��ͼ��ʼ��
	UINT TargetCtrlID = IDC_PView;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pPView = (CSeqPView*)RUNTIME_CLASS(CSeqPView)->CreateObject();
	(m_pPView->pDoc)=pDoc;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pPView)  
	{  
	return FALSE;  
	}  
	m_pPView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);  
	m_pPView->m_pDlg = this;
	//S��ͼ��ʼ��
	TargetCtrlID = IDC_SView;  
	pWnd = this->GetDlgItem(TargetCtrlID);   
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pSView = (CSeqSView*)RUNTIME_CLASS(CSeqSView)->CreateObject();
	(m_pSView->pDoc)=pDoc;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pSView)  
	{  
	return FALSE;  
	}  
	m_pSView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);  
	m_pSView->m_pDlg = this;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgSeqComp::OnCbnSelchangeChana()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�Զ����
	int a,curPos;
	CString temp,tempccbm,tempuu,tempc,tempu;
	ChanA.GetLBText(ChanA.GetCurSel(),temp);
	curPos=0;
	a = _wtoi((temp.Tokenize(_T(":"), curPos).GetBuffer()));
	tempccbm = pDoc->pFile->AVector[a-1]->ccbm;
	tempuu = pDoc->pFile->AVector[a-1]->uu;
	int numB = ChanB.GetCount();
	int numC = ChanC.GetCount();
	int curB=0;
	int curC=0;
	while(curB<numB)
	{
		ChanB.SetCurSel(curB);
		ChanB.GetLBText(ChanB.GetCurSel(),temp);
		curPos=0;
	    a = _wtoi((temp.Tokenize(_T(":"), curPos).GetBuffer()));
		tempc = pDoc->pFile->AVector[a-1]->ccbm;
		tempu = pDoc->pFile->AVector[a-1]->uu;
		if ((tempccbm==tempc)&&(tempuu==tempu))
			break;
		else
			curB++;
	}
	while(curC<numC)
	{
		ChanC.SetCurSel(curC);
		ChanC.GetLBText(ChanC.GetCurSel(),temp);
		curPos=0;
	    a = _wtoi((temp.Tokenize(_T(":"), curPos).GetBuffer()));
		tempc = pDoc->pFile->AVector[a-1]->ccbm;
		tempu = pDoc->pFile->AVector[a-1]->uu;
		if ((tempccbm==tempc)&&(tempuu==tempu))
			break;
		else
			curC++;
	}
	//�Զ�������
	CDlgSeqComp::OnCbnSelchangeChanc();
}


void CDlgSeqComp::OnCbnSelchangeChanb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgSeqComp::OnCbnSelchangeChanc();
}


void CDlgSeqComp::OnCbnSelchangeChanc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tempA,tempB,tempC,temp;
	int A,B,C,curPos;
	ChanA.GetLBText(ChanA.GetCurSel(),tempA);
	ChanB.GetLBText(ChanB.GetCurSel(),tempB);
	ChanC.GetLBText(ChanC.GetCurSel(),tempC);
	
	curPos = 0;
	A = _wtoi((tempA.Tokenize(_T(":"), curPos).GetBuffer()));
	curPos = 0;
	B = _wtoi((tempB.Tokenize(_T(":"), curPos).GetBuffer()));
	curPos = 0;
	C = _wtoi((tempC.Tokenize(_T(":"), curPos).GetBuffer()));
	temp = pDoc->pFile->AVector[A-1]->ccbm;
	CWnd* pWnd = GetDlgItem(IDC_ChanStatus);
	if ((pDoc->pFile->AVector[B-1]->ccbm == temp)&&(pDoc->pFile->AVector[C-1]->ccbm == temp))
	{
		pWnd->SetWindowTextW(_T("��ѡ��\n")+temp);
		pDoc->view_Scroll(A-1);
		pDoc->UpdateAllViews(NULL);
	}
	else pWnd->SetWindowTextW(_T("�������ͨ����ϡ�\n��ѡ����ͬԪ����A��B��C����ͨ����"));
	
	m_pPView->Invalidate();
	m_pSView->Invalidate();
}
// C:\Users\��٩\Desktop\FA2013F\FA2013\DlgSeqComp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgSeqComp.h"


// CSeqPView

IMPLEMENT_DYNCREATE(CSeqPView, CView)

CSeqPView::CSeqPView()
   :CursorNum1(0)
{

}

CSeqPView::~CSeqPView()
{
}

BEGIN_MESSAGE_MAP(CSeqPView, CView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CSeqPView ��ͼ

void CSeqPView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	DrawP(pDC);
}


// CSeqPView ���

#ifdef _DEBUG
void CSeqPView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSeqPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSeqPView ��Ϣ�������
// C:\Users\��٩\Desktop\FA2013F\FA2013\DlgSeqComp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgSeqComp.h"


// CSeqSView

IMPLEMENT_DYNCREATE(CSeqSView, CView)

CSeqSView::CSeqSView()
   :CursorNum1(0)
{

}

CSeqSView::~CSeqSView()
{
}

BEGIN_MESSAGE_MAP(CSeqSView, CView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CSeqSView ��ͼ

void CSeqSView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	DrawS(pDC);
}


// CSeqSView ���

#ifdef _DEBUG
void CSeqSView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSeqSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSeqSView ��Ϣ�������


int CSeqPView::DrawP(CDC* pDC)
{
	m_pDlg->PDList.DeleteAllItems();
	//����������
	CRect rect;
	using splab::PI;
	extern CFA2013App theApp;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(0,0,0));//����
	//pDC->SetBkColor(RGB(0,0,0));
	CFont* def_font = pDC->SelectObject(&theApp.font);
	pDC->SetTextColor(White);
	pDC->SetBkMode(TRANSPARENT);
	int Vsp = (int)(rect.Height()*0.05);
	int R = (int)(rect.Height()*0.45);
	int Hsp = rect.Width()/2 - R;
	pDC->TextOutW(10,rect.Height()-20,_T("����ͼ"));
	CPoint center(rect.Width()/2,rect.Height()/2);
	CPen* pOld = pDC->SelectObject(&theApp.PenGrid);
	pDC->Arc(Hsp,Vsp,rect.Width()-Hsp,rect.Height()-Vsp,rect.Width()/2,Vsp,rect.Width()/2,Vsp);
	pDC->Arc(Hsp+R/2,Vsp+R/2,rect.Width()-Hsp-R/2,rect.Height()-Vsp-R/2,rect.Width()/2,Vsp+R/2,rect.Width()/2,Vsp+R/2);
	//pDC->Ellipse(Hsp,Vsp,rect.Width()-Hsp,rect.Height()-Vsp);
	for(int i=0;i<12;i++)
	{
		pDC->MoveTo(center);
		pDC->LineTo(center.x+(int)(R*cos(i*PI/6)),center.y-(int)(R*sin(i*PI/6)));
	}
	//����
	CursorNum1 =pDoc->CursorNum1;
	CString tempA,tempB,tempC;
	int A,B,C,curPos;
	m_pDlg->ChanA.GetLBText(m_pDlg->ChanA.GetCurSel(),tempA);
	m_pDlg->ChanB.GetLBText(m_pDlg->ChanB.GetCurSel(),tempB);
	m_pDlg->ChanC.GetLBText(m_pDlg->ChanC.GetCurSel(),tempC);
	curPos = 0;
	A = _wtoi((tempA.Tokenize(_T(":"), curPos).GetBuffer()));
	curPos = 0;
	B = _wtoi((tempB.Tokenize(_T(":"), curPos).GetBuffer()));
	curPos = 0;
	C = _wtoi((tempC.Tokenize(_T(":"), curPos).GetBuffer()));
	//pDoc->pFile->GetCurrentSeqComp(CursorNum1+1,A,B,C,1);
	int NA[3];NA[0]=A;NA[1]=B;NA[2]=C;
	double firsttheta = 0.0;
	for (int i=0; i<3; i++)
	{
		int ChanNum= NA[i];
		int Flag = pDoc->pFile->AVector[ChanNum-1]->GetCurrentPhasor(CursorNum1+1,pDoc->pFile->m_SampleRate);
		if (Flag==1)
		{
			pDC->TextOutW(10,10,_T("���������޷����㣬�뽫�����ƣ�"));
			return 0;
		}
		CString uu = pDoc->pFile->AVector[ChanNum-1]->uu;
		double RChan;
		double thetaChan;
		double RChan0 = pDoc->pFile->AVector[ChanNum-1]->APhasor.Amplitude;
		double thetaChan0 = pDoc->pFile->AVector[ChanNum-1]->APhasor.phase;
		//��񲿷�
		CString CSNo,CSRChan,CSthetaChan;
		CSNo = pDoc->pFile->AVector[ChanNum-1]->ph +_T("��");
		CSRChan.Format(_T("%.3f"),RChan0);
		CSRChan += uu;
		CSthetaChan.Format(_T("%.3f��"),thetaChan0);
		m_pDlg->PDList.InsertItem(i,CSNo);
		m_pDlg->PDList.SetItemText(i,1,CSRChan);
		m_pDlg->PDList.SetItemText(i,2,CSthetaChan);

		//m_pDlg->UpdateData(true);
		//��ͼ����
		RChan = RChan0 * m_pDlg->Pps;
		if (m_pDlg->m_Mode==1)
		{
			if (i==0)
			{
				firsttheta = thetaChan0;
				thetaChan = 0;
			}
			else thetaChan = thetaChan0 -firsttheta;
		}
		else
			thetaChan = thetaChan0;
		if (i==0)  {pOld = pDC->SelectObject(&theApp.PenA);pDC->SetTextColor(Yellow);}
		else if (i==1)  {pOld = pDC->SelectObject(&theApp.PenB);pDC->SetTextColor(Green);}
		else if (i==2)  {pOld = pDC->SelectObject(&theApp.PenC);pDC->SetTextColor(Red);}
		pDC->MoveTo(center);
		pDC->LineTo(center.x+(int)(RChan*cos(thetaChan*PI/180.0)),center.y-(int)(RChan*sin(thetaChan*PI/180.0)));
		pDC->LineTo(center.x+(int)(RChan*0.9*cos((thetaChan-3)*PI/180.0)),center.y-(int)(RChan*0.9*sin((thetaChan-3)*PI/180.0)));
		pDC->MoveTo(center.x+(int)(RChan*cos(thetaChan*PI/180.0)),center.y-(int)(RChan*sin(thetaChan*PI/180.0)));
		pDC->LineTo(center.x+(int)(RChan*0.9*cos((thetaChan+3)*PI/180.0)),center.y-(int)(RChan*0.9*sin((thetaChan+3)*PI/180.0)));
		CString OutText;
		OutText.Format(_T(" [%d]"),ChanNum);
		pDC->TextOutW(center.x+(int)((RChan+15)*cos(thetaChan*PI/180.0)),center.y-(int)((RChan+15)*sin(thetaChan*PI/180.0)),OutText);
		pDC->SelectObject(pOld);
	}
	return 0;
}


int CSeqSView::DrawS(CDC* pDC)
{
	m_pDlg->SDList.DeleteAllItems();
	CRect rect;
	using splab::PI;
	extern CFA2013App theApp;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(0,0,0));//����
	//pDC->SetBkColor(RGB(0,0,0));
	CFont* def_font = pDC->SelectObject(&theApp.font);
	pDC->SetTextColor(White);
	pDC->SetBkMode(TRANSPARENT);
	int Vsp = (int)(rect.Height()*0.05);
	int R = (int)(rect.Height()*0.45);
	int Hsp = (int)(rect.Width()/2) - R;
	pDC->TextOutW(10,rect.Height()-20,_T("�����ͼ"));
	CPoint center(rect.Width()/2,rect.Height()/2);
	CPen* pOld = pDC->SelectObject(&theApp.PenGrid);
	pDC->Arc(Hsp,Vsp,rect.Width()-Hsp,rect.Height()-Vsp,rect.Width()/2,Vsp,rect.Width()/2,Vsp);
	pDC->Arc(Hsp+R/2,Vsp+R/2,rect.Width()-Hsp-R/2,rect.Height()-Vsp-R/2,rect.Width()/2,Vsp+R/2,rect.Width()/2,Vsp+R/2);
	//pDC->Ellipse(Hsp,Vsp,rect.Width()-Hsp,rect.Height()-Vsp);
	for(int i=0;i<12;i++)
	{
		pDC->MoveTo(center);
		pDC->LineTo(center.x+(int)(R*cos(i*PI/6)),center.y-(int)(R*sin(i*PI/6)));
	}
	//����
	CursorNum1 =pDoc->CursorNum1;
	CString tempA,tempB,tempC;
	int A,B,C,curPos;
	m_pDlg->ChanA.GetLBText(m_pDlg->ChanA.GetCurSel(),tempA);
	m_pDlg->ChanB.GetLBText(m_pDlg->ChanB.GetCurSel(),tempB);
	m_pDlg->ChanC.GetLBText(m_pDlg->ChanC.GetCurSel(),tempC);
	curPos = 0;
	A = _wtoi((tempA.Tokenize(_T(":"), curPos).GetBuffer()));
	curPos = 0;
	B = _wtoi((tempB.Tokenize(_T(":"), curPos).GetBuffer()));
	curPos = 0;
	C = _wtoi((tempC.Tokenize(_T(":"), curPos).GetBuffer()));
	int Flag = pDoc->pFile->GetCurrentSeqComp(CursorNum1+1,A,B,C,1);
	if (Flag==1)
	{
		pDC->TextOutW(10,10,_T("���������޷����㣬�뽫�����ƣ�"));
		return 0;
	}
	double firsttheta = 0.0;
	for (int i=0; i<3; i++)
	{
		CString uu = pDoc->pFile->AVector[A-1]->uu;
		double RChan;
		double thetaChan;
		double RChan0;
		double thetaChan0;
		CString CSNo,CSRChan,CSthetaChan;
		if (i==0)
		{
			RChan0 = abs(pDoc->pFile->CurentSeqComp[0].PSC);
			thetaChan0 = arg(pDoc->pFile->CurentSeqComp[0].PSC);  //����
			CSNo = _T("�������");
		}
		else if (i==1)
		{
			RChan0 = abs(pDoc->pFile->CurentSeqComp[0].NSC);
			thetaChan0 = arg(pDoc->pFile->CurentSeqComp[0].NSC);    //����
			CSNo = _T("�������");
		}
		else if (i==2)
		{
			RChan0 = abs(pDoc->pFile->CurentSeqComp[0].ZSC);
			thetaChan0 = arg(pDoc->pFile->CurentSeqComp[0].ZSC);    //����
			CSNo = _T("�������");
		}
		//��񲿷�
		//CSNo������
		CSRChan.Format(_T("%.3f"),RChan0);
		CSRChan += uu;
		CSthetaChan.Format(_T("%.3f��"),thetaChan0*180/PI);
		m_pDlg->SDList.InsertItem(i,CSNo);
		m_pDlg->SDList.SetItemText(i,1,CSRChan);
		m_pDlg->SDList.SetItemText(i,2,CSthetaChan);

		//m_pDlg->UpdateData(true);
		//��ͼ����
		RChan = RChan0 * m_pDlg->Sps;
		if (m_pDlg->m_Mode==1)
		{
			if (i==0)
			{
				firsttheta = thetaChan0;
				thetaChan = 0;
			}
			else thetaChan = thetaChan0 -firsttheta;
		}
		else
			thetaChan = thetaChan0;
		if (i==0)  {pOld = pDC->SelectObject(&theApp.PenA);pDC->SetTextColor(Yellow);}
		else if (i==1)  {pOld = pDC->SelectObject(&theApp.PenB);pDC->SetTextColor(Green);}
		else if (i==2)  {pOld = pDC->SelectObject(&theApp.PenN);pDC->SetTextColor(White);}
		pDC->MoveTo(center);
		pDC->LineTo(center.x+(int)(RChan*cos(thetaChan)),center.y-(int)(RChan*sin(thetaChan)));
		pDC->LineTo(center.x+(int)(RChan*0.9*cos((thetaChan-0.06))),center.y-(int)(RChan*0.9*sin((thetaChan-0.06))));
		pDC->MoveTo(center.x+(int)(RChan*cos(thetaChan)),center.y-(int)(RChan*sin(thetaChan)));
		pDC->LineTo(center.x+(int)(RChan*0.9*cos((thetaChan+0.06))),center.y-(int)(RChan*0.9*sin((thetaChan+0.06))));
		CString OutText;
		if (i==0)  OutText = _T("[1]");
		else if (i==1)  OutText = _T("[2]");
		else if (i==2)  OutText = _T("[0]");
		pDC->TextOutW(center.x+(int)((RChan+15)*cos(thetaChan)),center.y-(int)((RChan+15)*sin(thetaChan)),OutText);
		pDC->SelectObject(pOld);
	}
	return 0;
}


void CDlgSeqComp::OnBnClickedPinc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Pps<50)
		Pps =Pps *1.5;
	m_pPView->Invalidate();
}


void CDlgSeqComp::OnBnClickedPdec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Pps>0.1)
		Pps =Pps /1.5;
	m_pPView->Invalidate();
}


void CDlgSeqComp::OnBnClickedSinc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Sps<50)
		Sps =Sps *1.5;
	m_pSView->Invalidate();
}


void CDlgSeqComp::OnBnClickedSdec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Sps>0.1)
		Sps =Sps /1.5;
	m_pSView->Invalidate();
}


void CDlgSeqComp::OnBnClickedPini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Pps = 1.0;
	m_pPView->Invalidate();
}


void CDlgSeqComp::OnBnClickedSini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Sps = 1.0;
	m_pSView->Invalidate();
}


void CDlgSeqComp::OnBnClickedTurnmode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd* pWnd = GetDlgItem(IDC_TurnMode);
	if (m_Mode ==0)
	{
		m_Mode =1;
		pWnd->SetWindowTextW(_T("תΪ��תģʽ"));
	}
	else
	{
		m_Mode =0;
		pWnd->SetWindowTextW(_T("תΪ���ģʽ"));
	}

	m_pPView->Invalidate();
	m_pSView->Invalidate();
}


void CDlgSeqComp::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CDialog::OnCancel();
}


void CDlgSeqComp::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	this->pDoc->pDlgSeqComp = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


void CDlgSeqComp::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	//CDialog::OnClose();
}


int CSeqPView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


int CSeqSView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
