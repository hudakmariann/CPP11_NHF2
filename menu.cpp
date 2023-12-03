#include "menu.h"
#include "readimage.h"
#include "writeimage.h"
#include <iostream>

void displaymain(){
    std::cout<<"Please choose an option!\n";
    std::cout<<"0 EXIT\n";
    std::cout<<"1 Modify contrast\n";
    std::cout<<"2 Modify brightness\n";
    std::cout<<"3 Modify saturation\n";
    std::cout<<"4 Blur image\n";
    std::cout<<"5 Find edges\n";
}

enum MainMenu selectmain(){
    int selected;
    std::cin>> selected;
     while (selected < 0 || selected > 5){
        std::cout<<"Error: you selected "<< selected <<" - no such option.\nPlease select 0..5 from the menu below\n";
        displaymain();
        std::cin>> selected;
     }
     auto choice = static_cast<MainMenu>(selected);
     return choice;
}

void displaysubmenu(){
    std::cout<<"Please choose an option!\n";
    std::cout<<"0 further modification \n";
    std::cout<<"1 save as..\n";
    std::cout<<"2 save (overwrite original image)\n";

}


enum SubMenu selectsubmenu(){
    int selected;
    std::cin>> selected;
     while (selected < 0 || selected > 2){
        std::cout<<"Error: you selected " << selected <<" - no such option.\nPlease select 0..2 from the menu below\n";
        displaysubmenu();
        std::cin>> selected;
     }
     auto choice = static_cast<SubMenu>(selected);
     return choice;
}



