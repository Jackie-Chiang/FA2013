// DlgForm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgForm.h"
#include "afxdialogex.h"
#include "uniclass.h"
#include "calc.h"
#include "AChannel.h"
#include <math.h>
#include <algorithm>
#include <numeric>
#include "DlgVName.h"

// DlgForm �Ի���
//std::map<CString,double> Constants;
extern std::map<CString,double> Constants;
extern std::map<CString,CString> Funcs;
extern std::map<CString,CString> FxDes;
class CDlgform;
class CDlgVName;

IMPLEMENT_DYNAMIC(CDlgForm, CDialogEx)

CDlgForm::CDlgForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgForm::IDD, pParent)
	, m_pView(NULL)
	, t_VChannel(NULL)
	, t_VName(_T(""))
{

}

CDlgForm::~CDlgForm()
{
}

void CDlgForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChanList, AList);
	DDX_Control(pDX, IDC_EDIT1, Input);
	DDX_Control(pDX, IDC_EDIT2, Status);
	DDX_Control(pDX, IDC_VList, VList);
	DDX_Control(pDX, IDC_ConList, ConstList);
	DDX_Control(pDX, IDC_FunList, FxList);
}


BEGIN_MESSAGE_MAP(CDlgForm, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_ChanList, &CDlgForm::OnNMDblclkChanlist)
	ON_NOTIFY(NM_DBLCLK, IDC_ConList, &CDlgForm::OnNMDblclkConlist)
	ON_BN_CLICKED(IDC_GEN, &CDlgForm::OnBnClickedGen)
	ON_BN_CLICKED(IDC_INSERT, &CDlgForm::OnBnClickedInsert)
	ON_NOTIFY(NM_DBLCLK, IDC_FunList, &CDlgForm::OnNMDblclkFunlist)
	ON_NOTIFY(NM_CLICK, IDC_VList, &CDlgForm::OnNMClickVlist)
	ON_NOTIFY(NM_KILLFOCUS, IDC_VList, &CDlgForm::OnNMKillfocusVlist)
	ON_NOTIFY(NM_HOVER, IDC_FunList, &CDlgForm::OnNMHoverFunlist)
	ON_NOTIFY(NM_CLICK, IDC_FunList, &CDlgForm::OnNMClickFunlist)
	ON_NOTIFY(NM_KILLFOCUS, IDC_FunList, &CDlgForm::OnNMKillfocusFunlist)
END_MESSAGE_MAP()


// DlgForm ��Ϣ�������


BOOL CDlgForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Status.SetWindowTextW(_T("������"));

	CString str1,str2;
	int n;
	CRect listRect;
	//������չ���
	DWORD styles = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	//��ʼ��ͨ���б�
	ListView_SetExtendedListViewStyleEx(AList.m_hWnd, styles, styles );
	AList.GetClientRect(&listRect);
	AList.InsertColumn(0,_T("���"),LVCFMT_LEFT,listRect.Width()/4,-1);
	AList.InsertColumn(1,_T("ͨ��"),LVCFMT_LEFT,listRect.Width()/4*3,-1);
	int m_ANumber = pDoc->pFile->m_ANumber;
	for(int i=0; i<m_ANumber;i++)
	{
		str1.Format(_T("A%d"),i+1);
		AList.InsertItem(LVIF_TEXT | LVIF_STATE,i,str1,0,LVIS_SELECTED,0,0);
		AList.SetItemText(i,1,pDoc->pFile->AVector[i]->name);
	}
	//��ʼ������ͨ���б�
	ListView_SetExtendedListViewStyleEx(VList.m_hWnd, styles, styles );
	VList.GetClientRect(&listRect);
	VList.InsertColumn(0,_T("���"),LVCFMT_LEFT,listRect.Width()/4,-1);
	VList.InsertColumn(1,_T("����ͨ��"),LVCFMT_LEFT,listRect.Width()/4*3,-1);
	int m_VNumber = pDoc->pFile->m_VNumber;
	for(int i=0; i<m_VNumber;i++)
	{
		str1.Format(_T("V%d"),i+1);
		VList.InsertItem(LVIF_TEXT | LVIF_STATE,i,str1,0,LVIS_SELECTED,0,0);
		VList.SetItemText(i,1,pDoc->pFile->VVector[i]->name);
	}
	//��ʼ�������б�
	initConst(&Constants);
	ListView_SetExtendedListViewStyleEx(ConstList.m_hWnd, styles, styles );
	ConstList.GetClientRect(&listRect);
	ConstList.InsertColumn(0,_T("����"),LVCFMT_LEFT,listRect.Width()/4,-1);
	ConstList.InsertColumn(1,_T("ֵ"),LVCFMT_LEFT,listRect.Width()/4*3,-1);
	std::map<CString, double>::iterator it_Con = Constants.begin();
	for(int i=0; it_Con != Constants.end(); ++it_Con ,++i)
	{
		ConstList.InsertItem(LVIF_TEXT | LVIF_STATE,i,it_Con->first,0,LVIS_SELECTED,0,0);
		str2.Format(_T("%f"),it_Con->second);
		ConstList.SetItemText(i,1,str2);
	}
	//��ʼ�������б�
	initFunc(&Funcs,&FxDes);
	ListView_SetExtendedListViewStyleEx(FxList.m_hWnd, styles, styles );
	FxList.GetClientRect(&listRect);
	FxList.InsertColumn(0,_T("����"),LVCFMT_LEFT,listRect.Width()/3,-1);
	FxList.InsertColumn(1,_T("����"),LVCFMT_LEFT,listRect.Width()/3*2,-1);
	std::map<CString,CString>::iterator it_Fx = Funcs.begin();
	for(int i=0; it_Fx != Funcs.end(); ++it_Fx ,++i)
	{
		n = _wtoi(it_Fx->second.Right(1));
		str1 = it_Fx->first+_T("()");
		//for(int j=0; i<n; ++j)
		//{
		//}
		FxList.InsertItem(LVIF_TEXT | LVIF_STATE,i,str1,0,LVIS_SELECTED,0,0);
		str2 = it_Fx->second.Left(it_Fx->second.GetLength()-1);
		FxList.SetItemText(i,1,str2);
	}
	//
	////////////////////////////////////////////////////////////////

	//������ͼ������ʾͨ��
	UINT TargetCtrlID = IDC_VVIEW;  
	CWnd *pWnd = this->GetDlgItem(TargetCtrlID);  
	CRect RectTargetCtrl;  
	pWnd->GetWindowRect(RectTargetCtrl);  
	this->ScreenToClient(RectTargetCtrl);  
	m_pView = (CVView*)RUNTIME_CLASS(CVView)->CreateObject();
	(m_pView->pDoc)=pDoc;
	m_pView->m_pDlg=this;
	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = 3000;
	sizeTotal.cy = RectTargetCtrl.Height();
	m_pView->SetScrollSizes(MM_TEXT, sizeTotal);
	//��Ŀ��λ�ö�̬������ͼ
	if (NULL==m_pView)  
	{  
	return FALSE;  
	}  
	m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, RectTargetCtrl, this, TargetCtrlID);

	GetDlgItem (IDC_INPUT)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgForm::OnNMDblclkChanlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int i = 0;
	CString str1;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	i = pNMListView->iItem;//��
	str1.Format(_T("A%d"),i+1);
	Input.ReplaceSel(str1,TRUE);
	Input.SetFocus();
	*pResult = 0;
}

void CDlgForm::OnNMDblclkConlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int i = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	i = pNMListView->iItem;//��
	CString str1(ConstList.GetItemText(i,0));
	Input.ReplaceSel(str1,TRUE);
	Input.SetFocus();
	*pResult = 0;
}

void CDlgForm::OnNMDblclkFunlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	i = pNMListView->iItem;//��

	CString str1(FxList.GetItemText(i,0));
	str1.Remove(_T('('));
	str1.Remove(_T(')'));
	int n = _wtoi(Funcs[str1].Right(1));
	if(n==0)
	{
		n=1;
	}

	str1 += _T('(');
	for(int j=1; j<n; ++j)
	{
		str1+=_T(',');
	}
	str1 += _T(')');

	Input.ReplaceSel(str1,TRUE);
	int s,e;
	Input.SetFocus();
	Input.GetSel(s,e);
	Input.SetSel(s-n,e-n,FALSE);
	*pResult = 0;
}
// E:\fa_\FA2013\DlgForm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FA2013.h"
#include "DlgForm.h"


// CVView

IMPLEMENT_DYNCREATE(CVView, CScrollView)

CVView::CVView()
: m_pDlg(NULL)
{

}

CVView::~CVView()
{
}


BEGIN_MESSAGE_MAP(CVView, CScrollView)
	ON_WM_MOUSEACTIVATE()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CVView ��ͼ

void CVView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	CSize bar;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal = this->GetTotalSize();
	//GetScrollBarSizes(bar);
	//sizeTotal.cy -= bar.cx;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CVView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	CDC m_DC;
	if(!m_DC.CreateCompatibleDC(NULL))				
	{														
		::PostQuitMessage(0);
	}
	this->DrawVirtual(&m_DC);
	m_DC.DeleteDC();
	// TODO: �ڴ���ӻ��ƴ���
}


// CVView ���

#ifdef _DEBUG
void CVView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CVView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVView ��Ϣ�������


int CVView::DrawVirtual(CDC* m_DC)
{
	CRect bkgRect;
	this->GetClientRect(bkgRect);
	CPoint pPoint = this->GetScrollPosition();
	CSize realSize;
	int startSample, endSample;
	int lSpace = 20;
	CDC* pDC= this->GetDC();
	CBitmap m_Bmp;
	m_Bmp.CreateCompatibleBitmap(pDC, bkgRect.Width(), bkgRect.Height());
	CBitmap* bOld = (CBitmap*)(m_DC->SelectObject(&m_Bmp));

	realSize.cx = (LONG)((m_pDlg->pDoc->pFile->m_TotalSampleNum)*
		(m_pDlg->pDoc->pFile->m_drawParam.SPScale))+lSpace;
	realSize.cy = bkgRect.Height();
	SetScrollSizes(MM_TEXT,realSize);

	m_DC->DPtoLP(&bkgRect);
	m_DC->FillSolidRect(bkgRect,RGB(0,0,0));
	if(NULL!=m_pDlg->t_VChannel)
	{
		startSample=(int)(pPoint.x/(m_pDlg->pDoc->pFile->m_drawParam.SPScale));
		endSample=(int)((bkgRect.Width()+pPoint.x)/(m_pDlg->pDoc->pFile->m_drawParam.SPScale));
		m_pDlg->t_VChannel->drawChannel(m_DC,CPoint(lSpace,bkgRect.Height()/2),startSample,endSample,m_pDlg->pDoc->pFile->m_drawParam);
		//�����ֵ
		CFont* def_font = m_DC->SelectObject(&theApp.sfont);
		m_DC->SetTextColor(Yellow);
		m_DC->SetBkMode(TRANSPARENT);
		CString max1,max2;
		max1.Format(_T("%.2f"),m_pDlg->t_VChannel->maxAData);
		max2.Format(_T("-%.2f"),m_pDlg->t_VChannel->maxAData);
		m_DC->TextOutW(0,0,max1);
		m_DC->TextOutW(0,bkgRect.Height()-15,max2);
		m_DC->SelectObject(def_font);
	}
	else
	{
		m_DC->FillSolidRect(bkgRect,RGB(0,0,0));
	}
	pDC->BitBlt(0, 0, bkgRect.Width(), bkgRect.Height(), m_DC, 0, 0, SRCCOPY);
	m_DC->SelectObject(bOld);
	m_Bmp.DeleteObject();
	m_DC->DeleteDC();
	ReleaseDC(pDC);
	return 0;
}


int CVView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return CScrollView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


int CDlgForm::initConst(std::map<CString, double>* con)
{
	std::map<CString, double>* Constants = con;
	(*Constants)[_T("PI")]=3.14159265;
	(*Constants)[_T("EXP")]=2.71828183;
	(*Constants)[_T("SQRT2")]=1.41421356;
	(*Constants)[_T("SQRT3")]=1.73205080;
	return 0;
}

int CDlgForm::initFunc(std::map<CString,CString>* fx,std::map<CString,CString>* des)
{
	(*fx)[_T("abs")]="ȡ����ֵ��1";
	(*des)[_T("abs")]="����һ��������";
	(*fx)[_T("sin")]="ȡ����ֵ��1";
	(*des)[_T("sin")]="����һ��������";
	
	(*fx)[_T("harm_amp")]="ȡг����ֵ��2";
	(*des)[_T("harm_amp")]="��������������ͨ����������";
	(*fx)[_T("basewave")]="ȡ��������/��ֵ/��ǡ�2";
	(*des)[_T("basewave")]="��������������ͨ�������ͣ�1-���Σ�2-��ֵ��3-��ǡ�";
	(*fx)[_T("imp")]="ȡ�迹ʵ��/�鲿/ģֵ/��ǡ�3";
	(*des)[_T("imp")]="����������������ѹ�����������ͣ�1-ʵ����2-�鲿��3-ģֵ��4-��ǡ�";
	(*fx)[_T("power_p")]="ȡһ�Ի���ͨ���й�����֮�͡�0";
	(*des)[_T("power_p")]="����ż��������������Ϊ��ѹ����������ѹ������...";
	(*fx)[_T("power_q")]="ȡһ�Ի���ͨ���޹�����֮�͡�0";
	(*des)[_T("power_q")]="����ż��������������Ϊ��ѹ����������ѹ������...";
	(*fx)[_T("power_s")]="ȡһ�Ի���ͨ�����ڹ���֮�͡�0";
	(*des)[_T("power_s")]="����ż��������������Ϊ��ѹ����������ѹ������...";
	(*fx)[_T("make_sine")]="���ɱ�׼���Ҳ���3";
	(*des)[_T("make_sine")]="����������������ֵ�����࣬Ƶ�ʡ�";
	(*fx)[_T("make_complex")]="���ɸ�����3";
	(*des)[_T("make_complex")]="��������������������Ϊ���ͣ���Ϊ1������ʵ�����鲿����Ϊ2�������ֵ����ǣ��Ƕȣ���";
	(*fx)[_T("complex")]="������ʵ��/�鲿/ģֵ/��ǡ�2";
	(*des)[_T("complex")]="���ܶ�����������һ��Ϊͨ�����ڶ���Ϊ���ͣ�1-ʵ����2-�鲿��3-ģֵ��4-��ǡ�";
	return 0;
}

void CVView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnUpdate(NULL,0,NULL);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}



BOOL CVView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CScrollView::OnEraseBkgnd(pDC);
}


void CDlgForm::OnBnClickedGen()
{
	CString input;
	CRect bkgRect;
	m_pView->GetClientRect(bkgRect);
	int len = Input.LineLength(Input.LineIndex(0));
	Input.GetLine(0, input.GetBuffer(len), len);
	input.ReleaseBuffer(len);

	CString result;
	if(exam(&result,input, pDoc->pFile))
	{
		t_VChannel = NULL;
		Status.SetWindowTextW(result);
		m_pView->Invalidate();
		m_pView->UpdateWindow();
		return;
	}

	if(t_VChannel == NULL)
		t_VChannel = new AChannel;
	else
	{
		//delete t_VChannel;
		t_VChannel = new AChannel;
	}

	input.Insert(0,_T("("));
	input+=_T(")");

	*t_VChannel = EVA(input, pDoc->pFile);

	if(t_VChannel->uu == _T("ERR"))
	{
		result = _T("��ʽ���������г��ִ������鹫ʽ��");
		Status.SetWindowTextW(result);
		delete t_VChannel;
		t_VChannel = NULL;
		m_pView->Invalidate();
		m_pView->UpdateWindow();
		return;
	}

	t_VChannel->isReal = 0;
	t_VChannel->uu = input;
	t_VChannel->ph=_T("V");

	//����ͨ����ͼ����
	int VSpace = (int)(bkgRect.Height()*0.95);
	double max1,max2;
	t_VChannel->m_drawPara.VSpace=VSpace;
	t_VChannel->m_drawPara.defultVSpace=VSpace;
	max1 = *max_element(t_VChannel->AData.begin(),t_VChannel->AData.end());
	max2 = -*min_element(t_VChannel->AData.begin(),t_VChannel->AData.end());
	max1 = (max1>max2)?max1:max2;
	t_VChannel->maxAData = max1;
	t_VChannel->m_drawPara.defaultUPScale=max1/(VSpace/2);
	t_VChannel->m_drawPara.UPScale=t_VChannel->m_drawPara.defaultUPScale;
	t_VChannel->name=_T("");
	///////////////////
	result = _T("��ʽ�����ɹ���");
	Status.SetWindowTextW(result);
	m_pView->Invalidate();
	m_pView->UpdateWindow();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void CDlgForm::OnBnClickedInsert()
{
	if (NULL == t_VChannel)
	{
		MessageBox(_T("������������ͨ���ٲ��룡"),_T("����")); 
	}
	else
	{
		CDlgVName vnDlg;
		if(vnDlg.DoModal() == IDOK)
		{
			t_VName = vnDlg.t_VName;
			t_VChannel->name = t_VName;
			//t_VChannel->ph=_T("V");
			pDoc->pFile->VVector.push_back(t_VChannel);
			pDoc->pFile->m_VNumber += 1;
			refresh_VList();

			pDoc->pFile->AVector.push_back(t_VChannel);
			pDoc->pFile->m_ANumber += 1;
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
		}
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}




int CDlgForm::refresh_VList(void)
{
	CString str1;
	int m_VNumber = pDoc->pFile->m_VNumber;
	VList.DeleteAllItems();
	for(int i=0; i<m_VNumber;i++)
	{
		str1.Format(_T("V%d"),i+1);
		VList.InsertItem(LVIF_TEXT | LVIF_STATE,i,str1,0,LVIS_SELECTED,0,0);
		VList.SetItemText(i,1,pDoc->pFile->VVector[i]->name);
	}
	return 0;
}


void CDlgForm::OnNMClickVlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString str1;
	int i = pNMListView->iItem;//��
	t_VChannel = pDoc->pFile->VVector[i];
	str1 = _T("������ʾ����ͨ���� ��");
	str1 += pDoc->pFile->VVector[i]->name + _T("����");
	str1 += _T("\r\n��ʽΪ�� ");
	str1 += pDoc->pFile->VVector[i]->uu + _T(" ��");
	Status.SetWindowTextW(str1);
	m_pView->Invalidate();
	m_pView->UpdateWindow();
	*pResult = 0;
}


void CDlgForm::OnNMKillfocusVlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Status.SetWindowTextW(_T("������"));
	t_VChannel = NULL;
	m_pView->Invalidate();
	m_pView->UpdateWindow();
	*pResult = 0;
}


void CDlgForm::OnNMHoverFunlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CDlgForm::OnNMClickFunlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString str;
	int i = pNMListView->iItem;//��

	CString str1(FxList.GetItemText(i,0));
	str1.Remove(_T('('));
	str1.Remove(_T(')'));
	str = FxDes[str1];
	Status.SetWindowTextW(str);

	*pResult = 0;
}


void CDlgForm::OnNMKillfocusFunlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Status.SetWindowTextW(_T("������"));
	*pResult = 0;
}
