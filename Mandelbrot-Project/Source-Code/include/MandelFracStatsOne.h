#ifndef MANDEL_FRAC_STATS_ONE_H
#define MANDEL_FRAC_STATS_ONE_H

class MandelFracStatsOne
{
private:

public:
    MandelFracStatsOne(unsigned, unsigned, unsigned, double, double, double);
    unsigned widthInPixels;
    unsigned heightInPixels;
    unsigned maxIterations;
    double xCenterPoint;
    double yCenterPoint;
    double minRectRadius;
    double minRealValue;
    double maxRealValue;
    double minImaginaryValue;
    double maxImaginaryValue;
};

#endif