#include <iostream>

#include "Contrast.h"


double Contrast::maxval()
{
    double max = 0.0;
    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();
    std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
            if (HSVmatrix[i][j].value > max)
                max = HSVmatrix[i][j].value;
        }//end for j
    }//end for i

    return max;
}

double Contrast::minval()
{
    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();
    std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
    double min = 255.0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (HSVmatrix[i][j].value < min)
                min = HSVmatrix[i][j].value;
        }//end for j
    }//end for i
    return min;
}

std::unique_ptr<ImageParams> Contrast::ApplyFilter(int rate)
{

    bool HSVReady = false;
    bool RGBReady = false;


    if (imgParams->getHSVMatrix().size()==0)
        HSVReady = Filter::RGBtoHSV();

    std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();

    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();

    double min = minval();
    double max = maxval();

    if (rate < -100)
        rate = -100;
    else if (rate > 100)
        rate = 100;

    double percent =(double)rate/100;

    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
            HSVmatrix[i][j].value = ((HSVmatrix[i][j].value-min)*(((1+percent)*max)/(max-min))+min*(1-percent));

        }//end for j
    }//end for i

    imgParams->setHSVMatrix(std::move(HSVmatrix));
    RGBReady = Filter::HSVtoRGB();

    std::cout <<  "Contrast ready." << std::endl;
    return (std::move(imgParams));

}
