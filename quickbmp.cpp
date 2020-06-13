#include "quickbmp.h"
#include <iostream>

void BMP::generateBitmapImage(const BMP::BMPColor8* image, const uint32_t height, const uint32_t width, const char* imageFileName) {
    unsigned char padding[3] = { 0, 0, 0 };
    const uint32_t paddingSize = (4 - (width * sizeof(uint8_t)) % 4) % 4;
    createBitmapFileHeader(height, width, paddingSize, sizeof(uint8_t), sizeof(palette) + 2 /*pad*/);
    createBitmapInfoHeader(height, width, sizeof(uint8_t), sizeof(palette));

    FILE* imageFile;
    if (fopen_s(&imageFile, imageFileName, "wb") > 0)
    {
        return;
    }

    uint8_t pad[2] = { 0,0 };

    fwrite(&fileHeader, 1, sizeof(FileHeader), imageFile);
    fwrite(&infoHeader, 1, sizeof(InfoHeader), imageFile);
    fwrite(&palette, 1, sizeof(palette), imageFile);
    fwrite(pad, 1, sizeof(pad), imageFile);

    for (size_t i = 0; i < height; i++) {
        fwrite((void*)(image + (i * (size_t)width)), sizeof(uint8_t), width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

void BMP::generateBitmapImage(const BMPColor16* image, const uint32_t height, const uint32_t width, const char* imageFileName) {

    unsigned char padding[3] = { 0, 0, 0 };
    const uint32_t paddingSize = (4 - (width * sizeof(BMPColor16)) % 4) % 4;

    createBitmapFileHeader(height, width, paddingSize, sizeof(BMPColor16));
    createBitmapInfoHeader(height, width, sizeof(BMPColor16));

    FILE* imageFile;
    if (fopen_s(&imageFile, imageFileName, "wb") > 0)
    {
        return;
    }

    fwrite(&fileHeader, 1, sizeof(fileHeader), imageFile);
    fwrite(&infoHeader, 1, sizeof(infoHeader), imageFile);

    for (size_t i = 0; i < height; i++) {
        fwrite((void*)(image + (i * (size_t)width)), sizeof(BMPColor16), width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}


void BMP::generateBitmapImage(const BMPColor24* image, const uint32_t height, const uint32_t width, const char* imageFileName) {

    unsigned char padding[3] = { 0, 0, 0 };
    const uint32_t paddingSize = (4 - (width * sizeof(BMPColor24)) % 4) % 4;

    createBitmapFileHeader(height, width, paddingSize, sizeof(BMPColor24));
    createBitmapInfoHeader(height, width, sizeof(BMPColor24));

    FILE* imageFile;
    if (fopen_s(&imageFile, imageFileName, "wb") > 0)
    {
        return;
    }

    fwrite(&fileHeader, 1, sizeof(fileHeader), imageFile);
    //BMP::debugOutput((uint8_t*)&fileHeader, sizeof(fileHeader));
    fwrite(&infoHeader, 1, sizeof(infoHeader), imageFile);
    //BMP::debugOutput((uint8_t*)&infoHeader, sizeof(infoHeader));

    for (size_t i = 0; i < height; i++) {
        fwrite((void *)(image + (i * (size_t)width)), sizeof(BMPColor24), width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

void BMP::generateBitmapImage(const BMPColor32* image, const uint32_t height, const uint32_t width, const char* imageFileName) {
    createBitmapFileHeader(height, width, 0, sizeof(BMPColor32));
    createBitmapInfoHeader(height, width, sizeof(BMPColor32));

    FILE* imageFile;
    if (fopen_s(&imageFile, imageFileName, "wb") > 0)
    {
        return;
    }

    fwrite(&fileHeader, 1, sizeof(fileHeader), imageFile);
    fwrite(&infoHeader, 1, sizeof(infoHeader), imageFile);

    for (size_t i = 0; i < height; i++) {
        fwrite((void*)(image + (i * (size_t)width)), sizeof(BMPColor32), width, imageFile);
    }

    fclose(imageFile);
}

void BMP::createBitmapFileHeader(const uint32_t height, const uint32_t width, const uint32_t paddingSize, const uint32_t bytesPerPixel, const uint32_t paletteSize) {
    uint32_t fileSize = sizeof(FileHeader) + sizeof(InfoHeader) + ((size_t)bytesPerPixel * (size_t)width + (size_t)paddingSize) * height + (paletteSize * sizeof(BMPColor32));

    fileHeader.signature[0] = (unsigned char)('B');
    fileHeader.signature[1] = (unsigned char)('M');
    fileHeader.imageFileSize = fileSize;
    fileHeader.reserved = 0;
    fileHeader.pixelStart = (static_cast<uint32_t>(sizeof(FileHeader)) + static_cast<uint32_t>(sizeof(InfoHeader)) + paletteSize);
}


void BMP::createBitmapInfoHeader(const uint32_t height, const uint32_t width, const uint32_t bytesPerPixel, const uint32_t colorsInTable) {
    infoHeader.headerSize = (sizeof(InfoHeader));
    infoHeader.imageWidth = width;
    infoHeader.imageHeight = height;
    infoHeader.colorPlanes = 1;
    infoHeader.bitsPerPixel = bytesPerPixel * 8;
    infoHeader.horizontalResolution = 10000;
    infoHeader.verticalResolution = 10000;
    infoHeader.colorsInTable = colorsInTable;
}

void BMP::setPaletteColor(const size_t index, const BMPColor32 color) {
    if (index > 255) return;
    palette[index].r = color.r;
    palette[index].g = color.g;
    palette[index].b = color.b;
    palette[index].a = color.a;
}


void BMP::debugOutput(const uint8_t* data, const size_t length) {
    for (size_t i = 0; i < length; i++) {
        std::cout << std::hex << (unsigned int)data[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::flush;
}