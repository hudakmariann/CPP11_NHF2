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

    printf("Please type in the filename of the image!\n");
    std::cin >> filename;
    //scanf(" %s", filename);
    //printf("FILENAME = %s\n", filename);
    std::cout << filename << std::endl;
    ppm = filename.find(extension);
    if (ppm == std::string::npos)
        printf("The file extension is not *.ppm!\n");
    }while (ppm == std::string::npos);
    return filename;
}


bool saveimage(std::unique_ptr<ImageParams> outputImg, std::string filename, enum SubMenu suboption){//}ImageParams *imgdata, PixelData **matrix, char *filename){

    char yesno;



    switch(suboption){
        /*case 0:{
            writefile("PROBA.ppm", std::move(outputImg)); //egy biztonsagi mentest a teszt kedveert ebben az esetben is csinalok
            return false;

        }*/
        case 1: {
            std::string filename = filenev_beker();
            writefile(filename, std::move(outputImg));
            break;;
        }
        case 2: {
            printf("WARNING: are you sure you want to overwrite %s? (y/n) \n", filename);
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


std::unique_ptr<ImageParams> processimage(std::unique_ptr<ImageParams> imgParams){//}ImageParams *imgdata, PixelData **matrix, char* filename){
    enum MainMenu option;

    unsigned height = imgParams->getHeight();
    unsigned width = imgParams->getWidth();
    std::unique_ptr<ImageParams> outputParams;
    std::vector<std::vector<HSVData>> HSVmatrix;

    displaymain();
    option = selectmain();
    printf("The selected option is: %d\n", option);

    switch(option){
        case 0:{

            exit(0);
        }
        case 1: {
            /*HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            setcontrast(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);*/
            int rate;
            std::cout << "Contrast was chosen.\n";
            Contrast contrast(std::move(imgParams));
            std::cout << "Please provide the rate of contrast modification between -100 and 100\n";
            std::cin >> rate;
            outputParams = std::move(contrast.ApplyFilter(rate));

            break;
        }
        case 2: {
            /*HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            setbrightness(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);
            */
            int rate;
            std::cout << "Brightness was chosen.\n";
            Brightness brightness(std::move(imgParams));
            std::cout << "Please provide the rate of brightness modification between -100 and 100\n";
            std::cin >> rate;
            outputParams = std::move(brightness.ApplyFilter(rate));

            break;
        }
        case 3: {
            /*HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            setsaturation(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);*/
             std::cout << "Saturation was chosen.\n";
             int rate;
            Saturation saturation(std::move(imgParams));
            std::cout << "Please provide the rate of saturation modification between -100 and 100\n";
            std::cin >> rate;
            outputParams = std::move(saturation.ApplyFilter(rate));
            break;
        }
        case 4: {
            //blurimage(imgdata, matrix);
             std::cout << "Blur was chosen.\n";
             int filtersize;
            Blur blur(std::move(imgParams));
            std::cout << "Please provide the size of blur filter between 0 and 30 pixels\n";
            std::cin >> filtersize;
            outputParams = std::move(blur.ApplyFilter(filtersize));
            break;
        }
        case 5: {
            /*HSVmatrix = RGBtoHSV(imgdata, matrix);
            if (HSVmatrix == NULL){
                printf ("Error: HSV conversion failed!\n");
                return 2;
            }
            findedges(imgdata, HSVmatrix);
            HSVtoRGB(imgdata, HSVmatrix, matrix);
            free(HSVmatrix[0]);
            free(HSVmatrix);*/

            int rate = 100;
            std::cout << "FindEdges was chosen.\n";
            FindEdges findedges(std::move(imgParams));
            outputParams = std::move(findedges.ApplyFilter(rate));

            break;
        }

    }//end switch

    return (std::move (outputParams));
}



