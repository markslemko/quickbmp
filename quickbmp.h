#pragma once

#include <stdint.h>

class BMP {
public:

    #pragma pack(push, 1)

    struct FileHeader {
        char signature[2]; /// signature
        uint32_t imageFileSize, /// image file size in bytes
            reserved; /// reserved
        uint32_t pixelStart; /// start of pixel array
    };

    struct InfoHeader {
        uint32_t headerSize, /// header size
            imageWidth, /// image width
            imageHeight; /// image height
        uint16_t colorPlanes, /// number of color planes
            bitsPerPixel; /// bits per pixel
        uint32_t compression, /// compression
            imageSize, /// image size
            horizontalResolution, /// horizontal resolution
            verticalResolution, /// vertical resolution
            colorsInTable, /// colors in color table
            importantColorCount; /// important color count
        uint32_t redBM,         /// data that goes unused often
            greenBM,
            blueBM,
            alphaBM,
            CSType,
            CSEndpoints[9],
            gammaRed,
            gammaGreen,
            gammaBlue,
            intent,
            ICCdata,
            ICCsize,
            reserved;
    };

    struct BMPColor8 {
        uint8_t colorIndex;
    };

    struct BMPColor16 {
        uint16_t b : 5, g:5, r:5, a:1;
    };

    struct BMPColor24 {
        uint8_t b, g, r;
    };

    struct BMPColor32 {
        uint8_t b, g, r, a;
    };

    #pragma pack(pop)

    InfoHeader infoHeader = {};
    FileHeader fileHeader = {};

    void BMP::generateBitmapImage(const BMP::BMPColor8* image, const uint32_t height, const uint32_t width, const char* imageFileName);
    void generateBitmapImage(const BMPColor16* image, const uint32_t height, const uint32_t width, const char* imageFileName);
    void generateBitmapImage(const BMPColor24* image, const uint32_t height, const uint32_t width, const char* imageFileName);
    void generateBitmapImage(const BMPColor32* image, const uint32_t height, const uint32_t width, const char* imageFileName);
    void createBitmapFileHeader(const uint32_t height, const uint32_t width, const uint32_t paddingSize, const uint32_t bytesPerPixel, const uint32_t paletteSize = 0);
    void createBitmapInfoHeader(const uint32_t height, const uint32_t width, const uint32_t bytesPerPixel, const uint32_t colorsInTable = 0);
    void setPaletteColor(const size_t index, const BMPColor32 color);
    void debugOutput(const uint8_t* data, const size_t length);

    const int fileHeaderSize = 14;
    BMPColor32 palette[256];
};

