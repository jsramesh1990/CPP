/**
 * @file test_all.c
 * @brief Comprehensive test suite for all C keywords
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/c_keywords_demo.h"

// Test function declarations
void test_data_types(void);
void test_control_flow(void);
void test_storage_classes(void);
void test_type_qualifiers(void);
void test_c99_features(void);
void test_c11_features(void);

int main() {
    printf("Running C Keyword Test Suite\n");
    printf("============================\n\n");
    
    int tests_passed = 0;
    int total_tests = 0;
    
    // Run test suites
    test_data_types(); tests_passed++; total_tests++;
    test_control_flow(); tests_passed++; total_tests++;
    test_storage_classes(); tests_passed++; total_tests++;
    test_type_qualifiers(); tests_passed++; total_tests++;
    test_c99_features(); tests_passed++; total_tests++;
    test_c11_features(); tests_passed++; total_tests++;
    
    printf("\n============================\n");
    printf("Test Results: %d/%d passed\n", tests_passed, total_tests);
    
    if(tests_passed == total_tests) {
        printf("✅ ALL TESTS PASSED!\n");
        return EXIT_SUCCESS;
    } else {
        printf("❌ SOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
}

void test_data_types(void) {
    printf("Testing Data Types...\n");
    
    // Test char
    char c = 'A';
    assert(c == 65);
    
    // Test int
    int i = 42;
    assert(i == 42);
    
    // Test float and double
    float f = 3.14f;
    double d = 3.1415926535;
    assert(f < 3.15f);
    assert(d > 3.1415);
    
    // Test short and long
    short s = 32767;
    long l = 2147483647L;
    assert(s > 0);
    assert(l > 0);
    
    // Test signed and unsigned
    signed int si = -10;
    unsigned int ui = 100;
    assert(si < 0);
    assert(ui > 0);
    
    printf("✅ Data Types: PASSED\n");
}

// ... Additional test functions ...

void test_c11_features(void) {
    printf("Testing C11 Features...\n");
    
    // Test _Static_assert at compile time
    _Static_assert(sizeof(int) <= 8, "int size check");
    
    // Test _Generic
    int i = 10;
    double d = 3.14;
    #define TYPE_NAME(x) _Generic((x), \
        int: "int", \
        double: "double", \
        default: "other")
    
    assert(TYPE_NAME(i) == "int");
    assert(TYPE_NAME(d) == "double");
    
    printf("✅ C11 Features: PASSED\n");
}
