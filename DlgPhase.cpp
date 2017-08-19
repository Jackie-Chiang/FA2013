// DlgPhase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgPhase.h"
#include "afxdialogex.h"
#include <math.h>
#include "splab_vector.h"


// CDlgPhase �Ի���

IMPLEMENT_DYNAMIC(CDlgPhase, CDialog)

CDlgPhase::CDlgPhase(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPhase::IDD, pParent)
	, Vps(1.0)
	, Ips(1.0)
	, m_Mode(0)
{

}

CDlgPhase::~CDlgPhase()
{
}

void CDlgPhase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WaitList, WaitList);
	DDX_Control(pDX, IDC_CurList, CurList);
	DDX_Control(pDX, IDC_Phasemode, ModeButton);
	DDX_Control(pDX, IDC_DataList, PhaseList);
}


BEGIN_MESSAGE_MAP(CDlgPhase, CDialog)
	ON_BN_CLICKED(IDC_INSERTTOLIST, &CDlgPhase::OnBnClickedInserttolist)
	ON_BN_CLICKED(IDC_DELETEONE, &CDlgPhase::OnBnClickedDeleteone)
	ON_BN_CLICKED(IDC_DELETEALL, &CDlgPhase::OnBnClickedDeleteall)
//	ON_WM_MOUSEACTIVATE()
ON_BN_CLICKED(IDC_Vinc, &CDlgPhase::OnBnClickedVinc)
ON_BN_CLICKED(IDC_Iinc, &CDlgPhase::OnBnClickedIinc)
ON_BN_CLICKED(IDC_Vdec, &CDlgPhase::OnBnClickedVdec)
ON_BN_CLICKED(IDC_Idec, &CDlgPhase::OnBnClickedIdec)
ON_BN_CLICKED(IDC_Vini, &CDlgPhase::OnBnClickedVini)
ON_BN_CLICKED(IDC_Iini, &CDlgPhase::OnBnClickedIini)
ON_BN_CLICKED(IDC_Phasemode, &CDlgPhase::OnBnClickedPhasemode)
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgPhase ��Ϣ�������


void CDlgPhase::OnBnClickedInserttolist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int N = pDoc->pFile->m_ANumber;
	int M = CurList.GetCount();
	for(int i=0; i<N;i++)
	{
		CString tempCS;
		tempCS.Format(_T("%d:"),i+1);
		tempCS += pDoc->pFile->AVector[i]->name;
		if ((0 != WaitList.GetSel(i))&&(0 > CurList.FindString(0,tempCS)))	
			CurList.InsertString(M++,tempCS);
	}
	UpdateData(TRUE);
	m_pView->Invalidate();
}


BOOL CDlgPhase::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for(int i=0; i<pDoc->pFile->m_ANumber;i++)
	{
		CString tempCS;
		tempCS.Format(_T("%d:"),i+1);
		tempCS += pDoc->pFile->AVector[i]->name;
	    WaitList.InsertString(i,tempCS);
	}
	PhaseList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	PhaseList.InsertColumn(0,_T("ͨ����"),2,70,0);
	PhaseList.InsertColumn(1,_T("ͨ������"),2,200,1);
	PhaseList.InsertColumn(2,_T("��ֵ"),2,100,2);
	PhaseList.InsertColumn(3,_T("��λ"),2,100,3);
	UpdateData(TRUE);

	UINT TargetCtrlID = IDC_PhaseView;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CPhaseView*)RUNTIME_CLASS(CPhaseView)->CreateObject();
	(m_pView->pDoc)=pDoc;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);  
	m_pView->m_pDlg = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPhase::OnBnClickedDeleteone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int M = CurList.GetCount();
	for(int i=M-1; i>=0;i--)
	{
		if (0 != CurList.GetSel(i))
			CurList.DeleteString(i);
	}
	UpdateData(TRUE);
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedDeleteall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int M = CurList.GetCount();
	for(int i=M-1; i>=0;i--)
		CurList.DeleteString(i);
	UpdateData(TRUE);
	m_pView->Invalidate();
}
// C:\Users\��٩\Desktop\FA2013F\FA2013\DlgPhase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgPhase.h"


// CPhaseView

IMPLEMENT_DYNCREATE(CPhaseView, CView)

CPhaseView::CPhaseView()
: CursorNum1(0)
{
}

CPhaseView::~CPhaseView()
{
}

BEGIN_MESSAGE_MAP(CPhaseView, CView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CPhaseView ��ͼ

void CPhaseView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	DrawPhase(pDC);
}


// CPhaseView ���

#ifdef _DEBUG
void CPhaseView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPhaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPhaseView ��Ϣ�������




int CPhaseView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


int CPhaseView::DrawPhase(CDC* pDC)
{
	CRect rect;
	using splab::PI;
	extern CFA2013App theApp;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(0,0,0));//����
	//pDC->SetBkColor(RGB(0,0,0));
	CFont* def_font = pDC->SelectObject(&theApp.font);
	pDC->SetTextColor(White);
	pDC->SetBkMode(TRANSPARENT);
	m_pDlg->PhaseList.DeleteAllItems();
	//������
	int Vsp = (int)(rect.Height()*0.05);
	int R = (int)(rect.Height()*0.45);
	int Hsp = (int)(rect.Width()/2) - R;
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
	int M = m_pDlg->CurList.GetCount();
	int ChanNum;
	CursorNum1 =pDoc->CursorNum1;
	double firsttheta = 0.0;
	for (int i=0; i<M; i++)
	{
		CString tempCS;
		int curPos=0;
		m_pDlg->CurList.GetText(i,tempCS);
		ChanNum= _wtoi((tempCS.Tokenize(_T(":"), curPos).GetBuffer()));
		int Flag = pDoc->pFile->AVector[ChanNum-1]->GetCurrentPhasor(CursorNum1+1,pDoc->pFile->m_SampleRate);
		if (Flag==1)
		{
			pDC->TextOutW(10,10,_T("���������޷����㣬�뽫�����ƣ�"));
			return 0;
		}
		CString ph = pDoc->pFile->AVector[ChanNum-1]->ph;
		CString uu = pDoc->pFile->AVector[ChanNum-1]->uu;
		double RChan;
		double thetaChan;
		double RChan0 = pDoc->pFile->AVector[ChanNum-1]->APhasor.Amplitude;
		double thetaChan0 = pDoc->pFile->AVector[ChanNum-1]->APhasor.phase;
		//��񲿷�
		CString CSNo,CSName,CSRChan,CSthetaChan;
		CSNo.Format(_T("%d"),ChanNum);
		CSName =pDoc->pFile->AVector[ChanNum-1]->name;
		CSRChan.Format(_T("%.3f"),RChan0);
		CSRChan += uu;
		CSthetaChan.Format(_T("%.3f��"),thetaChan0);
		m_pDlg->PhaseList.InsertItem(i,CSNo);
		m_pDlg->PhaseList.SetItemText(i,1,CSName);
		m_pDlg->PhaseList.SetItemText(i,2,CSRChan);
		m_pDlg->PhaseList.SetItemText(i,3,CSthetaChan);

		//m_pDlg->UpdateData(true);
		//��ͼ����
		if (( uu == _T("V"))||(uu == _T("kV")))
			RChan = RChan0 * m_pDlg->Vps;
		else if ((uu == _T("A"))||( uu == _T("kA")))
			RChan = RChan0 * m_pDlg->Ips;
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
		if (ph==_T("A"))  {pOld = pDC->SelectObject(&theApp.PenA);pDC->SetTextColor(Yellow);}
		else if (ph==_T("B"))  {pOld = pDC->SelectObject(&theApp.PenB);pDC->SetTextColor(Green);}
		else if (ph==_T("C"))  {pOld = pDC->SelectObject(&theApp.PenC);pDC->SetTextColor(Red);}
		else if (ph==_T("N"))  {pOld = pDC->SelectObject(&theApp.PenN);pDC->SetTextColor(White);}
		else if ((ph==_T(" "))||(ph==_T("")))   pOld = pDC->SelectObject(&theApp.PenF);
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


void CDlgPhase::OnBnClickedVinc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Vps<10)
		Vps =Vps *1.2;
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedIinc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Ips<50)
		Ips =Ips *2;
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedVdec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Vps>0.2)
		Vps =Vps /1.2;
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedIdec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Ips>0.2)
		Ips =Ips /1.2;
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedVini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Vps =1.0;
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedIini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Ips =1.0;
	m_pView->Invalidate();
}


void CDlgPhase::OnBnClickedPhasemode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd* pWnd = GetDlgItem(IDC_Phasemode);
	if (m_Mode ==0)
	{
		m_Mode =1;
		pWnd->SetWindowTextW(_T("ת��Ϊ��ת����"));
	}
	else
	{
		m_Mode =0;
		pWnd->SetWindowTextW(_T("ת��Ϊ�������"));
	}

	m_pView->Invalidate();
}


void CDlgPhase::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CDialog::OnCancel();
}


void CDlgPhase::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	this->pDoc->pDlgPhase = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


void CDlgPhase::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	//CDialog::OnClose();
}
