#pragma once
#include <vector>
#include "uniclass.h"

class AChannel
{
public:
	AChannel(void);
	~AChannel(void);
//	AChannel(const AChannel&);
//	AChannel& operator=(const AChannel&);

	AChannel operator+(const AChannel& AChannel2) const;
	AChannel operator+(const double& Num) const;
	AChannel operator-(const AChannel& AChannel2) const;
	AChannel operator-(const double& Num) const;
	AChannel operator*(const AChannel& AChannel2) const;
	AChannel operator*(const double& Num) const;
	AChannel operator/(const AChannel& AChannel2) const;
	AChannel operator/(const double& Num) const;

	friend AChannel operator+(const double& Num,const AChannel& AChannel2);
	friend AChannel operator-(const double& Num,const AChannel& AChannel2);
	friend AChannel operator*(const double& Num,const AChannel& AChannel2);
//	AChannel operator/(const AChannel& AChannel2) const;

public:
	int An;         // index number
	CString name;  // ��¼����
	CString ph;                  // phase: A,B,C or none
	CString ccbm;   // ����������
	CString uu;       // ��λ
	double multiplier;        //����    
	double offset;            //ƫ��
	double skew;              //��ʱ
	int min;               //��Сֵ
	int max;               //���ֵ
	double primary;        //��������
	double secondary;      //�μ�����
	CString PS;               //����ֵΪ�������Ǵμ�
	std::vector<double> AData;
	//���߳�
	std::vector<double> AmpData;
	std::vector<double> PhData;
	std::vector<double> Harmonics;  //�ݴ浱ǰ��г��
	double Ph_base;                 //����FFT�����λֵ(����)
	phasor APhasor;              	// �ݴ浱ǰ������
	bool isReal;

	drawParaChan m_drawPara;
	double maxAData;
	int ThreadFlag;//�жϸ�ͨ���Ƿ�������


public:	
	AChannel(int _An,CString _name, CString _ph, CString _ccbm, CString _uu, double _multiplier, double _offset, double _skew, int _min,int _max,
		double _primary, double _secondary, CString _PS, bool Real);
	int InstFFT(int SamplePoint,std::vector<SampleRate>& m_SampleRate);

	int MyFFT(int start, int end, double SampRate);

	int GetCurrentPhasor(int SamplePoint,std::vector<SampleRate>& m_SampleRate);
	int drawChannel(CDC* p, CPoint pPos,int startSample, int endSample, drawParaCom drawParam);
};

class DChannel
{
public:
	DChannel(void);
	~DChannel(void);
public:
	int Dn;         // index number
	CString name;  // ��¼����
	CString ph;                  // phase: A,B,C or none
	CString ccbm;   // ����������
    int y;                    // ����״̬ 0 or 1 
	std::vector<BOOL> DData;
public:
	DChannel(int _Dn,CString _name, CString _ph, CString _ccbm, int _y);
	int drawChannel(CDC* p, CPoint pPos,int startSample, int endSample, drawParaCom drawParam);

};