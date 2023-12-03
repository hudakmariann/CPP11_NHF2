#include <stdio.h>
#include <stdlib.h>

#include "readimage.h"
#include "writeimage.h"



//ezt meghagytam a regi formajaban, csak a lecserelt valtozokat tettem bele
int writefile(std::string filenamestr,std::unique_ptr<ImageParams> imgParams){
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
                        v = (unsigned char)RGBMatrix[i][j].red ;
                        fwrite(&v,  sizeof(unsigned char), 1, outputfile) ;
                        break;
                     }
                     case 1: {
                         v = (unsigned char)RGBMatrix[i][j].green ;
                        fwrite(&v,  sizeof(unsigned char), 1, outputfile) ;
                        break;
                     }
                     case 2: {
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
