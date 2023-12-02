#ifndef SATURATION_H_INCLUDED
#define SATURATION_H_INCLUDED

#include "Filter.h"
#include <memory>


class Saturation final: public Filter {

public:

Saturation(std::unique_ptr<ImageParams> imgprms) : Filter {std::move(imgprms)} {}
virtual std::unique_ptr<ImageParams> ApplyFilter(int rate) override;



};


#endif // SATURATION_H_INCLUDED
