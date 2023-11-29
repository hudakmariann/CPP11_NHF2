#ifndef BRIGHTNESS_H_INCLUDED
#define BRIGHTNESS_H_INCLUDED
#include "Filter.h"
#include <memory>


class Brightness : public Filter {

public:

Brightness(std::unique_ptr<ImageParams> imgprms) : Filter {std::move(imgprms)} {}



};


#endif // BRIGHTNESS_H_INCLUDED
