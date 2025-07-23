#include "test_utils.h"
#include "merge_sort.h"
#include <stdio.h>


void test_empty_array();
void test_single_element();
void test_sorted_array();
void test_reverse_array();
void test_random_array();


int main() {
    printf("Running merge sort tests...\n");
    
    test_empty_array();
    test_single_element();
    test_sorted_array();
    test_reverse_array();
    test_random_array();
    
    printf("🎉 All tests passed successfully!\n");
    return 0;
}
