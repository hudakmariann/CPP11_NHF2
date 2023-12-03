#include "menu.h"
#include "readimage.h"
#include "ImageParams.h"
#include "PixelData.h"
#include "HSVData.h"
#include "Filter.h"
#include "Brightness.h"
#include "Saturation.h"
#include "Contrast.h"
#include "FindEdges.h"
#include "Blur.h"

#include "writeimage.h"
#include "control.h"

std::string filenev_beker(){


    std::string filename = "*.ppm";
    std::string extension = ".ppm";
    size_t ppm;

    do{

    std::cout <<"Please type in the filename of the image!\n";
    std::cin >> filename;
    std::cout << filename << std::endl;
    ppm = filename.find(extension);
    if (ppm == std::string::npos)
        std::cout <<"The file extension is not *.ppm!\n";
    }while (ppm == std::string::npos);
    return filename;
}


bool saveimage(std::unique_ptr<ImageParams> outputImg, std::string filename, enum SubMenu suboption){//}ImageParams *imgdata, PixelData **matrix, char *filename){

    char yesno;
    switch(suboption){

        case 1: {
            std::string filename = filenev_beker();
            writefile(filename, std::move(outputImg));
            break;;
        }
        case 2: {
            std::cout<<"WARNING: are you sure you want to overwrite "<< filename << "? (y/n) " << std::endl;
            scanf(" %c", &yesno); //szokoz kell, kulonben atugorja. Az elozo entert karakternek veszi!
            if ((yesno == 'y') || (yesno == 'Y'))
               writefile(filename, std::move(outputImg));
            else{
                std::string filename = filenev_beker();
                filename = filenev_beker();
                writefile(filename, std::move(outputImg));
            }
            break;
        }
    }
return true;
}


std::unique_ptr<ImageParams> processimage(std::unique_ptr<ImageParams> imgParams){
    enum MainMenu option;

    unsigned height = imgParams->getHeight();
    unsigned width = imgParams->getWidth();
    std::unique_ptr<ImageParams> outputParams;
    std::vector<std::vector<HSVData>> HSVmatrix;

    displaymain();
    option = selectmain();
    std::cout << "The selected option is: " << option << std::endl;

    switch(option){
        case 0:{
            exit(0);
        }
        case 1: {

            int rate;
            std::cout << "Contrast was chosen.\n";
            Contrast contrast(std::move(imgParams));
            std::cout << "Please provide the rate of contrast modification between -100 and 100\n";
            std::cin >> rate;
            outputParams = std::move(contrast.ApplyFilter(rate));

            break;
        }
        case 2: {

            int rate;
            std::cout << "Brightness was chosen.\n";
            Brightness brightness(std::move(imgParams));
            std::cout << "Please provide the rate of brightness modification between -100 and 100\n";
            std::cin >> rate;
            outputParams = std::move(brightness.ApplyFilter(rate));

            break;
        }
        case 3: {

            std::cout << "Saturation was chosen.\n";
            int rate;
            Saturation saturation(std::move(imgParams));
            std::cout << "Please provide the rate of saturation modification between -100 and 100\n";
            std::cin >> rate;
            outputParams = std::move(saturation.ApplyFilter(rate));
            break;
        }
        case 4: {

            std::cout << "Blur was chosen.\n";
            int filtersize;
            Blur blur(std::move(imgParams));
            std::cout << "Please provide the size of blur filter between 0 and 30 pixels\n";
            std::cin >> filtersize;
            outputParams = std::move(blur.ApplyFilter(filtersize));
            break;
        }
        case 5: {
            int rate = 100;
            std::cout << "FindEdges was chosen.\n";
            FindEdges findedges(std::move(imgParams));
            outputParams = std::move(findedges.ApplyFilter(rate));

            break;
        }

    }//end switch

    return (std::move (outputParams));
}



