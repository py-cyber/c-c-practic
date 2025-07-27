#include "bmp_redactor.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bmp_t* load_bmp(const char* filename){
	FILE* fptr = fopen(filename, "rb");
	if (fptr == NULL){
		printf("Can't open file\n");
		return NULL;
	}

	bmp_t* res = (bmp_t*)malloc(sizeof(bmp_t));
	if (res == NULL){
        fclose(fptr);
        printf("Memory allocation failed\n");
        return NULL;
    }

	if (fread(&res->fileheader, sizeof(bmp_fileheader_t), 1, fptr) != 1){
        fclose(fptr);
        free(res);
        printf("Failed to read file header\n");
        return NULL;
    }
    if (res->fileheader.bfType != 0x4D42 && res->fileheader.bfType != 0x424D) {  // 'BM' in little-endian
        fclose(fptr);
        free(res);
        printf("Not a valid BMP file\n");
        return NULL;
    }

    if (fread(&res->infoheader, sizeof(bmp_infoheader_t), 1, fptr) != 1){
        fclose(fptr);
        free(res);
        printf("Failed to read info header\n");
        return NULL;
    }

    int width = res->infoheader.biWidth;
    int height = abs(res->infoheader.biHeight);
    int row_padded = (width * sizeof(pixel_t) + 3) & ~3;
    int padding = row_padded - width * sizeof(pixel_t);

    res->pixels = (pixel_t*)malloc(width * height * sizeof(pixel_t));
    if (res->pixels == NULL){
        fclose(fptr);
        free(res);
        printf("Failed to allocate pixel array\n");
        return NULL;
    }

	fseek(fptr, res->fileheader.bfOffBits, SEEK_SET);

	for (int i = 0; i < height; i++) {
        if (fread(&res->pixels[i * width], sizeof(pixel_t), width, fptr) != (size_t)width) {
            fclose(fptr);
            free(res->pixels);
            free(res);
            printf("Failed to read pixel data\n");
            return NULL;
        }
        fseek(fptr, padding, SEEK_CUR);
    }

	fclose(fptr);
	return res;
}

bmp_t* crop(bmp_t* pic, int x, int y, int width, int height){
	if (pic == NULL || pic->pixels == NULL){
        printf("Invalid image pointer\n");
        return NULL;
    }

	size_t img_height = abs(pic->infoheader.biHeight);
	size_t img_width = pic->infoheader.biWidth;

    if (x < 0 || y < 0 || width <= 0 || height <= 0 || 
        (size_t)(x + width) > img_width || (size_t)(y + height) > img_height) {
        printf("Invalid crop dimensions or position\n");
        return NULL;
    }

    bmp_t* cropped = (bmp_t*)malloc(sizeof(bmp_t));
    if (cropped == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }

    memcpy(&cropped->fileheader, &pic->fileheader, sizeof(bmp_fileheader_t));
    memcpy(&cropped->infoheader, &pic->infoheader, sizeof(bmp_infoheader_t));

    cropped->infoheader.biWidth = width;
    cropped->infoheader.biHeight = ((pic->infoheader.biHeight < 0) ? -height : height);
    cropped->infoheader.biSizeImage = width * height * sizeof(pixel_t);
    cropped->fileheader.bfSize = sizeof(bmp_fileheader_t) + sizeof(bmp_infoheader_t) + cropped->infoheader.biSizeImage;

    cropped->pixels = (pixel_t*)malloc(width * height * sizeof(pixel_t));
    if (cropped->pixels == NULL){
        printf("Memory allocation for pixels failed\n");
        free(cropped);
        return NULL;
    }

    int src_y;
    if (pic->infoheader.biHeight > 0) 
    	src_y = pic->infoheader.biHeight - y - height; // Bottom-up
    else src_y = y; // Top-down
    

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int src_index = (src_y + row) * img_width + (x + col);
            int dst_index = row * width + col;
            cropped->pixels[dst_index] = pic->pixels[src_index];
        }
    }

    return cropped;
}

int bmp_save(const bmp_t* bmp, const char* filename){
	if (bmp == NULL || filename == NULL) {
        printf("Invalid parameters\n");
        return -1;
    }

    FILE* file = fopen(filename, "wb");
	if (file == NULL) {
        printf("Failed to open file for writing\n");
        return -1;
    }

	if (fwrite(&bmp->fileheader, sizeof(bmp_fileheader_t), 1, file) != 1) {
        printf("Failed to write file header\n");
        fclose(file);
        return -1;
    }

    if (fwrite(&bmp->infoheader, sizeof(bmp_infoheader_t), 1, file) != 1) {
        printf("Failed to write info header\n");
        fclose(file);
        return -1;
    }

    int width = bmp->infoheader.biWidth;
    int height = abs(bmp->infoheader.biHeight);
    int row_padded = (width * sizeof(pixel_t) + 3) & ~3;
    int padding = row_padded - width * sizeof(pixel_t);
    char pad[3] = {0, 0, 0};

    for (int i = 0; i < height; i++) {
        if (fwrite(&bmp->pixels[i * width], sizeof(pixel_t), width, file) != (size_t)width) {
            printf("Failed to write pixel data\n");
            fclose(file);
            return -1;
        }
        if (padding > 0 && fwrite(pad, 1, padding, file) != (size_t)padding) {
            printf("Failed to write padding\n");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

void bmp_free(bmp_t* bmp){
    if (bmp) {
        free(bmp->pixels);
        free(bmp);
    }
}

void rotate_90_clockwise(bmp_t* bmp) {
    if (bmp == NULL || bmp->pixels == NULL){
        printf("Invalid BMP image\n");
        return;
    }

    int old_width = bmp->infoheader.biWidth;
    int old_height = abs(bmp->infoheader.biHeight);
    
    pixel_t* rotated_pixels = (pixel_t*)malloc(old_width * old_height * sizeof(pixel_t));
    if (rotated_pixels == NULL){
        printf("Memory allocation failed\n");
        return;
    }

    // 0	1 	2
    // 3 	4	5
    // 6 	7	8
    // 9	10	11
    //______________		
    // 0|2	1|5 	2	3
    // 4|1 	5|4		6	7
    // 8|0 	9|3		10	11
    //______________


    for (int y = 0; y < old_height; y++){
        for (int x = 0; x < old_width; x++){
            rotated_pixels[x * old_height + old_height - 1 - y] = bmp->pixels[y * old_width + x];
        }
    }

    bmp->infoheader.biWidth = old_height;
    bmp->infoheader.biHeight = old_width;
    
    free(bmp->pixels);
    bmp->pixels = rotated_pixels;
}

