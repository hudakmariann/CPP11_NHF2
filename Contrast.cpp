#include <iostream>

#include "Contrast.h"


double Contrast::maxval(){
     double max = 0.0;
     unsigned h = imgParams->getHeight();
     unsigned w = imgParams->getWidth();
     std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
     for (unsigned i = 0; i < h; i++){
        for (unsigned j = 0; j < w; j++){
        if (HSVmatrix[i][j].value > max)
             max = HSVmatrix[i][j].value;
        }//end for j
    }//end for i
    std::cout  << "maxval ready" << std::endl;
    return max;
}

double Contrast::minval(){
     unsigned h = imgParams->getHeight();
     unsigned w = imgParams->getWidth();
     std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
     std::cout  << "HSVmatrix in MINVAL created" << std::endl;
    double min = 255.0;
     for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){

        if (HSVmatrix[i][j].value < min)
             min = HSVmatrix[i][j].value;
        }//end for j
    }//end for i
    std::cout  << "minval ready" << std::endl;
    return min;
}

std::unique_ptr<ImageParams> Contrast::ApplyFilter(int rate) {
std::cout  << "contrast created" << std::endl;

bool result = false;
bool HSVReady = false;
bool RGBReady = false;

std::cout  << "imgParams->HSVmatrix.size = " <<  imgParams->getHSVMatrix().size() << std::endl;

    if (imgParams->getHSVMatrix().size()==0)
        HSVReady = Filter::RGBtoHSV();

    std::cout  << "imgParams->HSVmatrix.size = " <<  imgParams->getHSVMatrix().size() << std::endl;

std::vector<std::vector<HSVData>> HSVmatrix = imgParams->getHSVMatrix();
std::cout  << "HSVmatrix in Contrast created" << std::endl;
    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();

    std::cout  << "imgParams->HSVmatrix.size = " <<  h<< std::endl;
    double min = minval();
    double max = maxval();




     //std::cout  << "imgParams->HSVmatrix[0][0] = " <<  imgParams->getHSVMatrix()[0][0].hue << std::endl;;
    // std::cout  << "imgParams->HSVmatrix[500][500] = " <<  imgParams->getHSVMatrix()[500][500].hue << std::endl;;

    std::cout << "ApplyFilter Contrast imgParams Height = " << h << " Width = " << w << std::endl;

    //std::vector<std::vector<HSVData>> HSVmatrix(h, std::vector<HSVData> (w));


    //std::cout  << "Please type in the factor of brightness change between -100 and +100.\n";
    //scanf("%f", &percent);
   // std::cin >> rate;
    if (rate < -100)
        rate = -100;
    else
    if (rate > 100)
        rate = 100;

    double percent =(double)rate/100;

    std::cout  << "Percent in Contrast = " << percent << std::endl;;



     for (unsigned i = 0; i < h; i++){
        for (unsigned j = 0; j < w; j++){
            HSVmatrix[i][j].value = ((HSVmatrix[i][j].value-min)*(((1+percent)*max)/(max-min))+min*(1-percent));

        }//end for j

    }//end for i

    imgParams->setHSVMatrix(std::move(HSVmatrix));

    RGBReady = Filter::HSVtoRGB();
    result = HSVReady;
    std::cout <<  "Contrast ready." << std::endl;
return (std::move(imgParams));

}
