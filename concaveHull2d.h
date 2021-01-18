#pragma once

#include <iostream>
#include <math.h>
#include <vector>

#ifdef _WIN32
#include <corecrt_math_defines.h>
#endif // _WIN32

using namespace std;

typedef struct POINT2D
{
	double x;
	double y;

	POINT2D(double otherx, double othery) { x = otherx; y = othery; }
	POINT2D() { x = 0; y = 0; }

}Point2D;


class ConCaveHull
{
public:
	ConCaveHull();
	~ConCaveHull();
	void computeConcaveHull();         // ������磬��������
	void setData(vector<Point2D> pp);  // ��������
	void setData(vector<Point2D> pp, double angThreshold, int nIter); // ������������
	void setParameters(double angThreshold, int nIter);               // ���ò������Ƕ���ֵ�������������Ƕ���ֵ�ϴ�ʱ���Ϊ͹��
	vector<Point2D> getConcaveHull();                                 // ��ȡ���磬��������
protected:
	void bubbleSort();	        //	ð������
	void getAngleDistance();    // ���������ĽǶȺ;���
	void deleteConcavePoints(); // ɾ���Ƕ�С����ֵ�İ���

private:
	vector<Point2D> m_P;	// ��������
	vector<Point2D> m_pCH;  // ����
	int m_nPoints;          // �������ݵĵ���
	double *m_ang;			// ÿ����ķ�λ��
	double *m_dis;			// ÿ���������ĵľ���

	double m_angThreshold;  // �Ƕ���ֵ
	double m_NumIteration;  // ��������

	double m_X0;            // ��������x����
	double m_Y0;            // ��������y����
};