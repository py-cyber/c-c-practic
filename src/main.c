#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "str.h"
#include "merge_sort.h"


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

    // ________________________

    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    merge_sort(arr, arr + size);

    printf("After sorting: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // ______________________

    return 0;
}
