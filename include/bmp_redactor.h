#pragma once
#include <stdint.h>

#pragma pack(push, 1)

typedef struct {
    uint8_t r;  
    uint8_t g;
    uint8_t b;
} pixel_t;

typedef struct __attribute__((packed)) {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} bmp_fileheader_t;

typedef struct __attribute__((packed)) {
    uint32_t biSize;          //      / Размер этого заголовка
    int32_t  biWidth;         //     |  Ширина
    int32_t  biHeight;        //core<  Высота
    uint16_t biPlanes;        //     |  1
    uint16_t biBitCount;      //      \ Бит на пиксель
    uint32_t biCompression;   // 0
    uint32_t biSizeImage;     // Размер данных пикселей
    int32_t  biXPelsPerMeter; // Горизонтальное разрешение (dpi)
    int32_t  biYPelsPerMeter; // Вертикальное разрешение (dpi)
    uint32_t biClrUsed;       // 0 (все цвета)
    uint32_t biClrImportant;  // 0
} bmp_infoheader_t;

typedef struct {
    bmp_fileheader_t fileheader;
    bmp_infoheader_t infoheader;
    pixel_t* pixels;  // Одномерный массив (размер: width * height)
} bmp_t;

#pragma pack(pop)

bmp_t* load_bmp(const char* filename);
bmp_t* crop(bmp_t* pic, int x, int y, int width, int height);
void rotate_90_clockwise(bmp_t* pic);
int bmp_save(const bmp_t* bmp, const char* filename);
void bmp_free(bmp_t* bmp);
