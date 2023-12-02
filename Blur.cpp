#include <iostream>

#include "Blur.h"


std::unique_ptr<ImageParams> Blur::ApplyFilter(int filtersize)
{

bool HSVReady = false;
bool RGBReady = false;



   // if (imgParams->getHSVMatrix().size()==0)
    //    HSVReady = Filter::RGBtoHSV();

    unsigned h = imgParams->getHeight();
    unsigned w = imgParams->getWidth();


    if (filtersize < 3){
        filtersize = 3;
        std::cout << "Warning: the requested factor is out of range. The factor is set to 3.\n ";
    }
    else if (filtersize > 30){
        filtersize = 31;
         std::cout << "Warning: the requested factor is out of range. The factor is set to 30.\n ";
    }
    if (filtersize%2 == 0)
        filtersize++; //paratlannak kell lennie

    double szele = 127;
    int kozepe = (filtersize-1)/2 ;
    double centerweight = (filtersize+1)/2;

    std::vector<std::vector<PixelData>> filteredIMG(h, std::vector<PixelData> (w));
    std::vector<std::vector<PixelData>> Window(filtersize, std::vector<PixelData> (filtersize));
    std::vector<std::vector<double>> filter(filtersize, std::vector<double> (filtersize));
    std::vector<std::vector<PixelData>> matrix = imgParams->getRGBMatrix();


    double filtersum = 0;
    std::cout <<"\nThe blur filter is:\n";
    for (int i = 0; i < filtersize; i++){
        for (int j = 0; j < filtersize; j++){
                filter[i][j] = centerweight - ((abs(kozepe-i))+ abs(kozepe-j));
            if (filter[i][j]< 1)
                filter[i][j] = 1;
            printf("%2.f ", filter[i][j]);
            filtersum += filter[i][j];
        }
    printf("\n");
    }


    std::cout << "\nProcessing 0%% ";
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){

       std::vector<std::vector<PixelData>> window(filtersize, std::vector<PixelData> (filtersize));

            double windowsum_r = 0;
            double windowsum_g = 0;
            double windowsum_b = 0;
            for (int i = 0; i< filtersize; ++i){
                for (int j = 0; j< filtersize; ++j){
                    if ((y+i > h-1) || (x+j > w-1)){
                        window[i][j].red = szele;
                        window[i][j].green = szele;
                        window[i][j].blue = szele;
                    }
                    else{
                        window[i][j].red = matrix[y+i][x+j].red;
                        window[i][j].green = matrix[y+i][x+j].green;
                        window[i][j].blue = matrix[y+i][x+j].blue;
                    }
                windowsum_r += window[i][j].red*filter[i][j];
                windowsum_g += window[i][j].green*filter[i][j];
                windowsum_b += window[i][j].blue*filter[i][j];
                }// end for j
            }//end for i

        filteredIMG[y][x].red =  windowsum_r/filtersum;
        filteredIMG[y][x].green =  windowsum_g/filtersum;
        filteredIMG[y][x].blue = windowsum_b/filtersum;


        }//end for x
        if (y%20 == 0)
            std::cout <<"|";
    }//end for y
    std::cout << " 100%%\nReady.\n";


    imgParams->setRGBMatrix(std::move(filteredIMG));

    std::cout <<  "Blur ready." << std::endl;
    return (std::move(imgParams));







    }
