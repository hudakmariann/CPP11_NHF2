#ifndef BLUR_H_INCLUDED
#define BLUR_H_INCLUDED

#include "Filter.h"
#include <memory>


class Blur final: public Filter {


public:

Blur(std::unique_ptr<ImageParams> imgprms) : Filter {std::move(imgprms)} {}
virtual std::unique_ptr<ImageParams> ApplyFilter(int rate) override;
};
#endif // BLUR_H_INCLUDED
