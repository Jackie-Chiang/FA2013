#pragma once
#include "afx.h"
#include <vector>
#include "AChannel.h"
#include "uniclass.h"
#include "ComTime.h"


class CDatFile :
	public CFile
{
public:
	CDatFile(void);
	~CDatFile(void);
};

class CCfgFile :
	public CStdioFile
{
public:
	CCfgFile(void);
	~CCfgFile(void);
	CString ReadLine(void);//��ANSI�ļ��ж�ȡһ��CString
};



class CComtrade
{
public:
	CComtrade(const CString& FileName);
	~CComtrade(void);
	AChannel Evaluator(const CString& inputExp);                           //��ʽ��ֵ��
//protected:
	CComtrade(void);
	CDatFile pDatFile;
	CCfgFile pCfgFile;
	CString m_Line1;
	CString m_Line2;
	int m_TotalNumber;
	int m_ANumber;
	int m_DNumber; 
	int m_VNumber;
	std::vector<unsigned int> Sample;
	std::vector<int> Time;
	std::vector<AChannel*> AVector; 
	std::vector<DChannel*> DVector;
	std::vector<AChannel*> VVector;
	double m_LF;   //line frequency
	int m_NRates;
	std::vector<SampleRate> m_SampleRate;
	int m_TotalSampleNum;
	CComTime m_StartTime;
	CComTime m_EndTime;
	CString m_DataFileType;
	double m_TimeMult;

	double maxVoltageData;
	double maxCurrentData;
	double maxFrequencyData;

	drawParaCom m_drawParam;
public:
	//������������
	std::vector<ChannelGroup> m_AChannelGroup;//ģ��ͨ����
	int FormAChannelGroup(void);
	Seq_Comp CurentSeqComp[2];    //��ǰ���������Ĭ�����ͬʱ��ʾ���������ͨ��
	int GetCurrentSeqComp(int CurrentPoint, int ch_A, int ch_B, int ch_C, int Index);
	//�迹��������
	Z z;
	int GetCurrentZ(int CurrentPoint, int ch_UA, int ch_UB, int ch_UC, int ch_IA, int ch_IB, int ch_IC , int Type, LineData TempData);
	//ĸ���������

	//
	double GetPointTime(int sampPoint);
	// ��õ�ͨ��
	int getPointChan(int scrollPos, int pointPos);
	int getTotalAVSpace(void);
	int getChanPos(int chanNum);
	// ĸ�����
	int GetCurrentBusDiff(int CurrentPoint, int ch_IA1, int ch_IB1, int ch_IC1, int ch_IA2, int ch_IB2, int ch_IC2, int Type);
	BusIDiff dI;

	//��������
	int GetPower(int ch_UA, int ch_UB, int ch_UC, int ch_IA, int ch_IB, int ch_IC,CString NAME);
};

