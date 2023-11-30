#ifndef READIMAGE_H
#define READIMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string>
#include <memory>

#include "ImageParams.h"

/*typedef struct PixelData{
    short r, g, b;
}PixelData;

typedef struct ImageParams{
    int w; //width
    int h; //height
    int d; //depth
}ImageParams;*/


//void readfilename(std::string filename);
std::unique_ptr<ImageParams>  readfile(std::string filename, short* errorcode);



#endif
