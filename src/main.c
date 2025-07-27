#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "str.h"
#include "merge_sort.h"
#include "intrusive_list.h"
#include "bmp_redactor.h"


signed main(){
    // char* str1 = "hello";
    // char str2[40] = {0};
    
    // my_str_cpy(str2, str1);
    // printf("str1: %s | str2: %s\n", str1, str2);
    // printf("lenstr1: %zu | lenstr2: %zu\n", my_str_len(str1), my_str_len(str2));

    // str1 = NULL;
    // printf("Length: %zu\n", my_str_len(str1));
    // my_str_cat(str2, str1);
    // printf("Concat string: %s\n", str2);
    // printf("Length: %zu\n", my_str_len(str2));

    // char *s1 = "abc", *s2 = NULL;
    // printf("%d\n", my_str_cmp(s1, s2));

    // // ________________________

    // int arr[] = {12, 11, 13, 5, 6, 7};
    // int size = sizeof(arr) / sizeof(arr[0]);

    // printf("Before sorting: ");
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    // merge_sort(arr, arr + size);

    // printf("After sorting: ");
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    // // ______________________

    // intrusive_list my_list;
    // init_list(&my_list);
    
    // intrusive_node node1, node2;
    
    // add_node(&(my_list.head), &node1);
    // add_node(&node1, &node2);
    
    // printf("Length: %d\n", get_length(&my_list));
    
    // remove_node(&node1);
    
    // printf("Length after removal: %d\n", get_length(&my_list));

    // // ______________________

    // bmp_t* load_bmp(const char* filename);
    // bmp_t* crop(bmp_t* pic, int x, int y, int width, int height);
    // int bmp_save(const bmp_t* bmp, const char* filename);
    // void bmp_free(bmp_t* bmp);

    bmp_t* origin = load_bmp("/Users/user1/Desktop/Airplane.bmp");
    bmp_t* cropped = crop(origin, 0, 0, 300, 400);
    rotate_90_clockwise(cropped);
    if (bmp_save(cropped, "/Users/user1/Desktop/Cropped.bmp") != 0) {
        printf("Failed to save cropped image\n");
    }
    bmp_free(origin);
    bmp_free(cropped);

    return 0;
}
