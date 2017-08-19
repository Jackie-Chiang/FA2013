// DlgHarmo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgHarmo.h"
#include "afxdialogex.h"
#include "uniclass.h"
#include<vector>
#include"drawcube.h"

// CDlgHarmo �Ի���

IMPLEMENT_DYNAMIC(CDlgHarmo, CDialog)

CDlgHarmo::CDlgHarmo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHarmo::IDD, pParent)
{

}

CDlgHarmo::~CDlgHarmo()
{
}

void CDlgHarmo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALIST, Alist);
}


BEGIN_MESSAGE_MAP(CDlgHarmo, CDialog)
	ON_LBN_SELCHANGE(IDC_ALIST, &CDlgHarmo::OnLbnSelchangeAlist)
//	ON_WM_MOUSEACTIVATE()
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgHarmo ��Ϣ�������


BOOL CDlgHarmo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for(int i=0; i<pDoc->pFile->m_ANumber;i++)
		//Alist.AddString(pDoc->pFile->AVector[i]->name);
	    Alist.InsertString(i,pDoc->pFile->AVector[i]->name);
	UpdateData(TRUE);

	UINT TargetCtrlID = IDC_HARMO_VIEW;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CHarmoView*)RUNTIME_CLASS(CHarmoView)->CreateObject();
	(m_pView->pDoc)=pDoc;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);  
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgHarmo::OnLbnSelchangeAlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = Alist.GetCurSel();
	pDoc->ChanNum1 = i;
	pDoc->view_Scroll(i);
	pDoc->UpdateAllViews(NULL);
	m_pView->Invalidate();
}
// C:\Users\yi\Desktop\fa\FA2013\DlgHarmo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgHarmo.h"


// CHarmoView

IMPLEMENT_DYNCREATE(CHarmoView, CView)

CHarmoView::CHarmoView()
: CursorNum1(0)
, ChanNum1(0)
{

}

CHarmoView::~CHarmoView()
{
}

BEGIN_MESSAGE_MAP(CHarmoView, CView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CHarmoView ��ͼ

void CHarmoView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	this->DrawHarmo(pDC);
	// TODO: �ڴ���ӻ��ƴ���
}


// CHarmoView ���

#ifdef _DEBUG
void CHarmoView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHarmoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHarmoView ��Ϣ�������



int CHarmoView::DrawHarmo(CDC *pDC)
{
	extern CFA2013App theApp;
	CursorNum1=pDoc->CursorNum1;
	ChanNum1=pDoc->ChanNum1;
	CString A;
	CComTime aT = pDoc->pFile->m_StartTime + pDoc->pFile->Time[CursorNum1];
	A = aT.PrintTimeWithDate();
	//View��
	CRect bkgRect;
	this->GetClientRect(bkgRect);
	double W = bkgRect.Width();
	double H = bkgRect.Height();
	//�ҿ�
	CRect MainRect(bkgRect.left + (int)(W*0.02),bkgRect.top+30,bkgRect.right-(int)(W*0.02),bkgRect.bottom-30);//(10,30,10+65*6+10,250);
	double HW = 0.96*W/6;   //���ܿ���϶
	double sW = 0.96*W/60; //����϶
	pDC->FillSolidRect(bkgRect,RGB(0,0,0));
	pDC->FillSolidRect(MainRect,Gray);
	CFont* def_font = pDC->SelectObject(&theApp.font);
	pDC->SetTextColor(White);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOutW(10,10,A);
	int flag = pDoc->pFile->AVector[ChanNum1]->InstFFT(CursorNum1+1,pDoc->pFile->m_SampleRate);
	if (flag==0)
	{
		double max_Harmo = pDoc->pFile->AVector[ChanNum1]->Harmonics[0];
		double sum,temp,DrawTemp[6],DataTemp;
		sum=0.0;
		CString TextHarmo,TextAxis;//г���ٷֱ�
		for (int i=0; i<6;i++)
		{
			temp = pDoc->pFile->AVector[ChanNum1]->Harmonics[i];
			sum +=temp;
			if (temp>max_Harmo)
				max_Harmo = temp;
		}
		for(int i=0; i<6; i++)
		{
			DrawTemp[i] = /*200*/(H-80)*pDoc->pFile->AVector[ChanNum1]->Harmonics[i]/max_Harmo;
			if (DrawTemp[i]<1)
				DrawTemp[i]=1;
			CRect rect(bkgRect.left+(int)(sW+i*HW+ W*0.02),bkgRect.bottom-30-(int)(DrawTemp[i]),bkgRect.left+(int)(sW+i*HW+(HW-2*sW)+ W*0.02),bkgRect.bottom-30);
			//pDC->FillSolidRect(20+i*65,250-DrawTemp[i],55,DrawTemp[i],Red);
			DrawColorCube(pDC,rect,Red,RGB(255,255,255), false);
			DataTemp = 100*pDoc->pFile->AVector[ChanNum1]->Harmonics[i]/sum;
			TextHarmo.Format(_T("%.1f"),DataTemp);
			TextHarmo += _T("%");
			pDC->TextOutW(bkgRect.left+(int)(sW+i*HW+ W*0.02+HW/6),bkgRect.bottom-50-(int)(DrawTemp[i]),TextHarmo);

			if (i==0) TextAxis = _T("ֱ��");
			else if (i==1) TextAxis =  _T("����");
			else TextAxis.Format(_T("%d��"),i);
			pDC->TextOutW(bkgRect.left+(int)(sW+i*HW+ W*0.02),bkgRect.bottom-25,TextAxis);
		}
		pDC->SelectObject(def_font);
	//	CPen *pOld=pDC->SelectObject(&theApp.PenC);
	//	pDC->MoveTo(10,251);
	//	pDC->LineTo(10+65*6+10,251);
	//	pDC->SelectObject(pOld);
	}
	else
	{
		pDC->TextOutW(bkgRect.left+40,(int)(bkgRect.bottom-H/2),_T("���������޷����㣬�뽫�����ƣ�"));
		pDC->SelectObject(def_font);
	}
	return 0;
}




//int CDlgHarmo::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
//}


int CHarmoView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CDlgHarmo::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	DestroyWindow();
	//CDialog::OnCancel();
}



void CDlgHarmo::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	this->pDoc->pDlgHarmo = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


void CDlgHarmo::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	//CDialog::OnClose();
}
