#ifndef CONTROL_H
#define CONTROL_H


#include <stdbool.h>

#include <string>
#include <iostream>
#include <memory>


std::string filenev_beker();
bool saveimage(std::unique_ptr<ImageParams> outputImg, std::string filename, enum SubMenu suboption);//ImageParams *imgdata, PixelData **matrix, char *filename);
std::unique_ptr<ImageParams>  processimage(std::unique_ptr<ImageParams> imgParams);//ImageParams *imgdata, PixelData **matrix, char* filename);


#endif
