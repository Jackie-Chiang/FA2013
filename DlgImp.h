#pragma once
#include "FA2013Doc.h"
#include "afxwin.h"
#include "atltypes.h"
#include "Boundry.h"
#include <vector>
#include "afxcmn.h"

class CFA2013Doc;
class CDlgImp;
class CImpView;
// CDlgImp �Ի���

class CDlgImp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImp)

public:
	CDlgImp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImp();

// �Ի�������
	enum { IDD = IDD_Impedance };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFA2013Doc* pDoc;
	CImpView* m_pView;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSetbd();
	CComboBox ImpTypeSel;
	afx_msg void OnCbnSelchangeImptype();
	int Ua,Ub,Uc,Ia,Ib,Ic;//ѡ���ͨ����ʼ��Ϊ-1��
	int SelFlag;     //ͨ���Ƿ���ѡ�� 1:��ѡ��0:δѡ��
	LineData LD;
	std::vector<CBoundry*> BdList;    //�߽��б�
	unsigned int P_num,L_num,C_num,R_num;  //�߽����
	CBoundry t_Boundry;               //Ԥ������ʱ�߽�
	CPoint t_midP;

	afx_msg void OnBnClickedImprst();
	afx_msg void OnBnClickedDisploc();
	CListCtrl BdListOuter;
	afx_msg void OnNMClickBdlist(NMHDR *pNMHDR, LRESULT *pResult);
	int refresh_BdList(void);
	afx_msg void OnLvnItemchangedBdlist(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl ImpList;
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
#pragma once


// CImpView ��ͼ

class CImpView : public CView
{
	DECLARE_DYNCREATE(CImpView)

protected:
	CImpView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CImpView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CFA2013Doc* pDoc;
	CDlgImp* m_pDlg;
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	
	int DrawImp(CDC* pDC);
	// �����λ��
	CPoint MPos;
	CPoint MidP,MidPLast,MidP0;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	double defaultZPS;   //Z/���أ�Ĭ�ϣ�
	double ZPS;          //Z/����
	double defaultSPD;   //����/�̶ȣ�Ĭ�ϣ�
	double SPD;          //����/�̶�
	int ZoomFlag;
	int LocFlag;   //�Ƿ���ʾ�켣 0����ʾ 1��ʾ
	int CursorNum1;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


