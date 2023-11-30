#ifndef IMAGEPARAMS_H_INCLUDED
#define IMAGEPARAMS_H_INCLUDED

#include <vector>
#include "PixelData.h"
#include "HSVData.h"


class ImageParams{

private:
    unsigned  Height;
    unsigned  Width;
    unsigned  Depth;


    std::vector<std::vector <PixelData>> RGBMatrix;
    std::vector< std::vector < HSVData> > HSVMatrix;


//protected:
//friend class Filter;

public:
    ImageParams(unsigned const H, unsigned W, unsigned D) : Height{H}, Width{W}, Depth{D} {}



    //getterek, hogy a Filter osztály hozzáférjen
    //azért nem friend lett a Filter osztály, mert akkor a leszármazottai nem tudnák lekérdezni az adatokat, csak az explicite friend ősosztály
    //minden leszármazottat meg nem lenne szerencsés Frienddé tenni, mert mi van, ha később vki csinál újabb szűrőket
    unsigned getHeight() const {return Height;}
    unsigned getWidth() const {return Width;}
    unsigned getDepth() const {return Depth;}
    std::vector<std::vector <PixelData>> getRGBMatrix(){return RGBMatrix;}
    std::vector< std::vector < HSVData> > getHSVMatrix(){return HSVMatrix;}

    void setHeight(unsigned h){ this->Height = h; }
    void setWidth(unsigned w){ this->Width = w; }
    void setDepth(unsigned d){ this->Depth = d; }
    void setRGBMatrix(std::vector< std::vector < PixelData> >&& rgbmatrix){ this->RGBMatrix = rgbmatrix; }
    void setHSVMatrix(std::vector< std::vector < HSVData> >&& hsvmatrix){ this->HSVMatrix = hsvmatrix; }


};



#endif // IMAGEPARAMS_H_INCLUDED
