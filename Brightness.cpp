#include <iostream>

#include "Brightness.h"

bool Brightness::ApplyFilter(int rate)const {

bool result = false;

    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();

    std::vector<std::vector<HSVData>> HSVmatrix(h, std::vector<HSVData> (w));

    std::cout  << "Please type in the factor of brightness change between -100 and +100.\n";
    //scanf("%f", &percent);
    std::cin >> rate;
    if (rate < -100)
        rate = -100;
    else
    if (rate > 100)
        rate = 100;

    double percent =rate/100;



     for (unsigned i = 0; i < h; i++){
        for (unsigned j = 0; j < w; j++){
        HSVmatrix[i][j].value = HSVmatrix[i][j].value*(1+percent);
        }//end for j
    }//end for i
    imgParams->setHSVMatrix(std::move(HSVmatrix));
    result = true;
return result;

}
