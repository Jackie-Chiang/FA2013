
// FA2013.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "FA2013.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "FA2013Doc.h"
#include "AView.h"
#include "DView.h"
#include "ThreadFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFA2013App

BEGIN_MESSAGE_MAP(CFA2013App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CFA2013App::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
//	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
ON_COMMAND(ID_FILE_OPEN, &CFA2013App::OnFileOpen)
END_MESSAGE_MAP()


// CFA2013App ����

CFA2013App::CFA2013App()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("FA2013.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

	PenA.CreatePen(PS_SOLID,1,Yellow);//��
	PenB.CreatePen(PS_SOLID,1,Green);//��
	PenC.CreatePen(PS_SOLID,1,Red);//��
	PenN.CreatePen(PS_SOLID,1,White);//��
	PenF.CreatePen(PS_SOLID,1,Orange);//��
	PenAD.CreatePen(PS_DASH,1,Yellow);
	PenBD.CreatePen(PS_DASH,1,Green);//��
	PenCD.CreatePen(PS_DASH,1,Red);//��
	
	PenV.CreatePen(PS_SOLID,1,Virtual);
	PenCur.CreatePen(PS_SOLID,2,RGB(187,255,255));
	BrushA.CreateSolidBrush(Yellow);
	BrushB.CreateSolidBrush(Green);
	BrushC.CreateSolidBrush(Red);
	BrushN.CreateSolidBrush(White);
	BrushF.CreateSolidBrush(Orange);
	BrushV.CreateSolidBrush(Virtual);
	BrushBk.CreateSolidBrush(RGB(0x38,0x8E,0x8E));

	PenGridGray.CreatePen(PS_SOLID,1,Gray);//��
	PenGrid.CreatePen(PS_DASH,1,Gray);
	PenAxis1.CreatePen(PS_SOLID,1,Pink);//�ۺ�ʵ��
	PenAxis2.CreatePen(PS_DASH,1,Orange);//��ɫ����

	APenG1.CreatePen(PS_SOLID,1,Gray00);
	APenG2.CreatePen(PS_SOLID,1,Gray0);
	APenG3.CreatePen(PS_SOLID,1,Gray1);

	Pen0.CreatePen(PS_SOLID,1,Green);
	Pen1.CreatePen(PS_SOLID,1,Red);

	VERIFY(font.CreateFont(
	20,                        // nHeight
	0,                         // nWidth
	0,                         // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	FALSE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	ANSI_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	_T("΢���ź�")));                 // lpszFacename

	sfont.CreateFont(
	16,                        // nHeight
	0,                         // nWidth
	0,                         // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	FALSE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	ANSI_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	_T("΢���ź�"));

}

// Ψһ��һ�� CFA2013App ����

CFA2013App theApp;


// CFA2013App ��ʼ��

BOOL CFA2013App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_FA2013TYPE,
		RUNTIME_CLASS(CFA2013Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CAView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	//AddDocTemplate (new CMultiDocTemplate(IDR_FA2013TYPE, 
 //         RUNTIME_CLASS(CFA2013Doc), 
 //         RUNTIME_CLASS(CChildFrame), 
 //         RUNTIME_CLASS(CDView))); 

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CFA2013App::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CFA2013App ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CFA2013App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CFA2013App �Զ������/���淽��

void CFA2013App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CFA2013App::LoadCustomState()
{
}

void CFA2013App::SaveCustomState()
{
}

// CFA2013App ��Ϣ�������





void CFA2013App::OnFileOpen()
{
	// TODO: �ڴ���������������
	CWinAppEx::OnFileNew();
	CMainFrame  *pMain = (CMainFrame*) AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame*)(pMain->GetActiveFrame());
	CFA2013Doc *pDoc = (CFA2013Doc*)(pChild->GetActiveDocument());
	
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
		pDoc->pFile = new CComtrade(FileName);
		delete IpzsOpenFile;
	}
	else
	{
		delete IpzsOpenFile;
		return;
	}
	//�ͷŷ���ĶԻ���
//	Flag_import=1;
	pDoc->UpdateAllViews(NULL);
	//pDoc->OnFileOpen();
	pDoc->pThread = AfxBeginThread(ThreadFunc,pDoc);

}
