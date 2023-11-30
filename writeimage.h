#ifndef WRITEIMAGE_H
#define WRITEIMAGE_H


//void matrix_kiir(ImageParams const *imgdata, PixelData  **matrix);
int writefile(std::string filenamestr,std::unique_ptr<ImageParams> outputImg);//char const *filename, ImageParams const *imgdata, PixelData  **matrix);

#endif // WRITEIMAGE_H
