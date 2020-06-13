#include <iostream>
#include "quickbmp.h"

using namespace std;

int main()
{
    BMP generate;
    const uint32_t height = 341;
    const uint32_t width = 753;
    char* imageFileName8 = "bitmapImage8.bmp";
    char* imageFileName16 = "bitmapImage16.bmp";
    char* imageFileName24 = "bitmapImage24.bmp";
    char* imageFileName32 = "bitmapImage32.bmp";
    BMP::BMPColor8* image8 = new BMP::BMPColor8[height * width];
    BMP::BMPColor16* image16 = new BMP::BMPColor16[height * width];
    BMP::BMPColor24* image24 = new BMP::BMPColor24[height * width];
    BMP::BMPColor32* image32 = new BMP::BMPColor32[height * width];

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // 24 bit reference
            {
                if (i == 0) { // first line blue (bottom of image because BMP start at the bottom and scan up)
                    image24[i * width + j].r = 0;
                    image24[i * width + j].g = 0;
                    image24[i * width + j].b = 255;
                }
                else {
                    image24[i * width + j].r = (unsigned char)((double)i / (double)height * 255); ///red
                    image24[i * width + j].g = (unsigned char)((double)j / (double)width * 255); ///green
                    image24[i * width + j].b = (unsigned char)(((double)i + j) / (double)(height + width) * 255); ///blue
                }
            }
            // 32 bit
            {
                image32[i * width + j].r = (unsigned char)((double)i / (double)height * 255); ///red
                image32[i * width + j].g = (unsigned char)((double)j / (double)width * 255); ///green
                image32[i * width + j].b = (unsigned char)(((double)i + j) / (double)(height + width) * 255); ///blue
                image32[i * width + j].a = 0; // alpha
            }
            // 16 bit
            {
                image16[i * width + j].r = (unsigned char)((double)i / (double)height * 31); ///red
                image16[i * width + j].g = (unsigned char)((double)j / (double)width * 31); ///green
                image16[i * width + j].b = (unsigned char)(((double)i + j) / (double)(height + width) * 31); ///blue
                image16[i * width + j].a = 0; // alpha
            }
            // 8 bit
            {
                if (i == j) {
                    image8[i * width + j].colorIndex = 4; // diagonal grey line through
                }
                else {
                    image8[i * width + j].colorIndex = (i * width + j) % 4; // pixel checker board
                }
            }
        }
    }

    // palette generation
    BMP::BMPColor32 color;
    color.a = color.b = color.g = color.r = 0;
    generate.setPaletteColor(0, color); // black
    color.r = 255;
    generate.setPaletteColor(1, color); // red
    color.r = 0;
    color.g = 255;
    generate.setPaletteColor(2, color); // green
    color.g = 0;
    color.b = 255;
    generate.setPaletteColor(3, color); // blue
    color.a = color.b = color.g = color.r = 128;
    generate.setPaletteColor(4, color); // grey

    generate.generateBitmapImage(image8, height, width, imageFileName8);
    generate.generateBitmapImage(image16, height, width, imageFileName16);
    generate.generateBitmapImage(image24, height, width, imageFileName24);
    generate.generateBitmapImage(image32, height, width, imageFileName32);

    printf("Images generated!!");
    
    delete[] image8;
    delete[] image16;
    delete[] image24;
    delete[] image32;

    return 0;
}
