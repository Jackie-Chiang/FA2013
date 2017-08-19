
// FA2013Doc.cpp : CFA2013Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FA2013.h"
#endif

#include "FA2013Doc.h"
#include "AView.h"
#include "DView.h"

#include "DlgPower.h"
#include "DlgVName.h"
class CDlgPower;
class CDlgVName;

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFA2013Doc

IMPLEMENT_DYNCREATE(CFA2013Doc, CDocument)

BEGIN_MESSAGE_MAP(CFA2013Doc, CDocument)
	ON_COMMAND(ID_OpenFile, &CFA2013Doc::OnOpenfile)
	ON_COMMAND(ID_CURSOR, &CFA2013Doc::OnCursor)
	ON_COMMAND(ID_VZOOM, &CFA2013Doc::OnVZoom)
	ON_COMMAND(ID_HZOOM, &CFA2013Doc::OnHZoom)
	ON_UPDATE_COMMAND_UI(ID_CURSOR, &CFA2013Doc::OnUpdateCursor)
	ON_UPDATE_COMMAND_UI(ID_VZOOM, &CFA2013Doc::OnUpdateVZoom)
	ON_UPDATE_COMMAND_UI(ID_HZOOM, &CFA2013Doc::OnUpdateHZoom)
	ON_COMMAND(ID_FILE_OPEN, &CFA2013Doc::OnFileOpen)
	ON_COMMAND(ID_Harmonics, &CFA2013Doc::OnHarmonics)
	ON_COMMAND(ID_Phase, &CFA2013Doc::OnPhase)
	ON_COMMAND(ID_SeqComp, &CFA2013Doc::OnSeqcomp)
	ON_COMMAND(ID_Form, &CFA2013Doc::OnForm)
	ON_COMMAND(ID_Imp, &CFA2013Doc::OnImp)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PROGRESS, &CFA2013Doc::OnUpdateIndicatorProgress)
	ON_COMMAND(ID_BusDiff, &CFA2013Doc::OnBusdiff)
	ON_COMMAND(ID_Power, &CFA2013Doc::OnPower)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CURSOR1, &CFA2013Doc::OnUpdateIndicatorCursor1)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CURSOR2, &CFA2013Doc::OnUpdateIndicatorCursor2)
END_MESSAGE_MAP()


// CFA2013Doc ����/����

CFA2013Doc::CFA2013Doc()
: pFile(NULL)
, pAView(NULL)
, chanPos(0)
, pCursor1(0)
, pCursor2(0)
, CursorNum1(0)
, CursorNum2(0)
, m_Cursor(CURSOR)
, pDlgHarmo(NULL)
, pDlgPhase(NULL)
, ChanNum1(0)
, pDlgSeqComp(NULL)
, pDlgForm(NULL)
, pDlgImp(NULL)
, pDlgBusDiff(NULL)
, ThreadPro(0.0)
, pThread(NULL)


{
	// TODO: �ڴ����һ���Թ������
	exit=1;
}

CFA2013Doc::~CFA2013Doc()
{
	exit=0;
	while(this->pThread!=NULL);
	delete pFile;
	pFile=NULL;
}

BOOL CFA2013Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFA2013Doc ���л�

void CFA2013Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CFA2013Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CFA2013Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CFA2013Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFA2013Doc ���

#ifdef _DEBUG
void CFA2013Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFA2013Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFA2013Doc ����


void CFA2013Doc::OnOpenfile()
{
	// TODO: �ڴ���������������
	CFileDialog *IpzsOpenFile;
	CString szGetName;
	IpzsOpenFile = new CFileDialog(true,
		NULL,
		NULL,
		OFN_FILEMUSTEXIST 
		|OFN_HIDEREADONLY,
		TEXT("�ļ�����(*.cfg;*.dat)|*.cfg;*.dat||"));//����һ���Ի���
	if(IpzsOpenFile->DoModal() == IDOK)//�������Ի���ȷ����
	{
		szGetName = IpzsOpenFile->GetPathName();//�õ����ļ���·��
		CString FileName = szGetName.Left(szGetName.GetLength()-4);
		pFile = new CComtrade(FileName);
	}
	else
	{
		delete IpzsOpenFile;
		return;
	}
	delete IpzsOpenFile;//�ͷŷ���ĶԻ���
//	Flag_import=1;
	UpdateAllViews(NULL);
	//CComtrade pFile(FileName);
	//pFile = new CComtrade(_T("E://demo/demo"));
	
	// TODO: �ڴ���������������

}


BOOL CFA2013Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	POSITION pos;
	CView* pView;
	pView=GetNextView(pos);
	while(pos!=NULL)
	{
		  pView=GetNextView(pos); 
		  if(pView->IsKindOf(RUNTIME_CLASS(CAView))==NULL) 
			  pAView=(CAView*)pView; 
		  else if(pView->IsKindOf(RUNTIME_CLASS(CDView))==NULL) 
			  pDView=(CDView*)pView; 
	} 
	// TODO:  �ڴ������ר�õĴ�������

	return TRUE;
}


void CFA2013Doc::OnCursor()
{
	m_Cursor = CURSOR;
}


void CFA2013Doc::OnVZoom()
{
	m_Cursor = VZOOM;
}


void CFA2013Doc::OnHZoom()
{
	m_Cursor = HZOOM;
}


void CFA2013Doc::OnUpdateCursor(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Cursor==CURSOR);
}


void CFA2013Doc::OnUpdateVZoom(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Cursor==VZOOM);
}


void CFA2013Doc::OnUpdateHZoom(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Cursor==HZOOM);
}


void CFA2013Doc::OnFileOpen()
{
	// TODO: �ڴ���������������

	CFA2013App* pApp =(CFA2013App*)AfxGetApp();
	pApp->OnFileOpen();

//	CFileDialog *IpzsOpenFile;
//	CString szGetName;
//	IpzsOpenFile = new CFileDialog(true,
//		NULL,
//		NULL,
//		OFN_FILEMUSTEXIST 
//		|OFN_HIDEREADONLY,
//		TEXT("�ļ�����(*.cfg;*.dat)|*.cfg;*.dat||"));//����һ���Ի���
//	if(IpzsOpenFile->DoModal() == IDOK)//�������Ի���ȷ����
//	{
//		szGetName = IpzsOpenFile->GetPathName();//�õ����ļ���·��
//		CString FileName = szGetName.Left(szGetName.GetLength()-4);
//		pFile = new CComtrade(FileName);
//		delete IpzsOpenFile;
//	}
//	else
//	{
//		delete IpzsOpenFile;
//		return;
//	}
//	//�ͷŷ���ĶԻ���
////	Flag_import=1;
//	UpdateAllViews(NULL);
}


void CFA2013Doc::OnHarmonics()
{
	// TODO: �ڴ���������������
	if(pDlgHarmo == NULL)
	{
		pDlgHarmo =new CDlgHarmo();
		pDlgHarmo->pDoc = this;
		pDlgHarmo->Create(CDlgHarmo::IDD);
	}
	pDlgHarmo->ShowWindow(SW_SHOW);
}


int CFA2013Doc::view_Scroll(int chanNum)
{
	int i = pFile->getChanPos(chanNum);
	if (i<0)
		i=0;
	pAView->ScrollToPosition(CPoint(pAView->GetScrollPosition().x,i));
	return 0;
}


void CFA2013Doc::OnPhase()
{
	// TODO: �ڴ���������������
	if(pDlgPhase == NULL)
	{
		pDlgPhase =new CDlgPhase();
		pDlgPhase->pDoc = this;
		pDlgPhase->Create(CDlgPhase::IDD);
	}
	pDlgPhase->ShowWindow(SW_SHOW);
}


void CFA2013Doc::OnSeqcomp()
{
	// TODO: �ڴ���������������
	if(pDlgSeqComp == NULL)
	{
		pDlgSeqComp =new CDlgSeqComp();
		pDlgSeqComp-> pDoc = this;
		pDlgSeqComp->Create(CDlgSeqComp::IDD);
	}
	pDlgSeqComp->ShowWindow(SW_SHOW);
}


void CFA2013Doc::OnForm()
{
	// TODO: �ڴ���������������
	if(pDlgForm == NULL)
	{
		pDlgForm =new CDlgForm();
		pDlgForm->pDoc = this;
		pDlgForm->Create(CDlgForm::IDD);
	}
	pDlgForm->ShowWindow(SW_SHOW);
}


void CFA2013Doc::OnImp()
{
	// TODO: �ڴ���������������
	if(pDlgImp == NULL)
	{
		pDlgImp =new CDlgImp();
		pDlgImp->pDoc = this;
		pDlgImp->Create(CDlgImp::IDD);
	}
	pDlgImp->ShowWindow(SW_SHOW);
}


void CFA2013Doc::OnUpdateIndicatorProgress(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	CString temp;
	if (ThreadPro<100)
	{
		pCmdUI->Enable();
		temp.Format(_T("��̨������ɶ�: %.2f"),ThreadPro);
		temp = temp +_T("%");
	}
	else
	{
		pCmdUI->Enable(0);
		temp = _T("��̨���������");
	}
	pCmdUI->SetText(temp);

}


void CFA2013Doc::OnBusdiff()
{

	// TODO: �ڴ���������������
	if(pDlgBusDiff == NULL)
	{
		pDlgBusDiff =new CDlgBusDiff();
		pDlgBusDiff->pDoc = this;
		pDlgBusDiff->Create(CDlgBusDiff::IDD);
	}
	pDlgBusDiff->ShowWindow(SW_SHOW);
}


void CFA2013Doc::OnPower()
{
	// TODO: �ڴ���������������
	CDlgPower pDlg;
	pDlg.pDoc = this;
	if(pDlg.DoModal() == IDOK)
	{
		int Ua,Ub,Uc,Ia,Ib,Ic;
		Ua=pDlg.Ua;
		Ub=pDlg.Ub;
		Uc=pDlg.Uc;
		Ia=pDlg.Ia;
		Ib=pDlg.Ib;
		Ic=pDlg.Ic;
		CDlgVName VName;
		if (VName.DoModal() == IDOK)
		{
			CString NAME = VName.t_VName;
			this->pFile->GetPower(Ua,Ub,Uc,Ia,Ib,Ic,NAME);
		}
	}
	UpdateAllViews(NULL);
	this->view_Scroll(this->pFile->m_ANumber);
	UpdateAllViews(NULL);
	
}


void CFA2013Doc::OnUpdateIndicatorCursor1(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CString temp;
	pCmdUI->Enable();
	CComTime aT;
	aT = pFile->m_StartTime + pFile->Time[CursorNum1];
	temp=_T("ʵ�α�ʱ�䣺")+aT.PrintTimeWithDate();
	pCmdUI->SetText(temp);
}


void CFA2013Doc::OnUpdateIndicatorCursor2(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CString temp;
	pCmdUI->Enable();
	CComTime aT;
	aT = pFile->m_StartTime + pFile->Time[CursorNum2];
	temp=_T("���α�ʱ�䣺")+aT.PrintTimeWithDate();
	pCmdUI->SetText(temp);
}
