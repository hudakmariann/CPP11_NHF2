#ifndef IMAGEPARAMS_H_INCLUDED
#define IMAGEPARAMS_H_INCLUDED

#include <vector>
#include "PixelData.h"
#include "HSVData.h"


class ImageParams{

private:
    unsigned const Height;
    unsigned const Width;
    unsigned const Depth;


    std::vector<std::vector <PixelData>> RGBMatrix;//(n, std::vector<PixelData> (m, 4));
    std::vector< std::vector < HSVData> > HSVMatrix;



friend class Filter;

public:
    ImageParams(unsigned const H, unsigned W, unsigned D) : Height{H}, Width{W}, Depth{D} {}

    unsigned getHeight() const {return Height;}
    unsigned getWidth() const {return Width;}
    unsigned getDepth() const {return Depth;}

    void setRGBMatrix(std::vector< std::vector < PixelData> >&& rgbmatrix){ this->RGBMatrix = rgbmatrix; }
    void setHSVMatrix(std::vector< std::vector < HSVData> >&& hsvmatrix){ this->HSVMatrix = hsvmatrix; }


};



#endif // IMAGEPARAMS_H_INCLUDED
