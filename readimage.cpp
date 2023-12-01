
#include <iostream>
#include "readimage.h"
//#include "debugmalloc.h"

/*void readfilename(std::string filename){
    printf("Please type in the filename of the image to modify. it should be a *.ppm file.");
    scanf("%s", filename);
}
*/

std::unique_ptr<ImageParams>  readfile(std::string filenamestr, short* errorcode){ //}, ImageParams *imgdata){

    std::unique_ptr<ImageParams> imgParams = std::unique_ptr<ImageParams>{new ImageParams(0, 0, 0)};

    FILE *inputfile;
    char c;
    char filetype[3];
    char size[10];
    char depth[5];
    //PixelData **matrix;
    unsigned char p;
    short v;

    const char * filename = filenamestr.c_str();

    inputfile = fopen(filename, "rb");
    printf("The selected file is %s\n", filename);
    if (inputfile == NULL){
        printf("Error opening file\n");
        *errorcode = 1;
        return NULL;
    }
    else
        printf("File opened successfully\n");

   for (int i = 0; i<3; ++i){
       fread(&filetype[i], sizeof(char), 1, inputfile);
   }
   if (filetype[0] != 'P' || filetype[1] !='6'){
        printf("Error: not a valid *.ppm file (identifier = %c%c)\n", filetype[0], filetype[1]);
        *errorcode = 2;
        return NULL;
    }
    else
        printf("Successful identification as valid *.ppm file (identifier = %c%c)\n", filetype[0], filetype[1]);

    //comment kiszurese
    fread(&c, sizeof(char), 1, inputfile);
    //printf("c = %c",c);
    if (c == '#'){
    printf("Reading comment\n");
        while (c != '\n')
            fread(&c, sizeof(char), 1, inputfile);
    }

// kep meretenek beolvasasa
if (isdigit(c))
     size[0] = c; //ha nem volt komment, a kep  merete mar itt kezodik, ezert be kell irni a size tombbe. Ha volt, akkor a \n kerul a size tomb elejere, de azt a sscanf ugysem fogja szamkent beolvasni, ugyhogy nem baj.
     else size[0] = ' ';
     fread(&c, sizeof(char), 1, inputfile);
      printf("Reading Image size\n");
     if (isdigit(c)){
        size[1] = c;
        int i = 2;
        while (c != '\n'){
        //while (!isspace(c)){
            fread(&c, sizeof(char), 1, inputfile);
            size[i] = c;
            i++;
        }
         //printf("Size = %s", size);
         std::cout << "Size = " << size << "pixels" << std::endl;
    unsigned width, height;
    sscanf(size, "%u %u", &width, &height);
     printf("Setting width, height\n");
     std::cout << "width = " << width << " height =  " << height<< std::endl;
    imgParams->setWidth(width);
    imgParams->setHeight(height);
     printf("Setting width, height ready\n");


    printf("width = %d, height = %d\n", imgParams->getWidth(), imgParams->getHeight());
    std::cout << "width = " << imgParams->getWidth() << " height =  " << imgParams->getHeight() << std::endl;
    }
    else{
        printf("Error: file contains invalid resolution data\n");
        *errorcode = 3;
        return NULL;
    }

    //bitmelyseg beolvasasa
     fread(&c, sizeof(char), 1, inputfile);
     if (isdigit(c)){
        depth[0] = c;
        int j = 1;
        while (c != '\n'){
            fread(&c, sizeof(char), 1, inputfile);
            depth[j] = c;
            j++;
        }
         std::cout << "Depth char = " << depth << " in chars" << std::endl;
        unsigned d;
        sscanf(depth, "%u", &d);
         std::cout << "Depth unsigned = " << d << " pixels" << std::endl;

        imgParams->setDepth(d);
        printf("bitdepth = %d\n", imgParams->getDepth());
    }
    else{
        printf("Error: file contains invalid color data\n");
        *errorcode = 4;
        return NULL;
    }

    //pixel adatok beolvasasa a heap-re

/* foglalás */
    //debugmalloc_max_block_size(imgdata->w * imgdata->h * sizeof(PixelData));

    /*matrix = (PixelData**) malloc(imgdata->h * sizeof(PixelData*));
    matrix[0] = (PixelData*) malloc(imgdata->w * imgdata->h * sizeof(PixelData));
    for (int y = 1; y < imgdata->h; ++y)
        matrix[y] = matrix[0] + y * imgdata->w;
*/

    unsigned height = imgParams->getHeight();
    unsigned width = imgParams->getWidth();
    //std::vector< std::vector < PixelData>> matrix;
    //std::vector< std::vector < PixelData>> matrix;
    std::vector<std::vector<PixelData>> matrix(height, std::vector<PixelData> (width));
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            for (int k = 0; k<3; k++){
                 fread(&p,  sizeof(unsigned char), 1, inputfile) ;
                 v = (short) p;
                 switch (k%3) {
                     case 0: {
                        matrix[i][j].red = v;
                        break;
                     }
                     case 1: {
                        matrix[i][j].green = v;
                        break;
                     }
                     case 2: {
                        matrix[i][j].blue = v;
                        break;
                     }
                }//end case
            }// end for k
        }//end for j
    }//end for i

fclose(inputfile);
errorcode = 0;
imgParams->setRGBMatrix(std::move(matrix));

return (std::move(imgParams));
}
