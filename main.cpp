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
    short readfileresult;
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
            std::cout<<"Image loaded successfully\n";
        else{
            std::cout<<"ERROR loading image\n";
            std::cout<<"errorcode = "<< readfileresult << std::endl;;
            return 1;
        }

        outputImg = std::move(processimage(std::move(imgParams)));

        if (outputImg == NULL){
                    printf("ERROR: Image processing failed.\n");
                return 2;
            }
        enum SubMenu suboption;
        displaysubmenu();
        suboption = selectsubmenu();
        printf("The selected option is: %d\n", suboption);
        while(suboption == 0){
            outputImg = std::move(processimage(std::move(outputImg)));
            displaysubmenu();
            suboption = selectsubmenu();

        }

        finished = saveimage(std::move(outputImg), filename, suboption);

        std::cout<<"Would you like to process another image? (y/n)\n";
        scanf(" %c", &yesno); //szokoz kell, kulonben atugorja. Az elozo entert karakternek veszi!


        if ((yesno == 'y') || (yesno == 'Y'))
            onemore = true;
        else
            onemore = false;

    }while(onemore);

    std::cout<<"end.\n";
    return 0;
}
