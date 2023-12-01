/*#include <iostream>
#include "ImageParams.h"

#include "Filter.h"
#include "Brightness.h"

int main()
{

    std::cout << "Hello bello!" << std::endl;
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string>
#include <iostream>

#include <vector>
#include <memory>

#include "menu.h"
#include "readimage.h"
#include "writeimage.h"
#include "control.h"
#include "ImageParams.h"




int main(){
    //PixelData **matrix;
    short readfileresult;
    //ImageParams imgdata;
    std::unique_ptr<ImageParams> imgParams = NULL;
    bool imgRead =false;
    std::unique_ptr<ImageParams> outputImg = NULL;
    std::string filename;
    bool onemore = false;
    char yesno;
    int processcompleted = 1;
    short errorcode;


    do{
        bool finished = false;
        filename = filenev_beker();

        imgParams = readfile(filename, &errorcode);
        if (imgParams != NULL)
            printf("Image loaded successfully\n");
        else{
            printf("ERROR loading image\n");
            printf("errorcode = %d\n", readfileresult);
            return 1;
        }

        while(!finished){
            outputImg = std::move(processimage(std::move(imgParams)));
            if (outputImg == NULL){
                    printf("ERROR: Image processing failed.\n");
                return 2;
            }
            finished = saveimage(std::move(outputImg), filename);
        }

        //free(matrix[0]);
        //free(matrix);

        printf("Would you like to process another image? (y/n)\n");
        scanf(" %c", &yesno); //szokoz kell, kulonben atugorja. Az elozo entert karakternek veszi!


        if ((yesno == 'y') || (yesno == 'Y'))
            onemore = true;
        else
            onemore = false;

    }while(onemore);

    printf("end.\n");
    return 0;
}
