#ifndef CONTRAST_H_INCLUDED
#define CONTRAST_H_INCLUDED

#include "Filter.h"
#include <memory>


class Contrast final: public Filter {

private:
double maxval();
double minval();

public:

Contrast(std::unique_ptr<ImageParams> imgprms) : Filter {std::move(imgprms)} {}
virtual std::unique_ptr<ImageParams> ApplyFilter(int rate) override;
};


#endif // CONTRAST_H_INCLUDED
