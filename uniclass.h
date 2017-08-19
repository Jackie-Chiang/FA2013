#pragma once

#ifndef _UNICLASS_H_
#define _UNICLASS_H_


#include "stdafx.h"
#define FREQ 50
#include<complex>
struct SampleRate
{
	double samp;
	int endsamp;
};

struct phasor
{
	double Amplitude;//��ֵ
	double phase;//��λ�Ƕ�
};

struct ChannelGroup
{
	CString Name;
	int A;
	int B;
	int C;
	int N;
};

struct Seq_Comp    //�����
{
	CString name;//��ѹor����
	std::complex<double> PSC;   //����
	std::complex<double> NSC;   //����
	std::complex<double> ZSC;   //����
};

struct Z
{
	double R1;
	double X1;
	std::complex<double> Z1;
	double R2;
	double X2;
	std::complex<double> Z2;
	double R3;
	double X3;
	std::complex<double> Z3;
};
struct LineData
{
	std::complex<double> z1;
	std::complex<double> z0;
};

struct BusIDiff
{
	double rIA;
	double rIB;
	double rIC;
	double resIA;
	double resIB;
	double resIC;
};

struct drawParaChan               //��ͼ����������class Channel
{
	int VSpace;                //�������������,ͨ���߶ȣ�����õ���
	int defultVSpace;           //�������������,ͨ���߶ȣ�Ĭ�ϣ�
	double UPScale;            //����ÿ����(V/A/Hz)
	double defaultUPScale; 
};

struct drawParaCom              //��ͼ����������class Comtrade
{
	int defaultVSpace;
	int defaultDVSpace;     //d channel
	int VGap;
	int DGap;
	double defaultVPScale;   //����ÿ����
	double defaultAPScale;
	double defaultHPScale;
	double defaultSPScale;          //������ÿ����(ms)��Ĭ��1.5
	double defaultDPScale;   //Dͨ������ÿ����

	double SPScale;
	double LastSPScale;

	int topSpace;
	int rightSpace;
	int leftSpace;

};

enum CursorType{CURSOR,VZOOM,HZOOM};

#define Yellow  RGB(255,255,0)
#define Green  RGB(0,255,0)
#define Red RGB(255,0,0)
#define White RGB(255,255,255)
#define Orange RGB(255,160,50)
#define Gray RGB(100,100,100)
#define Pink RGB(205,0,205)
#define Gray00 RGB(230,230,230)
#define Gray0 RGB(190,190,190)
#define Gray1 RGB(150,150,150)
#define Virtual RGB(127,255,212)

	

#endif 