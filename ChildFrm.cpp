
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "FA2013.h"

#include "ChildFrm.h"
#include"AView.h"
#include"DView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
//	ON_WM_SETCURSOR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	//GetClientRect(&rect);
	this->GetWindowRect(&rect);
	m_wndSplitter.CreateStatic(this,2,1);
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CAView),CSize(rect.Width(),rect.Height()/4*3),pContext);
	m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CDView),CSize(rect.Width(),100),pContext);
	return true;
	//return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


//BOOL CChildFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	return TRUE;
//	//return CMDIChildWndEx::OnSetCursor(pWnd, nHitTest, message);
//}


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_StatusBar.Create(this);
	static UINT indicators[] = {
		ID_INDICATOR_CURSOR1,
		ID_INDICATOR_CURSOR2,
		ID_INDICATOR_BLANK,
		ID_INDICATOR_PROGRESS};
	m_StatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));
	m_StatusBar.SetPaneStyle(2,SBPS_STRETCH|SBPS_NOBORDERS);

	return 0;
}
