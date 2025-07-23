#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdlib.h>
#include <stdio.h>

#define ASSERT_EQUAL(actual, expected, message) \
    do { \
        if ((actual) != (expected)) { \
            printf("❌ Test failed: %s. Expected %d, got %d\n", \
                   message, (expected), (actual)); \
            exit(1); \
        } \
    } while (0)

#define ASSERT_ARRAY_EQUAL(actual, expected, size, message) \
    do { \
        for (int i = 0; i < (size); i++) { \
            if ((actual)[i] != (expected)[i]) { \
                printf("❌ Test failed: %s. At index %d: expected %d, got %d\n", \
                       message, i, (expected)[i], (actual)[i]); \
                exit(1); \
            } \
        } \
    } while (0)

#endif
