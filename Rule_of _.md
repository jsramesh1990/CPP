# Rule of 3 (Rule of Three)

## Table of Contents

1. [Introduction](#introduction)
2. [Why Rule of 3 Exists](#why-rule-of-3-exists)
3. [The Three Functions](#the-three-functions)
4. [When Rule of 3 Applies](#when-rule-of-3-applies)
5. [Deep Copy vs Shallow Copy](#deep-copy-vs-shallow-copy)
6. [Destructor](#destructor)
7. [Copy Constructor](#copy-constructor)
8. [Copy Assignment Operator](#copy-assignment-operator)
9. [Complete Example](#complete-example)
10. [What Happens Internally](#what-happens-internally)
11. [Common Problems Without Rule of 3](#common-problems-without-rule-of-3)
12. [Real-Time Examples](#real-time-examples)
13. [Rule of 3 vs Rule of 5](#rule-of-3-vs-rule-of-5)
14. [Rule of 0](#rule-of-0)
15. [Advantages and Disadvantages](#advantages-and-disadvantages)
16. [Interview Questions](#interview-questions)
17. [Quick Revision](#quick-revision)
18. [Conclusion](#conclusion)

---

# Introduction

The **Rule of 3** states:

> If a class requires a custom **Destructor**, **Copy Constructor**, or **Copy Assignment Operator**, it usually requires all three.

This rule is important when a class manages resources such as:

```text
Heap Memory
File Handles
Sockets
Mutexes
Buffers
Hardware Resources
```

---

# Why Rule of 3 Exists

Consider:

```cpp
class Buffer
{
private:
    int* data;

public:
    Buffer()
    {
        data = new int[100];
    }

    ~Buffer()
    {
        delete[] data;
    }
};
```

Looks correct.

But:

```cpp
Buffer b1;

Buffer b2 = b1;
```

Compiler generates a default copy constructor.

Result:

```text
b1.data ----+
            |
            +----> Same Memory
            |
b2.data ----+
```

Both objects point to the same memory.

---

When destructors run:

```text
delete[] data;
delete[] data;
```

Result:

```text
Double Free
Program Crash
Undefined Behavior
```

---

# The Three Functions

Rule of 3 consists of:

| Function                 | Purpose           |
| ------------------------ | ----------------- |
| Destructor               | Release Resources |
| Copy Constructor         | Create Deep Copy  |
| Copy Assignment Operator | Assign Deep Copy  |

---

# When Rule of 3 Applies

Use Rule of 3 when class owns:

```cpp
new/delete
malloc/free
File Handles
Socket Handles
Database Connections
Device Drivers
Hardware Resources
```

---

Does NOT apply to:

```cpp
int
float
std::string
std::vector
std::unique_ptr
```

because they already manage resources safely.

---

# Deep Copy vs Shallow Copy

---

## Shallow Copy

Default compiler behavior.

```cpp
Buffer b2 = b1;
```

Copies only pointer value.

```text
b1.data ---> Memory

b2.data ---> Same Memory
```

Dangerous.

---

## Deep Copy

Allocates separate memory.

```text
b1.data ---> Memory1

b2.data ---> Memory2
```

Safe.

---

# Destructor

Responsible for releasing resources.

---

## Syntax

```cpp
~ClassName()
{
}
```

---

Example

```cpp
~Buffer()
{
    delete[] data;
}
```

---

## What Happens When Code Hits This?

```cpp
Buffer obj;
```

Leaving scope:

```cpp
}
```

Execution:

```text
1. Destructor Called

2. delete[] data

3. Memory Released
```

---

# Copy Constructor

Creates a new object from an existing object.

---

## Syntax

```cpp
ClassName(const ClassName& obj);
```

---

Example

```cpp
Buffer(const Buffer& obj)
{
    data = new int[100];

    std::copy(
        obj.data,
        obj.data + 100,
        data
    );
}
```

---

## What Happens When Code Hits This?

```cpp
Buffer b2 = b1;
```

Execution:

```text
1. Copy Constructor Called

2. Allocate New Memory

3. Copy Data

4. Separate Ownership
```

---

Memory Layout:

```text
b1.data ---> Memory1

b2.data ---> Memory2
```

---

# Copy Assignment Operator

Used when assigning existing objects.

---

## Syntax

```cpp
ClassName&
operator=(const ClassName& obj);
```

---

Example

```cpp
Buffer&
operator=(const Buffer& obj)
{
    if(this != &obj)
    {
        delete[] data;

        data = new int[100];

        std::copy(
            obj.data,
            obj.data + 100,
            data
        );
    }

    return *this;
}
```

---

## What Happens When Code Hits This?

```cpp
b2 = b1;
```

Execution:

```text
1. Check Self Assignment

2. Release Old Memory

3. Allocate New Memory

4. Copy Data

5. Return *this
```

---

# Complete Example

```cpp
#include <iostream>
#include <algorithm>

class Buffer
{
private:
    int* data;
    int size;

public:

    Buffer(int s)
    {
        size = s;
        data = new int[size];
    }

    ~Buffer()
    {
        delete[] data;
    }

    Buffer(const Buffer& other)
    {
        size = other.size;

        data = new int[size];

        std::copy(
            other.data,
            other.data + size,
            data
        );
    }

    Buffer& operator=(const Buffer& other)
    {
        if(this != &other)
        {
            delete[] data;

            size = other.size;

            data = new int[size];

            std::copy(
                other.data,
                other.data + size,
                data
            );
        }

        return *this;
    }
};
```

---

# What Happens Internally

Example:

```cpp
Buffer b1(100);

Buffer b2 = b1;
```

---

Step 1

```text
b1.data ---> Memory1
```

---

Step 2

Copy Constructor Called

```text
Allocate Memory2
```

---

Step 3

```text
Copy Memory1 → Memory2
```

---

Step 4

```text
b1.data ---> Memory1

b2.data ---> Memory2
```

Independent ownership.

---

# Common Problems Without Rule of 3

## Double Free

```cpp
delete memory twice
```

Result:

```text
Crash
```

---

## Dangling Pointer

```cpp
Pointer references freed memory
```

Result:

```text
Undefined Behavior
```

---

## Memory Corruption

```cpp
Two objects modify same memory
```

Result:

```text
Random Bugs
```

---

# Real-Time Examples

## Example 1: Device Driver Buffer

```cpp
class DMA_Buffer
{
    uint8_t* buffer;
};
```

Needs:

* Destructor
* Copy Constructor
* Assignment Operator

to avoid double-free.

---

## Example 2: File Handler

```cpp
class File
{
    FILE* fp;
};
```

Must manage ownership carefully.

---

## Example 3: Socket Wrapper

```cpp
class Socket
{
    int fd;
};
```

Copying file descriptors incorrectly can cause resource issues.

---

## Example 4: Embedded Linux

Used in:

```text
Camera Buffers
Network Packets
Sensor Data
DMA Buffers
Shared Memory
```

---

# Rule of 3 vs Rule of 5

---

## Rule of 3 (C++03)

Includes:

```cpp
Destructor
Copy Constructor
Copy Assignment Operator
```

---

## Rule of 5 (C++11)

Adds:

```cpp
Move Constructor
Move Assignment Operator
```

Total:

```cpp
Destructor
Copy Constructor
Copy Assignment
Move Constructor
Move Assignment
```

---

Comparison:

| Rule of 3    | Rule of 5           |
| ------------ | ------------------- |
| C++03        | C++11               |
| Copy Support | Copy + Move Support |
| Older Style  | Modern Style        |

---

# Rule of 0

Modern recommendation.

Instead of writing:

```cpp
new
delete
```

Use:

```cpp
std::vector
std::string
std::unique_ptr
```

Then compiler-generated functions are sufficient.

Example:

```cpp
class Data
{
private:
    std::vector<int> values;
};
```

No destructor needed.

No copy constructor needed.

No assignment operator needed.

---

# Advantages and Disadvantages

## Advantages

✔ Prevents Double Free

✔ Prevents Memory Corruption

✔ Safe Resource Ownership

✔ Proper Deep Copy

✔ Reliable Object Behavior

---

## Disadvantages

✘ More Code

✘ Easy to Make Mistakes

✘ Manual Resource Management

✘ Less Efficient Than Move Semantics

---

# Interview Questions

## What is Rule of 3?

If a class defines a custom destructor, copy constructor, or copy assignment operator, it usually needs all three.

---

## Why Was Rule of 3 Introduced?

To safely manage resources and avoid shallow-copy problems.

---

## What Happens When Code Hits This?

```cpp
Buffer b2 = b1;
```

### Answer

```text
Copy Constructor Called

Allocate New Memory

Copy Data

Create Independent Resource Ownership
```

---

## What Problem Does Rule of 3 Solve?

```text
Double Free
Dangling Pointers
Memory Corruption
Resource Leaks
```

---

## Difference Between Copy Constructor and Assignment Operator?

| Copy Constructor   | Assignment Operator     |
| ------------------ | ----------------------- |
| Creates New Object | Assigns Existing Object |
| Buffer b2 = b1;    | b2 = b1;                |

---

## What is Deep Copy?

Allocating separate memory and copying actual data.

---

## What is Shallow Copy?

Copying only pointer values, resulting in shared ownership.

---

## Why Check Self-Assignment?

```cpp
if(this != &other)
```

Prevents deleting your own data during assignment.

---

## What Replaced Rule of 3 in Modern C++?

```text
Rule of 5
Rule of 0
```

---

# Most Asked Interview Question

## Explain Rule of 3 with Real Example.

Rule of 3 states that if a class manages resources and defines a destructor, copy constructor, or copy assignment operator, it should typically define all three. For example, a class managing dynamically allocated memory must ensure deep copies are made during copying and assignment, while properly releasing memory in the destructor. Without Rule of 3, multiple objects may share the same resource, causing double-free errors, dangling pointers, and memory corruption.

---

# Interview Answer (2-Minute Version)

The Rule of 3 is a C++ resource management guideline stating that if a class requires a custom destructor, copy constructor, or copy assignment operator, it usually requires all three. This is necessary because classes that manage resources such as heap memory, files, sockets, or hardware buffers must implement deep-copy behavior and proper cleanup. Without Rule of 3, default shallow copies can lead to double-free errors, dangling pointers, and resource corruption. In modern C++, Rule of 3 evolved into Rule of 5 with move semantics, and Rule of 0 is preferred whenever standard library containers and smart pointers can manage resources automatically.

---

# Quick Revision

```text
Rule of 3

Includes:
1. Destructor
2. Copy Constructor
3. Copy Assignment Operator

Purpose:
Safe Resource Management

Prevents:
✔ Double Free
✔ Dangling Pointer
✔ Memory Corruption

Applies To:
✔ Heap Memory
✔ File Handles
✔ Sockets
✔ DMA Buffers
✔ Hardware Resources

Modern Evolution:
Rule of 3 → Rule of 5 → Rule of 0
```

---

# Conclusion

The Rule of 3 is a fundamental C++ concept for safe resource management. It ensures that classes owning resources implement proper cleanup, copying, and assignment behavior to avoid shallow-copy bugs. Although modern C++ encourages Rule of 5 and Rule of 0 through move semantics and smart pointers, understanding Rule of 3 remains essential for interviews, legacy codebases, embedded systems, device drivers, and low-level software development.
