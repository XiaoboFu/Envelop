#include <iostream>
#include <cmath>

#include "concaveHull2d.h"


int main(int argc, char *argv[])
{

	std::vector<Point2D> p;
	FILE *fpx = fopen("x.txt", "r");
	FILE *fpy = fopen("y.txt", "r");


	for (int i = 0; i < 100; i++)
	{
		Point2D tmp;

		fscanf(fpx, "%lf", &tmp.x);
		fscanf(fpy, "%lf", &tmp.y);

		p.push_back(tmp);
	}

	fclose(fpx);
	fclose(fpy);

	double minx = 0, maxx = 0;
	double miny = 0, maxy = 0;

	for (int i = 0; i < p.size(); i++)
	{
		minx = p[i].x < minx ? p[i].x : minx;
		maxx = p[i].x > maxx ? p[i].x : maxx;
		miny = p[i].y < miny ? p[i].y : miny;
		maxy = p[i].y > maxy ? p[i].y : maxy;
	}

	for (int i = 0; i < p.size(); i++)
	{
		p[i].x = (p[i].x - minx) / (maxx - minx);
		p[i].y = (p[i].y - miny) / (maxy - miny);
	}


	ConCaveHull *concavehull_ = new ConCaveHull();

	concavehull_->setData(p);
	concavehull_->setParameters(120,20);
	concavehull_->computeConcaveHull();
	vector<Point2D> pCH = concavehull_->getConcaveHull();

	pCH.push_back(pCH[0]); // °üÂçˇâąŐ
	fpx = fopen("pCH.txt", "w");

	for (int i = 0; i < pCH.size(); i++)
	{
		fprintf(fpx, "%f\t%f\n", pCH[i].x*(maxx - minx) + minx, pCH[i].y*(maxy - miny) + miny);
	}
	fclose(fpx);

	fpx = fopen("p.txt", "w");

	for (int i = 0; i < p.size(); i++)
	{
		fprintf(fpx, "%f\t%f\n", p[i].x*(maxx - minx) + minx, p[i].y*(maxy - miny) + miny);
	}
	fclose(fpx);

	vector<Point2D>().swap(pCH);
        delete concavehull_;

	return 0;
}
