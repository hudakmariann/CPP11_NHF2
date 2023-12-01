#include <iostream>

#include "Brightness.h"

bool Brightness::ApplyFilter(int rate) {

bool result = false;

    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();

    std::cout  << "imgParams->HSVmatrix.size = " <<  imgParams->getHSVMatrix().size() << std::endl;

    bool HSVReady = Filter::RGBtoHSV();

    std::cout  << "imgParams->HSVmatrix.size = " <<  imgParams->getHSVMatrix().size() << std::endl;

     //std::cout  << "imgParams->HSVmatrix[0][0] = " <<  imgParams->getHSVMatrix()[0][0].hue << std::endl;;
    // std::cout  << "imgParams->HSVmatrix[500][500] = " <<  imgParams->getHSVMatrix()[500][500].hue << std::endl;;

    std::cout << "ApplyFilter imgParams Height = " << h << " Width = " << w << std::endl;

    std::vector<std::vector<HSVData>> HSVmatrix(h, std::vector<HSVData> (w));

    //std::cout  << "Please type in the factor of brightness change between -100 and +100.\n";
    //scanf("%f", &percent);
   // std::cin >> rate;
    if (rate < -100)
        rate = -100;
    else
    if (rate > 100)
        rate = 100;

    double percent =(double)rate/100;

    std::cout  << "Percent = " << percent << std::endl;;



     for (unsigned i = 0; i < h; i++){
        for (unsigned j = 0; j < w; j++){
        HSVmatrix[i][j].value = (double)HSVmatrix[i][j].value*(1+percent);
        }//end for j
    }//end for i
     std::cout  << "HSVmatrix[0][0] = " <<  HSVmatrix[0][0].hue << std::endl;;
     std::cout  << "HSVmatrix[500][500] = " <<  HSVmatrix[500][500].hue << std::endl;;
    imgParams->setHSVMatrix(std::move(HSVmatrix));
    result = true;
return result;

}