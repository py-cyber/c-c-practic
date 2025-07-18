#include <stdio.h>
#include <string.h>
#include <stddef.h> 
#include "str.h"


signed main(){
    char* str1 = "hello";
    char str2[40] = {0};
    
    my_str_cpy(str2, str1);
    printf("str1: %s | str2: %s\n", str1, str2);
    printf("lenstr1: %zu | lenstr2: %zu\n", my_str_len(str1), my_str_len(str2));

    str1 = NULL;
    printf("Length: %zu\n", my_str_len(str1));
    my_str_cat(str2, str1);
    printf("Concat string: %s\n", str2);
    printf("Length: %zu\n", my_str_len(str2));

    char *s1 = "abc", *s2 = NULL;
    printf("%d\n", my_str_cmp(s1, s2));

    return 0;
}
