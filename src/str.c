#include "str.h"
#include <stddef.h> 

char* my_str_cpy(char* destination, const char* source){
    if (!destination || !source) return destination;

    char* temp = destination;
    while ((*destination++ = *source++));
    return temp;
}

size_t my_str_len(const char* source){
    if (!source) return 0;

    const char* str = source;
    while (*source++);
    return source - str - 1;
}

char* my_str_cat(char* destination, const char* source){
    if (!destination || !source) return destination;

    char* temp = destination;
    while (*destination++);
    destination--;

    while ((*destination++ = *source++));
    return temp;
}

int my_str_cmp(const char* str1, const char* str2){
    if (!str1 || !str2){
        if (!str1 && !str2) return 0;
        return (!str1 ? -1 : 1);
    }

    while (*str1 && (*str1++ == *str2++));
    str1--; str2--;
    return *str1 - *str2;
}
