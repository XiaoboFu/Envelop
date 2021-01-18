#include "concaveHull2d.h"

/*!
 * \fn	ConCaveHull::ConCaveHull()
 *
 * \brief	Default constructor.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 */

ConCaveHull::ConCaveHull()
{
	m_nPoints = 0;
	m_NumIteration = 100;
	m_ang = NULL;
	m_dis = NULL;
}

/*!
 * \fn	ConCaveHull::~ConCaveHull()
 *
 * \brief	Destructor.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 */

ConCaveHull::~ConCaveHull()
{
	if (m_ang)
	{
		delete[] m_ang;
		m_ang = nullptr;
	}
	if (m_dis)
	{
		delete[] m_dis;
		m_dis = nullptr;
	}

	if (m_P.size() > 1)
	{
		vector <Point2D>().swap(m_P);
	}
	if (m_pCH.size() > 1)
	{
		vector<Point2D>().swap(m_pCH);
	}
}

/*!
 * \fn	void ConCaveHull::computeConcaveHull()
 *
 * \brief	Calculates the concave hull.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 */

void ConCaveHull::computeConcaveHull()
{
	// 获得角度和距离
	getAngleDistance();
	// 角度排序，形成凹包，不封闭
	bubbleSort();
	// 判断凸凹点，删除角度小于angThreshold的凹点
	deleteConcavePoints();
}

/*!
 * \fn	void ConCaveHull::setData(vector<Point2D> pp)
 *
 * \brief	Sets a data.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 *
 * \param	pp	初始点云，将被去重.
 */

void ConCaveHull::setData(vector<Point2D> pp)
{
	// 删除重复点
	m_nPoints = (int)pp.size();
	bool flag = false;
	for (int i=0; i< m_nPoints; i++)
	{
		flag = false;
		for (int j=i+1; j< m_nPoints; j++ )
		{
			if (pp[i].x == pp[j].x && pp[i].y == pp[j].y)
			{
				flag = true; // 出现重复点时不进行赋值，将后面的点加入m_P中
				break;
			}
		}
		if (!flag)
		{
			m_P.push_back(pp[i]);
		}
	}

	m_nPoints =(int) m_P.size();

	if (!m_ang)
	{
		m_ang = new double[m_nPoints];
	}
	if (!m_dis)
	{
		m_dis = new double[m_nPoints];
	}
}

/*!
 * \fn	void ConCaveHull::setData(vector<Point2D> pp, double angThreshold, int nIter)
 *
 * \brief	Sets a data.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 *
 * \param	pp				点云.
 * \param	angThreshold	The angle threshold, =180时结果为凸包,需要凹包建议给120.
 * \param	nIter			The iterator.
 */

void ConCaveHull::setData(vector<Point2D> pp, double angThreshold, int nIter)
{
	setData(pp);
	setParameters(angThreshold, nIter);
}

/*!
 * \fn	void ConCaveHull::setParameters(double angThreshold, int nIter)
 *
 * \brief	Sets the parameters.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 *
 * \param	angThreshold	The angle threshold, =180时结果为凸包,需要凹包建议给120.
 * \param	nIter			The iterator迭代次数.
 */

void ConCaveHull::setParameters(double angThreshold, int nIter)
{
	m_angThreshold = angThreshold;
	m_NumIteration = nIter;
}

/*!
 * \fn	vector<Point2D> ConCaveHull::getConcaveHull()
 *
 * \brief	Gets concave hull.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 *
 * \return	The concave hull.
 */

vector<Point2D> ConCaveHull::getConcaveHull()
{
	return m_pCH;
}

/*!
 * \fn	void ConCaveHull::bubbleSort()
 *
 * \brief	Bubble sort.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 */

void ConCaveHull::bubbleSort()
{
	int len = m_nPoints;
	double temp;//中间变量 
	Point2D tmpP;
	for (int i = 0; i < len; i++)
	{
		for (int j = len - 1; j > i; j--)
		{
			if (m_ang[j] < m_ang[j - 1])
			{
				temp = m_ang[j - 1];
				m_ang[j - 1] = m_ang[j];
				m_ang[j] = temp;
				
				tmpP = m_P[j - 1];
				m_P[j - 1] = m_P[j];
				m_P[j] = tmpP;
			}
		}
	}

	// 计算凸包，不封闭
	m_pCH = m_P;
}

/*!
 * \fn	void ConCaveHull::getAngleDistance()
 *
 * \brief	Gets angle distance.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 */

void ConCaveHull::getAngleDistance()
{
	// 重心坐标
	double x0 = 0.;
	double y0 = 0.;

	for (int i = 0; i < m_nPoints; i++)
	{
		x0 += m_P[i].x;
		y0 += m_P[i].y;
	}

	x0 /= m_nPoints;
	y0 /= m_nPoints;

	m_X0 = x0;
	m_Y0 = y0;

	// compute angle and distance
	for (int i = 0; i < m_nPoints; i++)
	{
		m_ang[i] = atan2(m_P[i].y - y0, m_P[i].x - x0)*180. / M_PI;
		if (m_ang[i] < 0.f)
		{
			m_ang[i] = m_ang[i] + 360.f;
		}

		m_dis[i] = sqrt((m_P[i].x - x0)*(m_P[i].x - x0) + (m_P[i].y - y0)*(m_P[i].y - y0));
	}
}

/*!
 * \fn	void ConCaveHull::deleteConcavePoints()
 *
 * \brief	Deletes the concave points.
 *
 * \author	Xiaobo.Fu
 * \date	2021/1/18
 */

void ConCaveHull::deleteConcavePoints()
{
	bool flag = true;
	int iteration = 0;
	do
	{
		int nPoint = (int)m_pCH.size();
		vector<Point2D> tmpCH;
		for (int i = 0; i < nPoint; i++)
		{
			Point2D p0 = m_pCH[i];
			Point2D p1, p2;
			// 第一个点
			if (i == 0)
			{
				p2 = m_pCH[nPoint - 1];
			}
			else
			{
				p2 = m_pCH[i - 1];

			}
			// 最后一个点
			if (i == nPoint - 1)
			{
				p1 = m_pCH[0];
			}
			else
			{
				p1 = m_pCH[i + 1];
			}

			Point2D a(p1.x - p0.x, p1.y - p0.y);
			Point2D b(p2.x - p0.x, p2.y - p0.y);

			double c = a.x*b.x + a.y*b.y;
			double d = sqrt(a.x*a.x + a.y*a.y) * sqrt(b.x*b.x + b.y*b.y);
			double angTmp = acos(c / d)*180. / M_PI;
			double r = a.x*b.y - a.y*b.x;

			if (r <= 0 && angTmp < m_angThreshold)
			{
				continue;
				flag = false;
			}
			else
			{
				tmpCH.push_back(m_pCH[i]);
			}
		}

		m_pCH.clear();

		m_pCH = tmpCH;
		vector<Point2D>().swap(tmpCH);

		if (iteration++>= m_NumIteration)
		{
			flag = false;
		}
		cout << iteration << endl;

	} while (flag);


	/*
	do
	{
		int nPoint = (int)m_pCH.size();
		vector<Point2D> tmpCH;
		for (int i = 0; i < nPoint; i++)
		{
			Point2D p0 = m_pCH[i];
			Point2D p1;
			// 最后一个点
			if (i == 0)
			{
				p1 = m_pCH[nPoint-1];
			}
			else
			{
				p1 = m_pCH[i - 1];
			}

			Point2D a(p1.x - p0.x, p1.y - p0.y);

			double d1_ = sqrt(a.x*a.x + a.y*a.y);
			if (d1_ < 0.01)
			{
				double d1 = sqrt((p1.x - m_X0)*(p1.x - m_X0) + (p1.y - m_Y0)*(p1.y - m_Y0));
				double d0 = sqrt((p0.x - m_X0)*(p0.x - m_X0) + (p0.y - m_Y0)*(p0.y - m_Y0));
				if (d0 > d1)
				{
					if (tmpCH.size()>0)
					{
						tmpCH.pop_back();
					}
					tmpCH.push_back(m_pCH[i]);
				}
			}
			else
			{
				tmpCH.push_back(m_pCH[i]);
			}
			
		}

		m_pCH.clear();

		m_pCH = tmpCH;
		vector<Point2D>().swap(tmpCH);
	} while (false);*/

}