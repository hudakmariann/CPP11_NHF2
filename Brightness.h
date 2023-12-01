#ifndef BRIGHTNESS_H_INCLUDED
#define BRIGHTNESS_H_INCLUDED
#include "Filter.h"
#include <memory>


class Brightness final: public Filter {

public:

Brightness(std::unique_ptr<ImageParams> imgprms) : Filter {std::move(imgprms)} {}
virtual std::unique_ptr<ImageParams> ApplyFilter(int rate) override;



};


#endif // BRIGHTNESS_H_INCLUDED
