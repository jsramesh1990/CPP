/**
 * @file typedef_demo.c
 * @brief Demonstration of 'typedef' keyword
 */

#include <stdio.h>
#include <stdlib.h>

// Basic typedef for primitive type
typedef unsigned int uint;
typedef float real_number;

// Typedef for array type
typedef int IntArray[10];

// Typedef for function pointer
typedef int (*MathOperation)(int, int);

// Typedef for struct
typedef struct {
    int x;
    int y;
} Point;

// Typedef for enum
typedef enum { MON, TUE, WED, THU, FRI, SAT, SUN } Weekday;

// Function using typedefs
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

void perform_operation(MathOperation op, int a, int b) {
    int result = op(a, b);
    printf("Operation result: %d\n", result);
}

int main() {
    printf("=== typedef Keyword Demonstration ===\n\n");
    
    // Using primitive typedef
    uint count = 100;
    real_number pi = 3.14159f;
    printf("1. Primitive typedefs:\n");
    printf("   Unsigned int: %u\n", count);
    printf("   Real number: %.5f\n\n", pi);
    
    // Using array typedef
    IntArray numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("2. Array typedef:\n");
    printf("   Third element: %d\n\n", numbers[2]);
    
    // Using struct typedef
    Point p1 = {10, 20};
    printf("3. Struct typedef:\n");
    printf("   Point coordinates: (%d, %d)\n\n", p1.x, p1.y);
    
    // Using enum typedef
    Weekday today = WED;
    printf("4. Enum typedef:\n");
    printf("   Today is day number: %d\n\n", today);
    
    // Using function pointer typedef
    printf("5. Function pointer typedef:\n");
    perform_operation(add, 5, 3);
    perform_operation(multiply, 5, 3);
    
    // Typedef for complex declarations (readability)
    typedef int (*Comparator)(const void*, const void*);
    Comparator cmp = NULL;
    printf("\n6. Complex declaration simplified with typedef\n");
    
    // Typedef for portable types
    typedef unsigned char byte;
    byte data[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    printf("7. Portable type (byte): ");
    for(int i = 0; i < 4; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    
    // Benefits of typedef
    printf("\n=== Benefits of typedef ===\n");
    printf("1. Improves code readability\n");
    printf("2. Creates platform-independent types\n");
    printf("3. Simplifies complex declarations\n");
    printf("4. Makes code more maintainable\n");
    
    return 0;
}
