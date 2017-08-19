
// FA2013Doc.h : CFA2013Doc ��Ľӿ�
//


#pragma once
#include "Comtrade.h"
#include "atltypes.h"
#include "uniclass.h"
#include "DlgHarmo.h"
#include "DlgPhase.h"
#include "DlgSeqComp.h"
#include "DlgForm.h"
#include "DlgImp.h"
#include "DlgBusDiff.h"

class CAView;
class CDView;
class CDlgHarmo;
class CDlgPhase;
class CDlgSeqComp;
class CDlgForm;
class CDlgImp;
class CDlgBusDiff;

class CFA2013Doc : public CDocument
{
protected: // �������л�����
	CFA2013Doc();
	DECLARE_DYNCREATE(CFA2013Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CFA2013Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


public:
	CComtrade* pFile;
	afx_msg void OnOpenfile();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	CAView* pAView;
	CDView* pDView;
	CPoint chanPos;
	CSize viewSize;
	// �α�1
	CPoint pCursor1;
	CPoint pCursor2;
	int CursorNum1;
	int CursorNum2;
	afx_msg void OnCursor();
	afx_msg void OnVZoom();
	afx_msg void OnHZoom();
	CursorType m_Cursor;
public:
	afx_msg void OnUpdateCursor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVZoom(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHZoom(CCmdUI *pCmdUI);
	afx_msg void OnFileOpen();
public:
	CDlgHarmo* pDlgHarmo;  //г������
	CDlgPhase* pDlgPhase;   //��������
	CDlgForm* pDlgForm;     //��ʽ�༭��
	CDlgSeqComp* pDlgSeqComp;	//���������
	CDlgImp* pDlgImp;           //�迹��������
	CDlgBusDiff* pDlgBusDiff;   //ĸ���������
	afx_msg void OnHarmonics();
	int ChanNum1;
	int view_Scroll(int chanNum);
	afx_msg void OnPhase();

	afx_msg void OnSeqcomp();
	afx_msg void OnForm();

	afx_msg void OnImp();
	//Multi Thread
	CWinThread* pThread;
	double ThreadPro;

	afx_msg void OnUpdateIndicatorProgress(CCmdUI *pCmdUI);
	afx_msg void OnBusdiff();
	afx_msg void OnPower();
	int exit;
	afx_msg void OnUpdateIndicatorCursor1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorCursor2(CCmdUI *pCmdUI);
};
