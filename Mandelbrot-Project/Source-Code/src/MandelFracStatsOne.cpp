#include <MandelFracStatsOne.h>

MandelFracStatsOne::MandelFracStatsOne(unsigned wip, 
                                        unsigned hip, 
                                        unsigned mit, 
                                        double xc, 
                                        double yc, 
                                        double mrr)
{
    this->widthInPixels = wip;
    this->heightInPixels = hip;
    this->maxIterations = mit;
    this->xCenterPoint = xc;
    this->yCenterPoint = yc;
    this->minRectRadius = mrr;
    this->minRealValue = xCenterPoint - minRectRadius;
    this->maxRealValue = xCenterPoint + minRectRadius;
    this->minImaginaryValue = yCenterPoint - minRectRadius;
    this->maxImaginaryValue = yCenterPoint + minRectRadius;
}