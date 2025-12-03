#include "c_keywords_demo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>
#include <stdatomic.h>
#include <stdalign.h>
#include <stdnoreturn.h>
#include <threads.h>
#include <assert.h>
#include <setjmp.h>

#define MAX_BIT_POSITION 31

// Forward declarations for helper functions used in C99/C11
static inline int square(int x);
static void add_arrays(int *restrict a, int *restrict b, int *restrict c, int n);
noreturn void fatal_error(void);

// Thread-local variable must be at file scope
_Thread_local int thread_specific = 0;

// External variable declaration
int external_var = 999;

// ========== C89/C90 KEYWORDS (32) ==========

void demonstrate_c89_keywords(void) {
    printf("\n=== C89/C90 KEYWORDS (32) ===\n\n");
    
    // 1. auto (automatic storage class)
    printf("1. 'auto' keyword:\n");
    {
        auto int auto_var = 42;  // 'auto' is implicit, rarely used
        printf("   auto variable: %d\n", auto_var);
    }
    
    // 2. break
    printf("\n2. 'break' keyword:\n");
    for(int i = 0; i < 10; i++) {
        if(i == 5) {
            printf("   Breaking at i = %d\n", i);
            break;
        }
    }
    
    // 3. case
    printf("\n3. 'case' keyword:\n");
    int switch_var = 2;
    switch(switch_var) {
        case 1:
            printf("   Case 1 selected\n");
            break;
        case 2:
            printf("   Case 2 selected\n");
            break;
        default:
            printf("   Default case\n");
    }
    
    // 4. char
    printf("\n4. 'char' keyword:\n");
    char character = 'A';
    printf("   Character: %c, ASCII: %d\n", character, character);
    
    // 5. const
    printf("\n5. 'const' keyword:\n");
    const int immutable = 100;
    printf("   Constant value: %d (cannot be modified)\n", immutable);
    
    // 6. continue
    printf("\n6. 'continue' keyword:\n");
    printf("   Numbers 1-10 skipping 5: ");
    for(int i = 1; i <= 10; i++) {
        if(i == 5) continue;
        printf("%d ", i);
    }
    printf("\n");
    
    // 7. default
    printf("\n7. 'default' keyword:\n");
    // Demonstrated with switch above
    
    // 8. do
    printf("\n8. 'do' keyword:\n");
    int counter = 0;
    do {
        printf("   Do-while iteration: %d\n", counter);
        counter++;
    } while(counter < 3);
    
    // 9. double
    printf("\n9. 'double' keyword:\n");
    double pi = 3.141592653589793;
    printf("   Double precision pi: %.15f\n", pi);
    
    // 10. else
    printf("\n10. 'else' keyword:\n");
    int test = 10;
    if(test > 20) {
        printf("   Test is greater than 20\n");
    } else {
        printf("   Test is 20 or less (value: %d)\n", test);
    }
    
    // 11. enum
    printf("\n11. 'enum' keyword:\n");
    enum Color { RED, GREEN, BLUE };
    enum Color my_color = GREEN;
    printf("   Enum value: %d\n", my_color);
    
    // 12. extern
    printf("\n12. 'extern' keyword:\n");
    extern int external_var;  // Declared elsewhere
    printf("   External variable: %d\n", external_var);
    
    // 13. float
    printf("\n13. 'float' keyword:\n");
    float temperature = 36.6f;
    printf("   Float temperature: %.2f°C\n", temperature);
    
    // 14. for
    printf("\n14. 'for' keyword:\n");
    printf("   Counting with for loop: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // 15. goto (Use with caution!)
    printf("\n15. 'goto' keyword:\n");
    int goto_counter = 0;
    
    goto_label:
    if(goto_counter < 2) {
        printf("   Goto iteration: %d\n", goto_counter);
        goto_counter++;
        goto goto_label;
    }
    
    // 16. if
    printf("\n16. 'if' keyword:\n");
    if(1 < 2) {
        printf("   1 is indeed less than 2\n");
    }
    
    // 17. int
    printf("\n17. 'int' keyword:\n");
    int integer = 42;
    printf("   Integer: %d\n", integer);
    
    // 18. long
    printf("\n18. 'long' keyword:\n");
    long big_number = 1000000L;
    printf("   Long integer: %ld\n", big_number);
    
    // 19. register (hint to compiler)
    printf("\n19. 'register' keyword:\n");
    register int fast_access = 99;
    printf("   Register variable: %d\n", fast_access);
    
    // 20. return
    printf("\n20. 'return' keyword:\n");
    // Demonstrated by function return
    
    // 21. short
    printf("\n21. 'short' keyword:\n");
    short small_number = 32767;
    printf("   Short integer: %d\n", small_number);
    
    // 22. signed
    printf("\n22. 'signed' keyword:\n");
    signed int negative = -10;
    printf("   Signed integer: %d\n", negative);
    
    // 23. sizeof
    printf("\n23. 'sizeof' keyword:\n");
    printf("   Size of int: %zu bytes\n", sizeof(int));
    printf("   Size of double: %zu bytes\n", sizeof(double));
    
    // 24. static
    printf("\n24. 'static' keyword:\n");
    static int persistent = 0;
    persistent++;
    printf("   Static variable retains value: %d\n", persistent);
    
    // 25. struct
    printf("\n25. 'struct' keyword:\n");
    struct Point {
        int x;
        int y;
    };
    struct Point p1 = {10, 20};
    printf("   Struct Point: (%d, %d)\n", p1.x, p1.y);
    
    // 26. switch
    printf("\n26. 'switch' keyword:\n");
    // Demonstrated above with case
    
    // 27. typedef
    printf("\n27. 'typedef' keyword:\n");
    typedef unsigned int uint;
    uint custom_type = 100;
    printf("   Typedef alias used: %u\n", custom_type);
    
    // 28. union
    printf("\n28. 'union' keyword:\n");
    union Data {
        int i;
        float f;
        char str[20];
    };
    union Data data;
    data.i = 10;
    printf("   Union storing integer: %d\n", data.i);
    
    // 29. unsigned
    printf("\n29. 'unsigned' keyword:\n");
    unsigned int positive_only = 4000000000;
    printf("   Unsigned integer: %u\n", positive_only);
    
    // 30. void
    printf("\n30. 'void' keyword:\n");
    void *generic_pointer = &integer;
    printf("   Void pointer points to: %p\n", (void*)generic_pointer);
    
    // 31. volatile
    printf("\n31. 'volatile' keyword:\n");
    volatile int hardware_register = 0;
    printf("   Volatile variable: %d\n", hardware_register);
    
    // 32. while
    printf("\n32. 'while' keyword:\n");
    int while_count = 0;
    printf("   While loop: ");
    while(while_count < 3) {
        printf("%d ", while_count);
        while_count++;
    }
    printf("\n");
}

// ========== C99 KEYWORDS (5 additional) ==========

// Helper functions for C99
static inline int square(int x) { 
    return x * x; 
}

static void add_arrays(int *restrict a, int *restrict b, int *restrict c, int n) {
    for(int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void demonstrate_c99_keywords(void) {
    printf("\n=== C99 ADDITIONAL KEYWORDS (5) ===\n\n");
    
    // 33. _Bool (C99) - Also bool from stdbool.h
    printf("33. '_Bool' and 'bool' keywords (C99):\n");
    _Bool b1 = 1;  // Non-zero is true
    bool b2 = false; // From stdbool.h
    printf("   _Bool value: %d\n", b1);
    printf("   bool value: %s\n", b2 ? "true" : "false");
    
    // 34. _Complex (C99)
    printf("\n34. '_Complex' keyword (C99):\n");
    double _Complex z1 = 3.0 + 4.0 * I;
    printf("   Complex number: %.1f + %.1fi\n", 
           creal(z1), cimag(z1));
    
    // 35. _Imaginary (C99, optional)
    printf("\n35. '_Imaginary' keyword (C99, optional):\n");
    // Note: _Imaginary is rarely implemented
    printf("   Rarely used in implementations\n");
    
    // 36. inline (C99)
    printf("\n36. 'inline' keyword (C99):\n");
    // inline function demonstration
    printf("   Inline function square(5): %d\n", square(5));
    
    // 37. restrict (C99)
    printf("\n37. 'restrict' keyword (C99):\n");
    int arr[5] = {1, 2, 3, 4, 5};
    int brr[5] = {10, 20, 30, 40, 50};
    int crr[5];
    add_arrays(arr, brr, crr, 5);
    printf("   Restrict pointer optimization used\n");
    printf("   Result array: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", crr[i]);
    }
    printf("\n");
}

// ========== C11 KEYWORDS (7 additional) ==========

noreturn void fatal_error(void) {
    printf("   Fatal error occurred. Exiting...\n");
    exit(EXIT_FAILURE);
}

void demonstrate_c11_keywords(void) {
    printf("\n=== C11 ADDITIONAL KEYWORDS (7) ===\n\n");
    
    // 38. _Alignas (C11)
    printf("38. '_Alignas' keyword (C11):\n");
    _Alignas(16) int aligned_data[4];
    printf("   Memory aligned to 16 bytes\n");
    printf("   Alignment: %zu\n", alignof(aligned_data));
    
    // 39. _Alignof (C11)
    printf("\n39. '_Alignof' keyword (C11):\n");
    printf("   Alignment of int: %zu\n", _Alignof(int));
    printf("   Alignment of double: %zu\n", _Alignof(double));
    
    // 40. _Atomic (C11)
    printf("\n40. '_Atomic' keyword (C11):\n");
    _Atomic int atomic_counter = 0;
    atomic_fetch_add(&atomic_counter, 1);
    printf("   Atomic counter after increment: %d\n", atomic_counter);
    
    // 41. _Generic (C11)
    printf("\n41. '_Generic' keyword (C11):\n");
    #define get_type_name(x) _Generic((x), \
        int: "int", \
        double: "double", \
        char*: "string", \
        default: "unknown" \
    )
    
    int i = 42;
    double d = 3.14;
    char* s = "hello";
    printf("   Type of i (42): %s\n", get_type_name(i));
    printf("   Type of d (3.14): %s\n", get_type_name(d));
    printf("   Type of s (\"hello\"): %s\n", get_type_name(s));
    
    // 42. _Noreturn (C11)
    printf("\n42. '_Noreturn' keyword (C11):\n");
    printf("   _Noreturn function declared (won't return to caller)\n");
    // Note: We don't actually call fatal_error() as it would exit
    
    // 43. _Static_assert (C11)
    printf("\n43. '_Static_assert' keyword (C11):\n");
    _Static_assert(sizeof(int) == 4, "int must be 4 bytes");
    _Static_assert(sizeof(char) == 1, "char must be 1 byte");
    printf("   Static assertions passed\n");
    
    // 44. _Thread_local (C11)
    printf("\n44. '_Thread_local' keyword (C11):\n");
    printf("   Thread-local variable value: %d\n", thread_specific);
    thread_specific = 42;
    printf("   Thread-local variable after modification: %d\n", thread_specific);
}
