/**
 * @file main.c
 * @brief Main program demonstrating ALL C keywords with practical examples
 * @details This project showcases every C keyword with real-world examples
 */


/**
 * @file main.c
 * @brief Main program demonstrating ALL C keywords
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>
#include <stdatomic.h>
#include <threads.h>
#include <assert.h>
#include "c_keywords_demo.h"

int main(void) {
    printf("========================================\n");
    printf("      C KEYWORD MASTERY PROJECT\n");
    printf("========================================\n");
    printf("Demonstrating ALL C Keywords\n");
    printf("C Standards: C89, C99, C11\n");
    printf("Total Keywords: 44\n");
    printf("========================================\n\n");

    // Demonstrate by C Standard
    demonstrate_c89_keywords();
    demonstrate_c99_keywords();
    demonstrate_c11_keywords();

    printf("\n========================================\n");
    printf("    ALL KEYWORDS DEMONSTRATED!\n");
    printf("========================================\n");
    
    return EXIT_SUCCESS;
}
