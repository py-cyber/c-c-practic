#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"

void merge(int* left, int* mid, int* right) {
    int size = right - left;
    int* temp = malloc(size * sizeof(int));
    int* i = left;
    int* j = mid;
    int k = 0;

    while (i < mid && j < right) {
        if (*i <= *j) {
            temp[k++] = *i++;
        } else {
            temp[k++] = *j++;
        }
    }

    while (i < mid) temp[k++] = *i++;
    while (j < right) temp[k++] = *j++;

    for (int p = 0; p < k; p++) {
        left[p] = temp[p];
    }

    free(temp);
}

void merge_sort(int* left, int* right) {
    if (right - left <= 1) return;

    int* mid = left + (right - left) / 2;

    merge_sort(left, mid);
    merge_sort(mid, right);

    merge(left, mid, right);
}
