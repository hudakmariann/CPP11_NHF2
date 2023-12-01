#include <stdio.h>
#include <stdlib.h>

#include "readimage.h"
#include "writeimage.h"
//#include "debugmalloc.h"



int writefile(std::string filenamestr,std::unique_ptr<ImageParams> imgParams){//}char const *filename, ImageParams const *imgdata, PixelData  **matrix){

    char const* VERSION = "IMAGE EDITOR v.1119";

    FILE *outputfile;
    unsigned char v;

    const char * filename = filenamestr.c_str();
    outputfile  = fopen(filename, "wb");



    if (outputfile == NULL){
        printf("Error opening outputfile");
        return 1;
    }

    //fejlec kiirasa
    fprintf(outputfile, "P6\n");
    fprintf(outputfile, "# Processed by %s\n", VERSION);
    fprintf(outputfile, "%d %d\n", imgParams->getWidth(), imgParams->getHeight());
    fprintf(outputfile, "%d\n", imgParams->getDepth());

    unsigned height = imgParams->getHeight();
    unsigned width = imgParams->getWidth();
    std::vector<std::vector<PixelData>> RGBMatrix =   imgParams->getRGBMatrix();

for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            for (int k = 0; k<3; k++){
                 switch (k%3) {
                     case 0: {
                        //v = (unsigned char)imgParams->getRGBMatrix()[i][j].red ;
                        v = (unsigned char)RGBMatrix[i][j].red ;
                        fwrite(&v,  sizeof(unsigned char), 1, outputfile) ;
                        break;
                     }
                     case 1: {
                        //v = (unsigned char)imgParams->getRGBMatrix()[i][j].green ;
                         v = (unsigned char)RGBMatrix[i][j].green ;
                        fwrite(&v,  sizeof(unsigned char), 1, outputfile) ;
                        break;
                     }
                     case 2: {
                        //v = (unsigned char)imgParams->getRGBMatrix()[i][j].blue ;
                         v = (unsigned char)RGBMatrix[i][j].blue;
                        fwrite(&v,  sizeof(unsigned char), 1, outputfile) ;
                        break;
                     }
                }//end case
            }// end for k
        }//end for j
    }//end for i

    fclose(outputfile);
    printf("File saved\n");
    return 0;

}

//tesztelo rutin, kepernyore irja ki a fajlbol atkonvertalt adatokat
/*void matrix_kiir(ImageParams const *imgdata, PixelData  **matrix){
    for (int i = 0; i < imgdata->h; i++){
        for (int j = 0; j < imgdata->w; j++){
            for (int k = 0; k<3; k++){
                 switch (k%3) {
                     case 0: {
                        printf(" [%d][%d].r=%d ",i, j, matrix[i][j].r);
                        break;
                     }
                     case 1: {
                        printf(" [%d][%d].g=%d ", i, j, matrix[i][j].g);
                        break;
                     }
                     case 2: {
                        printf(" [%d][%d].b=%d ", i, j, matrix[i][j].b);
                        break;
                     }
                }//end case
            }// end for k
            printf("\n");
        }//end for j
    printf ("\n");
    }//end for i

    printf("\n");
    printf(" a %d. sor %d-edik pixelenek g erteke = %d \n", 117, 51, matrix[117][51].r);
}
*/
