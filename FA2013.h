
// FA2013.h : FA2013 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CFA2013App:
// �йش����ʵ�֣������ FA2013.cpp
//

class CFA2013App : public CWinAppEx
{
public:
	CFA2013App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CPen PenA;//��
	CPen PenB;//��
	CPen PenC;//��
	CPen PenN;//��
	CPen PenF;//��

	CPen PenAD;//��
	CPen PenBD;//��
	CPen PenCD;//��

	CPen PenV;
	CPen PenCur;
	CBrush BrushA;
	CBrush BrushB;
	CBrush BrushC;
	CBrush BrushN;
	CBrush BrushF;
	CBrush BrushV;
	CBrush BrushBk;

	//Axis
	CPen APenG1;
	CPen APenG2;
	CPen APenG3;

	CPen PenGridGray;//��
	CPen PenGrid;//�����
	CPen PenAxis1;//�ۺ�ʵ��
	CPen PenAxis2;//��ɫ����
	
	CPen Pen0;//Dͨ��0
	CPen Pen1;//Dͨ��1

	CFont font;
	CFont sfont;
	afx_msg void OnFileOpen();
};

extern CFA2013App theApp;
