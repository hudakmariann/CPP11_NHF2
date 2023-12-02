#ifndef FINDEDGES_H_INCLUDED
#define FINDEDGES_H_INCLUDED


#include "Filter.h"
#include <memory>


class FindEdges final: public Filter {


public:

FindEdges(std::unique_ptr<ImageParams> imgprms) : Filter {std::move(imgprms)} {}
virtual std::unique_ptr<ImageParams> ApplyFilter(int rate) override;
};

#endif // FINDEDGES_H_INCLUDED
