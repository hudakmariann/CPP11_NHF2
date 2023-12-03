#ifndef READIMAGE_H
#define READIMAGE_H

#include <string>
#include <memory>

#include "ImageParams.h"

std::unique_ptr<ImageParams>  readfile(std::string filename, short* errorcode);



#endif
