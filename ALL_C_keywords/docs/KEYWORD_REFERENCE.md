# Complete C Keyword Reference

## Keyword Categories

### 1. Data Type Keywords
**Purpose**: Define the type of data

| Keyword | Description | Example | Standard |
|---------|-------------|---------|----------|
| `char` | Character type | `char c = 'A';` | C89 |
| `int` | Integer type | `int count = 42;` | C89 |
| `float` | Single precision float | `float pi = 3.14f;` | C89 |
| `double` | Double precision float | `double pi = 3.14159;` | C89 |
| `void` | No type/empty | `void func(void);` | C89 |
| `_Bool` | Boolean type (C99) | `_Bool flag = 1;` | C99 |
| `_Complex` | Complex numbers | `double _Complex z;` | C99 |

### 2. Type Modifier Keywords
**Purpose**: Modify basic data types

| Keyword | Description | Example |
|---------|-------------|---------|
| `short` | Shorter integer | `short s = 100;` |
| `long` | Longer integer | `long l = 1000L;` |
| `signed` | Signed integer | `signed int si = -10;` |
| `unsigned` | Unsigned integer | `unsigned int ui = 100;` |

### 3. Storage Class Keywords
**Purpose**: Control storage duration and linkage

| Keyword | Description | Example |
|---------|-------------|---------|
| `auto` | Automatic storage (default) | `auto int x = 5;` |
| `static` | Persistent storage | `static int counter;` |
| `extern` | External linkage | `extern int global_var;` |
| `register` | Register storage hint | `register int i;` |
| `_Thread_local` | Thread storage (C11) | `_Thread_local int tls;` |

### 4. Control Flow Keywords
**Purpose**: Control program execution flow

| Keyword | Description | Example |
|---------|-------------|---------|
| `if` | Conditional execution | `if (x > 0) { ... }` |
| `else` | Alternative execution | `else { ... }` |
| `switch` | Multi-way branch | `switch (value) { ... }` |
| `case` | Switch case label | `case 1: ...` |
| `default` | Switch default case | `default: ...` |
| `for` | Counting loop | `for (int i=0; i<10; i++)` |
| `while` | Pre-test loop | `while (x > 0) { ... }` |
| `do` | Post-test loop | `do { ... } while (x>0);` |
| `break` | Exit loop/switch | `break;` |
| `continue` | Skip to next iteration | `continue;` |
| `goto` | Unconditional jump | `goto label;` |
| `return` | Return from function | `return 0;` |

### 5. Compound Data Type Keywords
**Purpose**: Define complex data structures

| Keyword | Description | Example |
|---------|-------------|---------|
| `struct` | Structure type | `struct Point { int x, y; };` |
| `union` | Union type | `union Data { int i; float f; };` |
| `enum` | Enumerated type | `enum Color { RED, GREEN };` |

### 6. Type Definition Keyword
**Purpose**: Create type aliases

| Keyword | Description | Example |
|---------|-------------|---------|
| `typedef` | Type alias | `typedef int Integer;` |

### 7. Operator Keywords
**Purpose**: Special operators

| Keyword | Description | Example |
|---------|-------------|---------|
| `sizeof` | Size of type/variable | `sizeof(int)` |

### 8. Type Qualifier Keywords
**Purpose**: Add special properties to types

| Keyword | Description | Example |
|---------|-------------|---------|
| `const` | Read-only variable | `const int MAX = 100;` |
| `volatile` | May change unexpectedly | `volatile int *reg;` |
| `restrict` | No aliasing guarantee (C99) | `void f(int *restrict p);` |

### 9. C99-Specific Keywords
**Purpose**: C99 standard additions

| Keyword | Description | Example |
|---------|-------------|---------|
| `inline` | Inline function expansion | `inline int sqr(int x);` |
| `_Imaginary` | Imaginary numbers | `float _Imaginary z;` |

### 10. C11-Specific Keywords
**Purpose**: C11 standard additions

| Keyword | Description | Example |
|---------|-------------|---------|
| `_Alignas` | Specify alignment | `_Alignas(16) int x;` |
| `_Alignof` | Get alignment | `_Alignof(double)` |
| `_Atomic` | Atomic operations | `_Atomic int counter;` |
| `_Generic` | Generic selection | `_Generic(x, int: "int")` |
| `_Noreturn` | Function doesn't return | `_Noreturn void exit();` |
| `_Static_assert` | Compile-time assertion | `_Static_assert(...)` |

## Detailed Examples by Category

### Data Types Deep Dive
```c
// Character types
char letter = 'A';                    // Basic character
unsigned char byte = 255;             // Unsigned byte
signed char sbyte = -128;             // Signed byte

// Integer types
int normal = 42;                      // Usually 32-bit
short small = 32767;                  // Usually 16-bit
long large = 2147483647L;             // Usually 32-bit or 64-bit
long long very_large = 9223372036854775807LL;  // C99, usually 64-bit

// Floating point
float single = 3.14159f;              // Single precision (32-bit)
double dbl = 3.141592653589793;       // Double precision (64-bit)
long double ldbl = 3.14159265358979323846L;  // Extended precision
