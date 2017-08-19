// DlgImp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgImp.h"
#include "afxdialogex.h"
#include "DlgBoundry.h"
#include "DlgImpChanSel.h"
#include "splab_vector.h"
#include<math.h>
#include <complex>

class CDlgImpChanSel;
// CDlgImp �Ի���

IMPLEMENT_DYNAMIC(CDlgImp, CDialogEx)

CDlgImp::CDlgImp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgImp::IDD, pParent)
	, pDoc(NULL)
	, m_pView(NULL)
	, Ua(-1)
	, Ub(-1)
	, Uc(-1)
	, Ia(-1)
	, Ib(-1)
	, Ic(-1)
	, SelFlag(0)
	, t_midP(0,0)
	,P_num(1)
	,L_num(1)
	,C_num(1)
	,R_num(1)
{

}

CDlgImp::~CDlgImp()
{
}

void CDlgImp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ImpType, ImpTypeSel);
	DDX_Control(pDX, IDC_BdList, BdListOuter);
	DDX_Control(pDX, IDC_ImpList, ImpList);
}


BEGIN_MESSAGE_MAP(CDlgImp, CDialogEx)
	ON_BN_CLICKED(IDC_SetBd, &CDlgImp::OnBnClickedSetbd)
	ON_CBN_SELCHANGE(IDC_ImpType, &CDlgImp::OnCbnSelchangeImptype)
	ON_BN_CLICKED(IDC_ImpRst, &CDlgImp::OnBnClickedImprst)
	ON_BN_CLICKED(IDC_DispLoc, &CDlgImp::OnBnClickedDisploc)
	ON_NOTIFY(NM_CLICK, IDC_BdList, &CDlgImp::OnNMClickBdlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_BdList, &CDlgImp::OnLvnItemchangedBdlist)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgImp ��Ϣ�������
// C:\Users\��٩\Desktop\FA2013\FA2013\DlgImp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgImp.h"


// CImpView

IMPLEMENT_DYNCREATE(CImpView, CView)

CImpView::CImpView()
: pDoc(NULL)
, m_pDlg(NULL)
, MPos(-1,-1)
, MidP(0,0)
, MidP0(0,0)
, MidPLast(0,0)
, ZoomFlag(0)
, CursorNum1(0)
, LocFlag(0)
{
	ZPS = defaultZPS = 0.5;
	SPD = defaultSPD =30;

}

CImpView::~CImpView()
{
}

BEGIN_MESSAGE_MAP(CImpView, CView)
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CImpView ��ͼ

void CImpView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	DrawImp(pDC);
}


// CImpView ���

#ifdef _DEBUG
void CImpView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CImpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CImpView ��Ϣ�������


BOOL CDlgImp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UINT TargetCtrlID = IDC_ImpView;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CImpView*)RUNTIME_CLASS(CImpView)->CreateObject();
	(m_pView->pDoc)=pDoc;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);
	m_pView->m_pDlg = this;
	ImpTypeSel.InsertString(0,_T("��ѡ���������..."));
	ImpTypeSel.InsertString(1,_T("��·�ӵ��迹[Uy/(Iy+kIo)]..."));
	ImpTypeSel.InsertString(2,_T("��·�����迹[Uy/Iy]..."));
	ImpTypeSel.InsertString(3,_T("��·����迹[U��/I��]..."));
	ImpTypeSel.SetCurSel(0);

	//��ʼ���迹�б�
	ImpList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	ImpList.InsertColumn(0,_T("���"),2,70,0);
	ImpList.InsertColumn(1,_T("�迹��R+jX��"),2,150,1);
	ImpList.InsertColumn(2,_T("�迹��Z�Ϧȣ�"),2,150,2);
	UpdateData(TRUE);
	//��ʼ���߽��б�
	CRect listRect;
	//������չ���
	DWORD styles = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyleEx(BdListOuter.m_hWnd, styles, styles );
	BdListOuter.GetClientRect(&listRect);
	BdListOuter.InsertColumn(0,_T("�߽�"),LVCFMT_LEFT,listRect.Width()/5*4,-1);
	//BdListCtrl.InsertColumn(1,_T("ͨ��"),LVCFMT_LEFT,listRect.Width()/4*3,-1);
	int totalNum =BdList.size();
	for(int i=0; i<totalNum;i++)
	{
		BdListOuter.InsertItem(LVIF_TEXT | LVIF_STATE,i,BdList[i]->Name,0,LVIS_SELECTED,0,0);
		//BdListCtrl.SetItemText(i,1,pDoc->pFile->AVector[i]->name);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


int CImpView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CDlgImp::OnBnClickedSetbd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgBoundry Bd;
	Bd.m_pDlg=this;
	Bd.DoModal();
}


void CDlgImp::OnCbnSelchangeImptype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	using std::complex;
	int Type = ImpTypeSel.GetCurSel();
	if (Type==0)
		return;
	CDlgImpChanSel pDlg;
	pDlg.pDoc = pDoc;
	pDlg.Type = Type;
	if(pDlg.DoModal() == IDOK)
	{
		SelFlag = pDlg.SelFlag;
		Ua = pDlg.Ua;Ub = pDlg.Ub;Uc = pDlg.Uc;
		Ia = pDlg.Ia;Ib = pDlg.Ib;Ic = pDlg.Ic;
		LD.z0 = complex<double>(pDlg.R0,pDlg.X0);
		LD.z1 = complex<double>(pDlg.R1,pDlg.X1);
	}
	else
	{
	}
}


int CImpView::DrawImp(CDC* pDC)
{
	m_pDlg->ImpList.DeleteAllItems();
	CRect rect;
	using splab::PI;
	extern CFA2013App theApp;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(0,0,0));//����
	int space = rect.Width()*0.05;
	MidP0.x = rect.right/2;
	MidP0.y = rect.bottom/2;
	if (MPos.x==-1)
	{
		MidPLast = MidP = MidP0;
	}
	else if(MPos.x==-2)
	{
		MidP = MidPLast;
	}
	else
	{
		MidPLast = MidP;
		//MidP = MPos;
		if (ZoomFlag == 1)
		{
			MidP.y = (MidPLast.y- (MPos.y - rect.Height()/4))*2;
			MidP.x = (MidPLast.x- (MPos.x - rect.Width()/4))*2;
		}
		else if(ZoomFlag ==-1)
		{
			MidP.y = (MidPLast.y +rect.Height() -MPos.y)/2;
			MidP.x = (MidPLast.x +rect.Width() -MPos.x)/2;
		}
		MPos = (-2,-2);
	}
	int Dx = MidP.x-MidP0.x;
	int Dy = MidP.y-MidP0.y; 
	CPen* pOld = pDC->SelectObject(&theApp.PenGridGray);
	//����
	int nXa,nYl,nXb,nYr;
	nXa=nYl=nXb=nYr=1;
	CString TempCS;
	CFont* def_font = pDC->SelectObject(&theApp.font);
	pDC->SetTextColor(White);
	TempCS.Format(_T("����̶�: %.3f ��/��"),SPD*ZPS);
	pDC->TextOutW(rect.left+space,rect.bottom-20,TempCS);
	while(MidP.x + SPD*nYr < rect.right-space)
	{
		pDC->MoveTo(MidP.x + SPD*nYr,rect.top+space);
		pDC->LineTo(MidP.x + SPD*nYr,rect.bottom-space);
		nYr++;
	}
	while(MidP.x - SPD*nYl > rect.left+space)
	{
		pDC->MoveTo(MidP.x - SPD*nYl,rect.top+space);
		pDC->LineTo(MidP.x - SPD*nYl,rect.bottom-space);
		nYl++;
	}
	while(MidP.y + SPD*nXb < rect.bottom-space)
	{
		pDC->MoveTo(rect.left+space,MidP.y + SPD*nXb);
		pDC->LineTo(rect.right-space,MidP.y + SPD*nXb);
		nXb++;
	}
	while(MidP.y - SPD*nXa > rect.top+space)
	{
		pDC->MoveTo(rect.left+space,MidP.y - SPD*nXa);
		pDC->LineTo(rect.right-space,MidP.y - SPD*nXa);
		nXa++;
	}
	pOld = pDC->SelectObject(&theApp.PenN);
	//x��
	pDC->MoveTo(rect.left+space,rect.bottom/2+Dy);
	pDC->LineTo(rect.right-space,rect.bottom/2+Dy);
	pDC->TextOutW(rect.right-space,rect.bottom/2+Dy,_T("R"));
	//y��
	pDC->MoveTo(rect.right/2+Dx,rect.top+space);
	pDC->LineTo(rect.right/2+Dx,rect.bottom-space);
	pDC->TextOutW(rect.right/2+2+Dx,rect.top,_T("jX"));
	pDC->SelectObject(pOld);
	CBrush* pOldb = pDC->SelectObject(&theApp.BrushN);
	//X��ͷ
	pDC->BeginPath();
	pDC->MoveTo(rect.right-space,rect.bottom/2+Dy);
	pDC->LineTo(rect.right-space-10,rect.bottom/2+Dy+7);
	pDC->LineTo(rect.right-space-10,rect.bottom/2+Dy-7);
	pDC->LineTo(rect.right-space,rect.bottom/2+Dy);
	pDC->EndPath();
	pDC->FillPath();
	//Y��ͷ
	pDC->BeginPath();
	pDC->MoveTo(rect.right/2+Dx,rect.top+space);
	pDC->LineTo(rect.right/2-7+Dx,rect.top+space+10);
	pDC->LineTo(rect.right/2+7+Dx,rect.top+space+10);
	pDC->LineTo(rect.right/2+Dx,rect.top+space);
	pDC->EndPath();
	pDC->FillPath();

	//����
	//pDC->Ellipse(MidP.x-30/ZPS,MidP.y-20/ZPS,MidP.x+30/ZPS,MidP.y+20/ZPS);

	if (m_pDlg->SelFlag!=1)
		return 0;
	else
	{
		
		//���Ʊ߽�
		for(int i=0; i< m_pDlg->BdListOuter.GetItemCount(); i++)
		{
			if(m_pDlg->BdListOuter.GetCheck(i))
			{
				m_pDlg->BdList[i]->ZPS=ZPS;
				m_pDlg->BdList[i]->drawBd(pDC,MidP,rect);
			}
		}

		CursorNum1 = pDoc->CursorNum1;
		int Type = m_pDlg->ImpTypeSel.GetCurSel();
		CPoint PnowA,PlastA,PnowB,PlastB,PnowC,PlastC;
		if (this->LocFlag == 1)
		{
			int Pcount=0;
			int c_Flag;
			for(int i=0; i<=CursorNum1; i++)
			{
				c_Flag =pDoc->pFile->GetCurrentZ(i+1,m_pDlg->Ua,m_pDlg->Ub,m_pDlg->Uc,m_pDlg->Ia,m_pDlg->Ib,m_pDlg->Ic,Type,m_pDlg->LD);
				if (c_Flag==1)
				{
					Pcount = 0;
					continue;
				}
				else
				{
					Pcount++;
					//A��
					PnowA.x = MidP.x + (pDoc->pFile->z.R1)/ZPS;
					PnowA.y = MidP.y - (pDoc->pFile->z.X1)/ZPS;
					PnowB.x = MidP.x + (pDoc->pFile->z.R2)/ZPS;
					PnowB.y = MidP.y - (pDoc->pFile->z.X2)/ZPS;
					PnowC.x = MidP.x + (pDoc->pFile->z.R3)/ZPS;
					PnowC.y = MidP.y - (pDoc->pFile->z.X3)/ZPS;
					pOld = pDC->SelectObject(&theApp.PenA);
					if (((PnowA.x<rect.right)&&(PnowA.x>rect.left)&&(PnowA.y<rect.bottom)&&(PnowA.y>rect.top))
						||((PlastA.x<rect.right)&&(PlastA.x>rect.left)&&(PlastA.y<rect.bottom)&&(PlastA.y>rect.top)))
					{
						if (Pcount==1)
							pDC->MoveTo(PnowA);
						else
						{
							pDC->MoveTo(PlastA);
							pDC->LineTo(PnowA);
						}
					}
					//B��
					pOld = pDC->SelectObject(&theApp.PenB);
					if (((PnowB.x<rect.right)&&(PnowB.x>rect.left)&&(PnowB.y<rect.bottom)&&(PnowB.y>rect.top))
						||((PlastB.x<rect.right)&&(PlastB.x>rect.left)&&(PlastB.y<rect.bottom)&&(PlastB.y>rect.top)))
					{
						if (Pcount==1)
							pDC->MoveTo(PnowB);
						else
						{
							pDC->MoveTo(PlastB);
							pDC->LineTo(PnowB);
						}
					}
					//C��
					pOld = pDC->SelectObject(&theApp.PenC);
					if (((PnowC.x<rect.right)&&(PnowC.x>rect.left)&&(PnowC.y<rect.bottom)&&(PnowC.y>rect.top))
						||((PlastC.x<rect.right)&&(PlastC.x>rect.left)&&(PlastC.y<rect.bottom)&&(PlastC.y>rect.top)))
					{
						if (Pcount==1)
							pDC->MoveTo(PnowC);
						else
						{
							pDC->MoveTo(PlastC);
							pDC->LineTo(PnowC);
						}
					}
					PlastA = PnowA; PlastB = PnowB; PlastC = PnowC;
			
				}
			}
			if (c_Flag!=1)
			{
				pOld = pDC->SelectObject(&theApp.PenAD);
				pDC->MoveTo(MidP);
				pDC->LineTo(MidP.x + pDoc->pFile->z.R1/ZPS,MidP.y - pDoc->pFile->z.X1/ZPS);
				pDC->Ellipse(MidP.x + pDoc->pFile->z.R1/ZPS-3,MidP.y - pDoc->pFile->z.X1/ZPS-3,MidP.x + pDoc->pFile->z.R1/ZPS+3,MidP.y - pDoc->pFile->z.X1/ZPS+3);
				pOld = pDC->SelectObject(&theApp.PenBD);
				pDC->MoveTo(MidP);
				pDC->LineTo(MidP.x + pDoc->pFile->z.R2/ZPS,MidP.y - pDoc->pFile->z.X2/ZPS);
				pDC->Ellipse(MidP.x + pDoc->pFile->z.R2/ZPS-3,MidP.y - pDoc->pFile->z.X2/ZPS-3,MidP.x + pDoc->pFile->z.R2/ZPS+3,MidP.y - pDoc->pFile->z.X2/ZPS+3);
				pOld = pDC->SelectObject(&theApp.PenCD);
				pDC->MoveTo(MidP);
				pDC->LineTo(MidP.x + pDoc->pFile->z.R3/ZPS,MidP.y - pDoc->pFile->z.X3/ZPS);
				pDC->Ellipse(MidP.x + pDoc->pFile->z.R3/ZPS-3,MidP.y - pDoc->pFile->z.X3/ZPS-3,MidP.x + pDoc->pFile->z.R3/ZPS+3,MidP.y - pDoc->pFile->z.X3/ZPS+3);
			}
		}
		else
		{
			int c_Flag;
			c_Flag =pDoc->pFile->GetCurrentZ(CursorNum1+1,m_pDlg->Ua,m_pDlg->Ub,m_pDlg->Uc,m_pDlg->Ia,m_pDlg->Ib,m_pDlg->Ic,Type,m_pDlg->LD);
			if (c_Flag==1)
			{
				pDC->TextOutW(10,10,_T("���������޷����㣬�뽫�����ƣ�"));
				return 0;
			}
			pOld = pDC->SelectObject(&theApp.PenAD);
			pDC->MoveTo(MidP);
			pDC->LineTo(MidP.x + pDoc->pFile->z.R1/ZPS,MidP.y - pDoc->pFile->z.X1/ZPS);
			pDC->Ellipse(MidP.x + pDoc->pFile->z.R1/ZPS-3,MidP.y - pDoc->pFile->z.X1/ZPS-3,MidP.x + pDoc->pFile->z.R1/ZPS+3,MidP.y - pDoc->pFile->z.X1/ZPS+3);
			pOld = pDC->SelectObject(&theApp.PenBD);
			pDC->MoveTo(MidP);
			pDC->LineTo(MidP.x + pDoc->pFile->z.R2/ZPS,MidP.y - pDoc->pFile->z.X2/ZPS);
			pDC->Ellipse(MidP.x + pDoc->pFile->z.R2/ZPS-3,MidP.y - pDoc->pFile->z.X2/ZPS-3,MidP.x + pDoc->pFile->z.R2/ZPS+3,MidP.y - pDoc->pFile->z.X2/ZPS+3);
			pOld = pDC->SelectObject(&theApp.PenCD);
			pDC->MoveTo(MidP);
			pDC->LineTo(MidP.x + pDoc->pFile->z.R3/ZPS,MidP.y - pDoc->pFile->z.X3/ZPS);
			pDC->Ellipse(MidP.x + pDoc->pFile->z.R3/ZPS-3,MidP.y - pDoc->pFile->z.X3/ZPS-3,MidP.x + pDoc->pFile->z.R3/ZPS+3,MidP.y - pDoc->pFile->z.X3/ZPS+3);
		}
	
		CString CSName,CSRX,CSZtheta;

		switch(Type)
		{
		case 1:
				m_pDlg->ImpList.InsertItem(0,_T("A��Ե�"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R1,pDoc->pFile->z.X1);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z1),arg(pDoc->pFile->z.Z1)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(0,1,CSRX);
				m_pDlg->ImpList.SetItemText(0,2,CSZtheta);
				m_pDlg->ImpList.InsertItem(1,_T("B��Ե�"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R2,pDoc->pFile->z.X2);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z2),arg(pDoc->pFile->z.Z2)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(1,1,CSRX);
				m_pDlg->ImpList.SetItemText(1,2,CSZtheta);
				m_pDlg->ImpList.InsertItem(2,_T("C��Ե�"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R3,pDoc->pFile->z.X3);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z3),arg(pDoc->pFile->z.Z3)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(2,1,CSRX);
				m_pDlg->ImpList.SetItemText(2,2,CSZtheta);
			break;
		case 2:
				m_pDlg->ImpList.InsertItem(0,_T("A��"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R1,pDoc->pFile->z.X1);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z1),arg(pDoc->pFile->z.Z1)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(0,1,CSRX);
				m_pDlg->ImpList.SetItemText(0,2,CSZtheta);
				m_pDlg->ImpList.InsertItem(1,_T("B��"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R2,pDoc->pFile->z.X2);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z2),arg(pDoc->pFile->z.Z2)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(1,1,CSRX);
				m_pDlg->ImpList.SetItemText(1,2,CSZtheta);
				m_pDlg->ImpList.InsertItem(2,_T("C��"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R3,pDoc->pFile->z.X3);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z3),arg(pDoc->pFile->z.Z3)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(2,1,CSRX);
				m_pDlg->ImpList.SetItemText(2,2,CSZtheta);
			break;
		case 3:
				m_pDlg->ImpList.InsertItem(0,_T("AB���"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R1,pDoc->pFile->z.X1);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z1),arg(pDoc->pFile->z.Z1)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(0,1,CSRX);
				m_pDlg->ImpList.SetItemText(0,2,CSZtheta);
				m_pDlg->ImpList.InsertItem(1,_T("BC���"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R2,pDoc->pFile->z.X2);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z2),arg(pDoc->pFile->z.Z2)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(1,1,CSRX);
				m_pDlg->ImpList.SetItemText(1,2,CSZtheta);
				m_pDlg->ImpList.InsertItem(2,_T("CA���"));
				CSRX.Format(_T("%.2f+j%.2f"),pDoc->pFile->z.R3,pDoc->pFile->z.X3);
				CSZtheta.Format(_T("%.2f��%.2f��"),abs(pDoc->pFile->z.Z3),arg(pDoc->pFile->z.Z3)*180/(splab::PI));
				m_pDlg->ImpList.SetItemText(2,1,CSRX);
				m_pDlg->ImpList.SetItemText(2,2,CSZtheta);
			break;
		}
	}


	return 0;
}


void CImpView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);
	MPos = point;
	int space = rect.Width()*0.05;
	if ((MPos.x>space)&&(MPos.y>space)&&(MPos.x<rect.right-space)&&(MPos.y<rect.bottom-space))
	{
		ZoomFlag = 1;
		if (ZPS*SPD > 0.1)
			ZPS = ZPS / 2;
		Invalidate();
	}
	else
		MPos = (-2,-2);
	CView::OnLButtonDown(nFlags, point);
}


void CImpView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);
	MPos = point;
	int space = rect.Width()*0.05;
	if ((MPos.x>space)&&(MPos.y>space)&&(MPos.x<rect.right-space)&&(MPos.y<rect.bottom-space))
	{
		ZoomFlag = -1;
		if (ZPS*SPD < 100)
			ZPS = ZPS * 2;
		Invalidate();
	}
	else
		MPos = (-2,-2);
	CView::OnRButtonDown(nFlags, point);
}


void CDlgImp::OnBnClickedImprst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_pView->MPos = (-1,-1);
	this->m_pView->ZPS = this->m_pView->defaultZPS;
	this->m_pView->SPD = this->m_pView->defaultSPD;
	this->m_pView->MidP = (0,0);
	this->m_pView->MidP0 = (0,0);
	this->m_pView->MidPLast = (0,0);
	this->m_pView->ZoomFlag = 0;
	this->m_pView->Invalidate();
}


void CDlgImp::OnBnClickedDisploc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd* pWnd=GetDlgItem(IDC_DispLoc);
	pWnd->EnableWindow(FALSE);
	if (this->m_pView->LocFlag==0)
	{
		this->m_pView->LocFlag =1;
		pWnd->SetWindowTextW(_T("�����迹�켣"));
	}
	else
	{
		this->m_pView->LocFlag =0;
		pWnd->SetWindowTextW(_T("��ʾ�迹�켣"));
	}
	this->m_pView->Invalidate();
	pWnd->EnableWindow(TRUE);
}


void CDlgImp::OnNMClickBdlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_pView->Invalidate();
	//m_pView->UpdateWindow();
	*pResult = 0;
}


int CDlgImp::refresh_BdList(void)
{
	BdListOuter.DeleteAllItems();
	int totalNum = BdList.size();
	for(int i=0; i<totalNum;i++)
	{
		BdListOuter.InsertItem(LVIF_TEXT | LVIF_STATE,i,BdList[i]->Name,0,LVIS_SELECTED,0,0);
		//BdListCtrl.SetItemText(i,1,pDoc->pFile->AVector[i]->name);
	}
	return 0;
}


void CDlgImp::OnLvnItemchangedBdlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pView->Invalidate();
	m_pView->UpdateWindow();
	*pResult = 0;
}


void CDlgImp::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	//CDialogEx::OnClose();
}


void CDlgImp::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void CDlgImp::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	this->pDoc->pDlgImp = NULL;
	delete this;
	CDialogEx::PostNcDestroy();
}
