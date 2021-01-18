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
	void computeConcaveHull();         // 计算包络，结果不封闭
	void setData(vector<Point2D> pp);  // 设置数据
	void setData(vector<Point2D> pp, double angThreshold, int nIter); // 重载设置数据
	void setParameters(double angThreshold, int nIter);               // 设置参数，角度阈值，迭代次数，角度阈值较大时结果为凸包
	vector<Point2D> getConcaveHull();                                 // 获取包络，结果不封闭
protected:
	void bubbleSort();	        //	冒泡排序
	void getAngleDistance();    // 计算各个点的角度和距离
	void deleteConcavePoints(); // 删除角度小于阈值的凹点

private:
	vector<Point2D> m_P;	// 输入数据
	vector<Point2D> m_pCH;  // 包络
	int m_nPoints;          // 输入数据的点数
	double *m_ang;			// 每个点的方位角
	double *m_dis;			// 每个点与重心的距离

	double m_angThreshold;  // 角度阈值
	double m_NumIteration;  // 迭代次数

	double m_X0;            // 点云重心x坐标
	double m_Y0;            // 点云重心y坐标
};