#ifndef M_IMAGE
#define M_IMAGE

#include<sstream>

struct M_Image
{
public:
M_Image(int iw = 500, int ih = 500, int mN = 255,double minr = -2.1,double maxr = 1.1,double mini = -1.6,double maxi = 1.6)
{
	imageWidthpx = iw;
	imageHeightpx = ih;
	maxN = mN;
	minR = minr;
	maxR = maxr;
	minI = mini;
	maxI = maxi;

}
int imageWidthpx;
int imageHeightpx;
int maxN;
double minR,maxR,minI,maxI;
std::ostringstream writeToFile;

};

#endif
