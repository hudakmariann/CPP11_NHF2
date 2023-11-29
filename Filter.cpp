#include <vector>
#include "Filter.h"

bool Filter::RGBtoHSV(){

double min, max, diff;
   // HSVData** HSVmatrix;
    double r, g, b;

    /* foglalás */
    //debugmalloc_max_block_size(imgdata->w * imgdata->h * sizeof(HSV)); //ha ezt nem allitom be, a debugmalloc sir mar egy 512*512-es keptol is
    unsigned const h = imgParams->Height;
    unsigned const w = imgParams->Width;
    //HSVmatrix = new HSVData[h][w];//(HSV**) malloc(imgdata->h * sizeof(HSV*));
    //HSVmatrix[0] = (HSV*) malloc(imgdata->w * imgdata->h * sizeof(HSV));

    std::vector<std::vector<HSVData>> HSVmatrix(h, std::vector<HSVData> (w));



    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){

            r = (double)imgParams->RGBMatrix[i][j].red/256;
            g = (double)imgParams->RGBMatrix[i][j].green/256;
            b = (double)imgParams->RGBMatrix[i][j].blue/256;

            max = Max<double>(r,g,b);
            min = Min<double>(r,g,b);
            diff = max - min;

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
        }//end for j
    }//end for i
   // return HSVmatrix;
   imgParams->setHSVMatrix(std::move(HSVmatrix));

   return true;




}




bool Filter::HSVtoRGB(){
    //double max, min;
    double h, s, v;
    double r, g, b;

    for (unsigned i = 0; i < imgParams->getHeight(); i++){
        for (unsigned j = 0; j < imgParams->getWidth(); j++){

    // RGB-HSV konverziohoz hasznalt forras: https://lodev.org/cgtutor/color.html

            h = imgParams->HSVMatrix[i][j].hue;
            s = imgParams->HSVMatrix[i][j].saturation;
            v = imgParams->HSVMatrix[i][j].value;

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


            imgParams->RGBMatrix[i][j].red = (short)(r * 255);
            imgParams->RGBMatrix[i][j].green = (short)(g * 255);
            imgParams->RGBMatrix[i][j].blue = (short)(b * 255);


            }//end for j
        }//end for i
//printf("***********************************RGBtoHSV***************************\n");
return true;
}






