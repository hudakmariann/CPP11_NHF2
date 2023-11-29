#ifndef PIXELDATA_H_INCLUDED
#define PIXELDATA_H_INCLUDED

class PixelData
{

public:
    short  red = 0;
    short  green = 0;
    short  blue = 0;

    PixelData(short &&r=0, short &&g = 0, short &&b = 0) : red{r}, green{g}, blue{b} {} //itt move semantics, mert odaát a hívónál már nem kell az adat, így jöhet rvalue-ként, és akkor nem másolgat feleslegesen (?)

    // copy constructor
    PixelData(const PixelData& rhs)
    {
        this->red = rhs.red;
        this->green = rhs.green;
        this->blue = rhs.blue;
    }

    // copy assignment
    PixelData& operator=(const PixelData& rhs)
    {
        if (this !=&rhs)
        {
            this->red = rhs.red;
            this->green = rhs.green;
            this->blue = rhs.blue;
        }
    }

        //move constructor - ha jól értem, hiába nincs most itt heap (mert egy short olyan rövid, hogy egy pointer sem rövidebb),
        //ha move-ot használok az adatstuktúra átpasszolásához, akkor nem történik felesleges másolás,
        //ha a hívónál már nem kell az átadott adat (?)
        PixelData(const PixelData&& rhs)
        {
            this->red = rhs.red;
            this->green = rhs.green;
            this->blue = rhs.blue;
        }

        PixelData& operator=(const PixelData&& rhs)
        {
            if (this !=&rhs)
            {
                this->red = rhs.red;
                this->green = rhs.green;
                this->blue = rhs.blue;
            }

        }

        //destruktor (memoriat nem kell felszabaditani, mert shortok miatt nem erdemes pointerezni,
        //de a rule of 5 miatt definiálni, c++11 módra default-tal
        ~PixelData() = default;








    };




#endif // PIXELDATA_H_INCLUDED
