#include "merge_sort.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

void test_empty_array() {
    int arr[1] = {0};
    merge_sort(arr, arr);
    printf("✅ test_empty_array passed\n");
}

void test_single_element() {
    int arr[] = {42};
    merge_sort(arr, arr + 1);
    ASSERT_EQUAL(arr[0], 42, "single element");
    printf("✅ test_single_element passed\n");
}

void test_sorted_array() {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    merge_sort(arr, arr + 5);
    ASSERT_ARRAY_EQUAL(arr, expected, 5, "sorted array");
    printf("✅ test_sorted_array passed\n");
}

void test_reverse_array() {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    merge_sort(arr, arr + 5);
    ASSERT_ARRAY_EQUAL(arr, expected, 5, "reverse array");
    printf("✅ test_reverse_array passed\n");
}

void test_random_array() {
    int arr[100];
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 1000;
    }
    
    merge_sort(arr, arr + 100);
    
    for (int i = 0; i < 99; i++) {
        if (arr[i] > arr[i+1]) {
            printf("❌ test_random_array failed at index %d\n", i);
            exit(1);
        }
    }
    printf("✅ test_random_array passed\n");
}
