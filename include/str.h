#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED

#include <stddef.h> 

char* my_str_cpy(char* destination, const char* source);
size_t my_str_len(const char* source);
char* my_str_cat(char* destination, const char* source);
int my_str_cmp(const char* str1, const char* str2);

#endif
