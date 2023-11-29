#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "ImageParams.h"
#include <memory>

class Filter
{

private:
virtual bool ApplyFilter(int &rate)const = 0; //"Az NVI név arra utal, hogy egy jól megtervezett osztály interfészén (publikus részén) nem kellene virtuális függvények legyenek, hanem csak a privát részen. "

protected:
    std::unique_ptr<ImageParams> imgParams;

    bool RGBtoHSV();
    bool HSVtoRGB();

   template<typename T>
    T Min (T a, T b, T c)
    {
        T abc[3] = {a, b, c};
        T min = abc[0];
        for (int i = 1; i < 3; i++){
            if (abc[i] < abc[i-1])
                min = abc[i];
        }
        return min;
    }

   template<typename T>
    T Max (T a, T b, T c)
    {
        T abc[3] = {a, b, c};
        T max = abc[0];
        for (int i = 1; i < 3; i++){
            if (abc[i] > abc[i-1])
                max = abc[i];
        }
        return max;
    }




public:
//itt nem kell rule of 5, mert a unique_pointer elintéz mindent. (?)
  Filter(std::unique_ptr<ImageParams> imgprms) : imgParams{std::move(imgprms)} {}
  virtual ~Filter() = default;





};



#endif // FILTER_H_INCLUDED
