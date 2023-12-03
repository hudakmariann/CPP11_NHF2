#include <iostream>
#include "Brightness.h"

std::unique_ptr<ImageParams> Brightness::ApplyFilter(int rate)
{

    bool result = false;
    bool HSVReady = false;
    bool RGBReady = false;

    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();

    if (imgParams->getHSVMatrix().size()==0)
        HSVReady = Filter::RGBtoHSV();

    std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
    if (rate < -100)
        rate = -100;
    else if (rate > 100)
        rate = 100;

    double percent =(double)rate/100;

    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
            HSVmatrix[i][j].value = (double)HSVmatrix[i][j].value*(1+percent);
        }//end for j
    }//end for i

    imgParams->setHSVMatrix(std::move(HSVmatrix));

    RGBReady = Filter::HSVtoRGB();
    result = HSVReady;
    std::cout <<  "Brightness ready." << std::endl;
    return (std::move(imgParams));

}
