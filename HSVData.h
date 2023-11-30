#ifndef HSVDATA_H_INCLUDED
#define HSVDATA_H_INCLUDED

class HSVData
{

public:
    double  hue;
    double  saturation;
    double  value;

    HSVData(double &&h=0, double &&s=0, double &&v=0) : hue{h}, saturation{s}, value{v} {}


    // copy constructor
    HSVData(const HSVData& rhs)
    {
        this->hue = rhs.hue;
        this->saturation = rhs.saturation;
        this->value = rhs.value;
    }

    // copy assignment
    HSVData& operator=(const HSVData& rhs)
    {
        if (this !=&rhs)
        {
            this->hue = rhs.hue;
            this->saturation = rhs.saturation;
            this->value = rhs.value;
        }
        return *this;
    }

    //destruktor (memoriat nem kell felszabaditani, mert shortok miatt nem erdemes pointerezni, de a rule of 3 miatt def.
    ~HSVData() = default;


};

#endif // HSVDATA_H_INCLUDED
