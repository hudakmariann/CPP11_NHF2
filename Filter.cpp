#include <vector>
#include <iostream>
#include "Filter.h"


double minRGB(double r, double g, double b){
    double rgb[3] = {r,g,b};
    double min = 255;
    for (int i = 0; i<3; ++i){
        if (rgb[i] < min)
            min = rgb[i];
    }
    return min;
}

double maxRGB(double r, double g, double b){
    double rgb[3] = {r,g,b};
    double max = 0;
    for (int i = 0; i<3; ++i){
        if (rgb[i] > max)
            max = rgb[i];
    }
    return max;
}

bool Filter::RGBtoHSV(){

bool result = false;

double min, max, diff;

    double r, g, b;


    unsigned const h = imgParams->getHeight();
    unsigned const w = imgParams->getWidth();

     std::cout  << "RGBtoHSV : RGBmatrix.size = " <<  imgParams->getRGBMatrix().size() << std::endl;;

    std::vector<std::vector<HSVData>> HSVmatrix(h, std::vector<HSVData> (w));


    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){

            r = (double)imgParams->getRGBMatrix()[i][j].red/256;
            g = (double)imgParams->getRGBMatrix()[i][j].green/256;
            b = (double)imgParams->getRGBMatrix()[i][j].blue/256;

            //std::cout  << "RGBtoHSV : r = " <<  r << std::endl;;

            max = maxRGB(r,g,b); //Max<double>(r,g,b);
            min = minRGB(r,g,b); //Min<double>(r,g,b);
            diff = max - min;

            //std::cout  << "RGBtoHSV : diff = " <<  diff << std::endl;;

            if (max == 0)
                HSVmatrix[i][j].saturation = 0;
            else
                HSVmatrix[i][j].saturation = diff / max;

            if (diff == 0){
                HSVmatrix[i][j].hue = 0;
                HSVmatrix[i][j].saturation = 0;
            }

            if (max == r)
                     HSVmatrix[i][j].hue = (g - b) /diff;
            else
            if (max == g)
                HSVmatrix[i][j].hue = 2 + (b - r) / diff;
            else
                HSVmatrix[i][j].hue = 4 + (r - g) / diff;

            if (HSVmatrix[i][j].hue < 0)
                HSVmatrix[i][j].hue=0;
            HSVmatrix[i][j].hue /= 6;
            HSVmatrix[i][j].value = max;
            //std::cout  << "HSVmatrix[i][j].value = " << HSVmatrix[i][j].value << std::endl;;

        }//end for j
        std::cout  << "HSVmatrix[i][j].value = " << i << std::endl;;
    }//end for i
   // return HSVmatrix;

   std::cout  << "RGBtoHSV ready. " << std::endl;;
   imgParams->setHSVMatrix(std::move(HSVmatrix));
result = true;
   return result;




}




bool Filter::HSVtoRGB(){
    bool result = false;
    double h, s, v;
    double r, g, b;

    unsigned const  height = imgParams->getHeight();
    unsigned const  width = imgParams->getWidth();



    std::vector<std::vector<PixelData>> RGBmatrix(height, std::vector<PixelData> (width));



    for (unsigned i = 0; i < height; i++){
        for (unsigned j = 0; j < width; j++){

    // RGB-HSV konverziohoz hasznalt forras: https://lodev.org/cgtutor/color.html

            h = imgParams->getHSVMatrix()[i][j].hue;
            s = imgParams->getHSVMatrix()[i][j].saturation;
            v = imgParams->getHSVMatrix()[i][j].value;

            if(s == 0)
                r = g = b = v;
            else
            {
                float f, p, q, t;
                int n;
                h *= 6;
                i = (int)h;//(floor(h));
                f = h - n;
                p = v * (1 - s);
                q = v * (1 - (s * f));
                t = v * (1 - (s * (1 - f)));
                switch(i)
                {
                    case 0:{
                        r = v;
                        g = t;
                        b = p;
                        break;
                    }
                    case 1: {
                        r = q;
                        g = v;
                        b = p;
                        break;
                    }
                    case 2: {
                        r = p;
                        g = v;
                        b = t;
                        break;
                    }
                    case 3: {
                        r = p;
                        g = q;
                        b = v;
                        break;
                    }
                    case 4: {
                        r = t;
                        g = p;
                        b = v;
                        break;
                    }
                    case 5: {
                        r = v;
                        g = p;
                        b = q;
                        break;
                    } //end case
                } //end switch
            } // end else

            if (r < 0) r = 0;
            if (r>1)  r = 1;
            if (g < 0) g = 0;
            if (g>1)  g = 1;
            if (b < 0) b = 0;
            if (b>1)  b = 1;


            RGBmatrix[i][j].red = (short)(r * 255);
            RGBmatrix[i][j].green = (short)(g * 255);
            RGBmatrix[i][j].blue = (short)(b * 255);


            }//end for j
        }//end for i
        imgParams->setRGBMatrix(std::move(RGBmatrix));
result = true;
return result;
}






