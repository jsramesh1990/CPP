# Inline Function in C++

## Table of Contents

1. What is an Inline Function?
2. Why Do We Need Inline?
3. Function Call Overhead
4. How Inline Works
5. Syntax
6. Example
7. What Happens When Code Hits It?
8. Inline vs Normal Function
9. Advantages
10. Limitations
11. Inline in Classes
12. Inline and Compiler Optimization
13. Real-Time Embedded Examples
14. Interview Questions
15. Quick Revision
16. Interview Answer (2 Minutes)

---

# What is an Inline Function?

## Definition

An **inline function** is a function where the compiler attempts to replace the function call with the actual function code during compilation.

Instead of:

```cpp
add(10, 20);
```

the compiler may replace it with:

```cpp
10 + 20;
```

directly.

---

## Simple Definition

> Inline functions reduce function call overhead by expanding the function code at the place where it is called.

---

# Why Do We Need Inline?

Normal function calls involve extra operations:

```text
Call Function
Push Parameters
Save Registers
Jump To Function
Execute Function
Return Back
Restore Registers
```

This consumes CPU cycles.

For very small functions:

```cpp
int add(int a, int b)
{
    return a + b;
}
```

Function call overhead may be larger than the actual work.

Inline helps eliminate this overhead.

---

# Function Call Overhead

Normal Function:

```cpp
int add(int a, int b)
{
    return a + b;
}

int main()
{
    int x = add(5,10);
}
```

Runtime:

```text
main()
   ↓
Call add()
   ↓
Execute
   ↓
Return
```

Extra stack operations occur.

---

# How Inline Works

Example:

```cpp
inline int add(int a, int b)
{
    return a + b;
}
```

Call:

```cpp
int x = add(5,10);
```

Compiler may generate:

```cpp
int x = 5 + 10;
```

No function call.

---

# Syntax

```cpp
inline return_type function_name(parameters)
{
    // code
}
```

Example:

```cpp
inline int square(int x)
{
    return x * x;
}
```

---

# Example

```cpp
#include <iostream>
using namespace std;

inline int square(int x)
{
    return x * x;
}

int main()
{
    cout << square(5);
}
```

Output:

```text
25
```

---

# What Happens When Code Hits It?

Example:

```cpp
inline int add(int a, int b)
{
    return a + b;
}

int main()
{
    int result = add(10,20);
}
```

---

### Compile Time

Compiler sees:

```cpp
add(10,20)
```

---

### Expansion

May replace with:

```cpp
int result = 10 + 20;
```

---

### Generated Code

Instead of:

```text
CALL add
```

Compiler may generate:

```text
MOV
ADD
STORE
```

directly.

---

### Interview Answer

**What happens when code hits an inline function?**

The compiler may replace the function call with the actual function body during compilation. This removes function call overhead such as stack operations, parameter passing, and return handling. The result is potentially faster execution, especially for small frequently called functions.

---

# Inline vs Normal Function

| Feature           | Normal Function | Inline Function            |
| ----------------- | --------------- | -------------------------- |
| Function Call     | Yes             | Usually No                 |
| Call Overhead     | Present         | Reduced                    |
| Code Size         | Smaller         | Larger                     |
| Speed             | Slower          | Faster for small functions |
| Compiler Decision | Mandatory call  | Compiler may inline        |

---

# Advantages

## Faster Execution

No function call overhead.

---

## Better for Small Functions

Example:

```cpp
inline int max(int a, int b)
{
    return a > b ? a : b;
}
```

---

## Useful in Embedded Systems

Reduces CPU cycles.

---

## Improves Performance

Especially in:

```text
Getters
Setters
Math Functions
Utility Functions
```

---

# Limitations

## Larger Binary Size

Example:

```cpp
square();
square();
square();
square();
```

Compiler may duplicate code multiple times.

This is called:

```text
Code Bloat
```

---

## Compiler May Ignore Inline

Important interview point.

```cpp
inline
```

is only a request.

Compiler can refuse.

---

Example:

```cpp
inline void hugeFunction()
{
    // 500 lines
}
```

Compiler may not inline it.

---

# Inline in Classes

Functions defined inside a class are automatically treated as inline candidates.

Example:

```cpp
class Calculator
{
public:

    int add(int a, int b)
    {
        return a+b;
    }
};
```

Compiler may inline `add()`.

---

# Inline and Compiler Optimization

Modern compilers decide automatically.

Even without:

```cpp
inline
```

compiler may inline:

```cpp
int add(int a, int b)
{
    return a+b;
}
```

if optimization is enabled.

Example:

```bash
-O2
-O3
```

---

Important:

```text
inline keyword
≠
Guaranteed Inline
```

---

# Real-Time Embedded Examples

## Example 1: GPIO Read

```cpp
inline bool readPin()
{
    return GPIOA->IDR & (1<<5);
}
```

Called thousands of times.

---

## Example 2: Bit Manipulation

```cpp
inline void setBit(uint32_t &x)
{
    x |= (1<<3);
}
```

Fast execution.

---

## Example 3: CAN Driver

```cpp
inline uint8_t getDLC()
{
    return CAN->DLC;
}
```

Removes call overhead.

---

## Example 4: RTOS Tick Check

```cpp
inline uint32_t getTick()
{
    return tickCount;
}
```

Frequently used.

---

# Interview Questions

## What is an Inline Function?

An inline function is a function whose code may be expanded directly at the call site to reduce function call overhead.

---

## Why Use Inline?

To improve performance for small frequently called functions.

---

## Does Inline Guarantee Inlining?

No.

Important answer:

> `inline` is only a compiler request. The compiler may ignore it.

---

## What Happens When Code Hits an Inline Function?

The compiler may replace the function call with the function body during compilation, eliminating call overhead.

---

## What is Code Bloat?

When excessive inlining increases executable size because function code is duplicated at multiple call sites.

---

## Are Class Member Functions Inline?

Functions defined inside the class definition are automatically inline candidates.

---

# Most Asked Interview Question

## Difference Between Macro and Inline Function

### Macro

```cpp
#define SQUARE(x) x*x
```

Problems:

```cpp
SQUARE(2+3)
```

becomes:

```cpp
2+3*2+3
```

Result:

```text
11
```

Wrong.

---

### Inline Function

```cpp
inline int square(int x)
{
    return x*x;
}
```

```cpp
square(2+3)
```

Result:

```text
25
```

Correct.

---

| Macro            | Inline        |
| ---------------- | ------------- |
| No Type Checking | Type Safe     |
| Text Replacement | Real Function |
| Hard to Debug    | Easy to Debug |
| Error Prone      | Safer         |

---

# Interview Answer (2 Minutes)

Inline functions are functions that the compiler may expand directly at the point of call instead of generating a normal function call. This reduces overhead associated with stack operations, parameter passing, and return instructions. Inline functions are most useful for small, frequently called functions such as getters, setters, and utility functions. The `inline` keyword is only a suggestion to the compiler, not a guarantee. Excessive inlining can increase executable size, a phenomenon known as code bloat. Modern compilers often perform automatic inlining during optimization.

---

# Quick Revision

```text
Inline Function

Purpose:
Reduce Function Call Overhead

Syntax:

inline int add(int a,int b)
{
    return a+b;
}

Working:

Function Call
      ↓
Compiler Expands Code
      ↓
No CALL Instruction

Advantages:
✔ Faster
✔ Efficient
✔ Good For Small Functions

Disadvantages:
✔ Code Bloat
✔ Not Guaranteed

Important:

inline = Request
NOT Guarantee

Difference:

Macro:
Text Replacement

Inline:
Type Safe Function

Embedded Use:
✔ GPIO Access
✔ Bit Operations
✔ Drivers
✔ RTOS Utilities
```

---

# Conclusion

Inline functions are a C++ optimization feature used to reduce function call overhead by expanding function code directly at the call site. They are particularly useful in embedded systems, device drivers, firmware, and performance-critical applications where small functions are called frequently. Understanding inline functions, compiler behavior, code bloat, and the difference between macros and inline functions is a common requirement in C++ and Embedded Systems interviews.
