#include <iostream>

#include "FindEdges.h"

std::unique_ptr<ImageParams> FindEdges::ApplyFilter(int rate)
{

    bool HSVReady = false;
    bool RGBReady = false;

    if (imgParams->getHSVMatrix().size()==0)
        HSVReady = Filter::RGBtoHSV();

    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();

    std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
    std::vector<std::vector<HSVData>> filteredHSV(h, std::vector<HSVData> (w));

    double surround[8];
    double szele = 1;


    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {

            if ((y != 0) && (x != 0) && (y != h-1) && (x != w-1) )
            {
                surround[0] = HSVmatrix[y-1][x-1].value;
                surround[1] = HSVmatrix[y-1][x].value;
                surround[2] = HSVmatrix[y-1][x+1].value;
                surround[3] = HSVmatrix[y][x-1].value;
                surround[4] = HSVmatrix[y][x+1].value;
                surround[5] = HSVmatrix[y+1][x-1].value;
                surround[6] = HSVmatrix[y+1][x].value;
                surround[7] = HSVmatrix[y+1][x+1].value;
            }
            else
                for (int i = 0; i < 8; i++) //kep szelenek lekezelese a tulindexeles elkerulese vegett
                    surround[i] = szele;

            double sum = 0;
            for (int i = 0; i < 8; i++)
            {
                sum+=surround[i];
            }
            filteredHSV[y][x].hue = HSVmatrix[y][x].hue;
            filteredHSV[y][x].saturation = 0;
            filteredHSV[y][x].value = (-8)*HSVmatrix[y][x].value + sum;

        }//end for x
    }//end for y

    imgParams->setHSVMatrix(std::move(filteredHSV));

    RGBReady = Filter::HSVtoRGB();

    std::cout <<  "FindEdges ready." << std::endl;
    return (std::move(imgParams));

}
