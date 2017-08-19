#include "stdafx.h"
#include "FA2013.h"
#include "DlgBdChild.h"
#include "splab_vector.h"
#include "DlgBoundry.h"

using splab::PI;
class CDlgBoundry;
// CBdView

IMPLEMENT_DYNCREATE(CBdView, CView)

CBdView::CBdView()
: m_pDlg(NULL)
{

}

CBdView::~CBdView()
{
}

BEGIN_MESSAGE_MAP(CBdView, CView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CBdView ��ͼ

void CBdView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	CPen* pOld;
	CRect bkgRect;
	this->GetClientRect(&bkgRect);
	pDC->FillSolidRect(&bkgRect,RGB(0,0,0));
	CPoint midP;
	midP.x = bkgRect.Height()/2;
	midP.y = bkgRect.Width()/2;
	pOld = pDC->SelectObject(&theApp.PenN);
	pDC->MoveTo(0,midP.y);
	pDC->LineTo(bkgRect.Width(),midP.y);
	pDC->MoveTo(midP.x,0);
	pDC->LineTo(midP.x,bkgRect.Height());
	pDC->SelectObject(pOld);
	if ((m_pDlg!=NULL)&&(m_pDlg->t_Boundry.isVisible))
	{
		m_pDlg->t_Boundry.drawBd(pDC,midP,bkgRect);
	}
	else
	{
		CBitmap bmp;
		bmp.LoadBitmapW(IDB_BITMAP1);
		pDC->SelectObject(&bmp);
	}
}


// CBdView ���

#ifdef _DEBUG
void CBdView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBdView ��Ϣ�������

// DlgBdChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgBdChild.h"
#include "afxdialogex.h"


// CDlgBdParam �Ի���

IMPLEMENT_DYNAMIC(CDlgBdParam, CDialogEx)

CDlgBdParam::CDlgBdParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBdParam::IDD, pParent)
	, m_pView(NULL)
{

}

CDlgBdParam::~CDlgBdParam()
{
}

void CDlgBdParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBdParam, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CDlgBdParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bkgBr.CreateSolidBrush(RGB(255,255,255));

	UINT TargetCtrlID = IDC_ParamStatic;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CBdView*)RUNTIME_CLASS(CBdView)->CreateObject();
	//(m_pView->pDoc)=pDoc;
	//m_pView->m_pDlg=this;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
// CDlgBdParam ��Ϣ�������
HBRUSH CDlgBdParam::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return bkgBr;
}

// DlgBdChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgBdChild.h"
#include "afxdialogex.h"


// CDlgBdPoly �Ի���

IMPLEMENT_DYNAMIC(CDlgBdPoly, CDialogEx)

CDlgBdPoly::CDlgBdPoly(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBdPoly::IDD, pParent)
	, m_pView(NULL)
	, Rset1(20)
	, Xset1(20)
	, Beta(0.125)
	, Alpha(15)
	, Theta(60)
	, m_pDlg(NULL)
	, outerDlg(NULL)
{

}

CDlgBdPoly::~CDlgBdPoly()
{
}

void CDlgBdPoly::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PolyRset, Rset1);
	DDX_Text(pDX, IDC_PolyXset, Xset1);
	DDX_Text(pDX, IDC_PolyTg, Beta);
	DDX_Text(pDX, IDC_PolyAlpha, Alpha);
	DDX_Text(pDX, IDC_PolyTheta, Theta);
}


BEGIN_MESSAGE_MAP(CDlgBdPoly, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PREPOLY, &CDlgBdPoly::OnBnClickedPrePoly)
	ON_BN_CLICKED(IDC_INSPOLY, &CDlgBdPoly::OnBnClickedInsPoly)
END_MESSAGE_MAP()


// CDlgBdPoly ��Ϣ�������


HBRUSH CDlgBdPoly::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return bkgBr;
}




BOOL CDlgBdPoly::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bkgBr.CreateSolidBrush(RGB(255,255,255));

	UINT TargetCtrlID = IDC_PolyStatic;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CBdView*)RUNTIME_CLASS(CBdView)->CreateObject();
	//(m_pView->pDoc)=pDoc;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgBdPoly::OnBnClickedPrePoly()
{
	UpdateData(TRUE);
	m_pDlg->t_Boundry.Rset1 = Rset1;
	m_pDlg->t_Boundry.Xset1 = Xset1;
	m_pDlg->t_Boundry.Beta = Beta;
	m_pDlg->t_Boundry.Alpha = Alpha;
	m_pDlg->t_Boundry.Theta = Theta;
	m_pDlg->t_Boundry.isVisible = 1;
	m_pDlg->t_Boundry.Type = _T("Poly");
	m_pView->m_pDlg=m_pDlg;
	m_pView->Invalidate();
	m_pView->UpdateWindow();
}


void CDlgBdPoly::OnBnClickedInsPoly()
{
	UpdateData(TRUE);
	CBoundry* t_Boundry = new CBoundry;
	t_Boundry->Rset1 = Rset1;
	t_Boundry->Xset1 = Xset1;
	t_Boundry->Beta = Beta;
	t_Boundry->Alpha = Alpha;
	t_Boundry->Theta = Theta;
	t_Boundry->isVisible = 1;
	t_Boundry->Color = 0x00836FFF;

	CString str;
	str.Format(_T("%d"),(m_pDlg->P_num)++);
	t_Boundry->Type = _T("Poly");
	t_Boundry->Name = _T("�����")+str;
	m_pDlg->BdList.push_back(t_Boundry);
	outerDlg->refresh_BdList();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


// DlgBdChild.cpp : ʵ���ļ�
//

// DlgBdChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgBdChild.h"
#include "afxdialogex.h"


// CDlgBdLine �Ի���

IMPLEMENT_DYNAMIC(CDlgBdLine, CDialogEx)

CDlgBdLine::CDlgBdLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBdLine::IDD, pParent)
	, m_pView(NULL)
	, Rset1(5)
	, Xset1(20)
	, Beta(15)
	, m_pDlg(NULL)
{

}

CDlgBdLine::~CDlgBdLine()
{
}

void CDlgBdLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LineRset, Rset1);
	DDX_Text(pDX, IDC_LineXset, Xset1);
	DDX_Text(pDX, IDC_LineBeta, Beta);
}


BEGIN_MESSAGE_MAP(CDlgBdLine, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PreLine, &CDlgBdLine::OnBnClickedPreLine)
	ON_BN_CLICKED(IDC_InsLine, &CDlgBdLine::OnBnClickedInsLine)
END_MESSAGE_MAP()


// CDlgBdLine ��Ϣ�������
BOOL CDlgBdLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bkgBr.CreateSolidBrush(RGB(255,255,255));

	UINT TargetCtrlID = IDC_LineStatic;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CBdView*)RUNTIME_CLASS(CBdView)->CreateObject();
	//(m_pView->pDoc)=pDoc;
	//m_pView->m_pDlg=this;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CDlgBdLine::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return bkgBr;
}
void CDlgBdLine::OnBnClickedPreLine()
{
	UpdateData(TRUE);
	m_pDlg->t_Boundry.Rset1 = Rset1;
	m_pDlg->t_Boundry.Xset1 = Xset1;
	m_pDlg->t_Boundry.Beta = Beta;
	m_pDlg->t_Boundry.isVisible = 1;
	m_pDlg->t_Boundry.Type = _T("Line");
	m_pView->m_pDlg=m_pDlg;
	m_pView->Invalidate();
	m_pView->UpdateWindow();
}

void CDlgBdLine::OnBnClickedInsLine()
{
	UpdateData(TRUE);
	CBoundry* t_Boundry = new CBoundry;
	t_Boundry->Rset1 = Rset1;
	t_Boundry->Xset1 = Xset1;
	t_Boundry->Beta = Beta;
	t_Boundry->isVisible = 1;
	t_Boundry->Color = 0x0087CEFF;
	
	CString str;
	str.Format(_T("%d"),(m_pDlg->L_num)++);
	t_Boundry->Type = _T("Line");
	t_Boundry->Name = _T("ֱ��")+str;
	m_pDlg->BdList.push_back(t_Boundry);
	outerDlg->refresh_BdList();
}


// DlgBdChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgBdChild.h"
#include "afxdialogex.h"


// CDlgBdCircle �Ի���

IMPLEMENT_DYNAMIC(CDlgBdCircle, CDialogEx)

CDlgBdCircle::CDlgBdCircle(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBdCircle::IDD, pParent)
	, m_pView(NULL)
	, Rset1(20)
	, Xset1(20)
	, Alpha(0.5)
{

}

CDlgBdCircle::~CDlgBdCircle()
{
}

void CDlgBdCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CircleRset, Rset1);
	DDX_Text(pDX, IDC_CircleXset, Xset1);
	DDX_Text(pDX, IDC_CircleAlpha, Alpha);
}


BEGIN_MESSAGE_MAP(CDlgBdCircle, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PreCircle, &CDlgBdCircle::OnBnClickedPreCircle)
	ON_BN_CLICKED(IDC_InsCircle, &CDlgBdCircle::OnBnClickedInsCircle)
END_MESSAGE_MAP()


// CDlgBdCircle ��Ϣ�������
BOOL CDlgBdCircle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bkgBr.CreateSolidBrush(RGB(255,255,255));

	UINT TargetCtrlID = IDC_CircleStatic;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CBdView*)RUNTIME_CLASS(CBdView)->CreateObject();
	//(m_pView->pDoc)=pDoc;
	//m_pView->m_pDlg=this;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CDlgBdCircle::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return bkgBr;
}

void CDlgBdCircle::OnBnClickedPreCircle()
{
	UpdateData(TRUE);
	m_pDlg->t_Boundry.Rset1 = Rset1;
	m_pDlg->t_Boundry.Xset1 = Xset1;
	m_pDlg->t_Boundry.Alpha = Alpha;
	m_pDlg->t_Boundry.isVisible = 1;
	m_pDlg->t_Boundry.Type = _T("Circle");
	m_pView->m_pDlg=m_pDlg;
	m_pView->Invalidate();
	m_pView->UpdateWindow();
}

void CDlgBdCircle::OnBnClickedInsCircle()
{
	UpdateData(TRUE);
	CBoundry* t_Boundry = new CBoundry;
	t_Boundry->Rset1 = Rset1;
	t_Boundry->Xset1 = Xset1;
	t_Boundry->Alpha = Alpha;
	t_Boundry->isVisible = 1;
	t_Boundry->Color = 0x00FF83FA;
	
	CString str;
	str.Format(_T("%d"),(m_pDlg->C_num)++);
	t_Boundry->Type = _T("Circle");
	t_Boundry->Name = _T("Բ��")+str;
	m_pDlg->BdList.push_back(t_Boundry);
	outerDlg->refresh_BdList();
}


// DlgBdChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgBdChild.h"
#include "afxdialogex.h"


// CDlgBdRect �Ի���

IMPLEMENT_DYNAMIC(CDlgBdRect, CDialogEx)

CDlgBdRect::CDlgBdRect(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBdRect::IDD, pParent)
	, m_pView(NULL)
	, Rset1(20)
	, Rset2(-5)
	, Xset1(20)
	, Xset2(-5)
{

}

CDlgBdRect::~CDlgBdRect()
{
}

void CDlgBdRect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RectRmax, Rset1);
	DDX_Text(pDX, IDC_RectRmin, Rset2);
	DDX_Text(pDX, IDC_RectXmax, Xset1);
	DDX_Text(pDX, IDC_RectXmin, Xset2);
}


BEGIN_MESSAGE_MAP(CDlgBdRect, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PreRect, &CDlgBdRect::OnBnClickedPreRect)
	ON_BN_CLICKED(IDC_InsRect, &CDlgBdRect::OnBnClickedInsRect)
END_MESSAGE_MAP()


// CDlgBdRect ��Ϣ�������



BOOL CDlgBdRect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bkgBr.CreateSolidBrush(RGB(255,255,255));

	UINT TargetCtrlID = IDC_RectStatic;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CBdView*)RUNTIME_CLASS(CBdView)->CreateObject();
	//(m_pView->pDoc)=pDoc;
	//m_pView->m_pDlg=this;
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CDlgBdRect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return bkgBr;
}


void CDlgBdRect::OnBnClickedPreRect()
{
	UpdateData(TRUE);
	m_pDlg->t_Boundry.Rset1 = Rset1;
	m_pDlg->t_Boundry.Xset1 = Xset1;
	m_pDlg->t_Boundry.Rset2 = Rset2;
	m_pDlg->t_Boundry.Xset2 = Xset2;
	m_pDlg->t_Boundry.isVisible = 1;
	m_pDlg->t_Boundry.Type = _T("Rect");
	m_pView->m_pDlg=m_pDlg;
	m_pView->Invalidate();
	m_pView->UpdateWindow();
}


void CDlgBdRect::OnBnClickedInsRect()
{
	UpdateData(TRUE);
	CBoundry* t_Boundry = new CBoundry;
	t_Boundry->Rset1 = Rset1;
	t_Boundry->Xset1 = Xset1;
	t_Boundry->Rset2 = Rset2;
	t_Boundry->Xset2 = Xset2;
	t_Boundry->isVisible = 1;
	t_Boundry->Color = 0x004876FF;
	
	CString str;
	str.Format(_T("%d"),(m_pDlg->R_num)++);
	t_Boundry->Type = _T("Rect");
	t_Boundry->Name = _T("�����")+str;
	m_pDlg->BdList.push_back(t_Boundry);
	outerDlg->refresh_BdList();
}


int CBdView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
