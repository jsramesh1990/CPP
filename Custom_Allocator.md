# Custom Allocator

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Custom Allocator?](#what-is-a-custom-allocator)
3. [Why Do We Need a Custom Allocator?](#why-do-we-need-a-custom-allocator)
4. [How Default Memory Allocation Works](#how-default-memory-allocation-works)
5. [Problems with malloc() and new](#problems-with-malloc-and-new)
6. [How a Custom Allocator Works](#how-a-custom-allocator-works)
7. [Types of Custom Allocators](#types-of-custom-allocators)
8. [Memory Pool Allocator](#memory-pool-allocator)
9. [Stack Allocator](#stack-allocator)
10. [Arena Allocator](#arena-allocator)
11. [Fixed Block Allocator](#fixed-block-allocator)
12. [Custom Allocator Example in C](#custom-allocator-example-in-c)
13. [Custom Allocator Example in C++](#custom-allocator-example-in-cpp)
14. [STL Custom Allocators](#stl-custom-allocators)
15. [What Happens When Code Hits It?](#what-happens-when-code-hits-it)
16. [Real-Time Examples](#real-time-examples)
17. [Custom Allocators in Embedded Systems](#custom-allocators-in-embedded-systems)
18. [Advantages and Disadvantages](#advantages-and-disadvantages)
19. [Interview Questions](#interview-questions)
20. [Quick Revision](#quick-revision)
21. [Conclusion](#conclusion)

---

# Introduction

Normally memory is allocated using:

```c
malloc()
calloc()
realloc()
free()
```

or in C++:

```cpp
new
delete
new[]
delete[]
```

Example:

```cpp
int* ptr = new int;
```

or

```c
int *ptr = malloc(sizeof(int));
```

These use the system's default memory allocator.

Sometimes this is not sufficient.

We create our own allocator called a:

```text
Custom Allocator
```

---

# What is a Custom Allocator?

## Definition

A Custom Allocator is a user-defined memory management mechanism that controls:

```text
Memory Allocation
Memory Deallocation
Memory Reuse
Memory Tracking
```

instead of using the default allocator.

---

Example:

```cpp
MyAllocator alloc;

int* ptr =
alloc.allocate(sizeof(int));
```

---

# Why Do We Need a Custom Allocator?

Default allocators are general-purpose.

They must work for:

```text
Browsers
Games
Servers
Embedded Systems
Operating Systems
```

Because they are generic:

```text
May Be Slow
May Fragment Memory
May Be Non-Deterministic
```

---

Custom allocators provide:

✔ Faster Allocation

✔ Predictable Timing

✔ Reduced Fragmentation

✔ Better Memory Usage

✔ Real-Time Safety

---

# How Default Memory Allocation Works

Example:

```cpp
int* ptr = new int;
```

Internally:

```text
new
 ↓
operator new()
 ↓
malloc()
 ↓
Heap Manager
 ↓
OS Memory
```

---

Many layers are involved.

This introduces overhead.

---

# Problems with malloc() and new

## 1. Fragmentation

```cpp
new int;
new char;
new double;
delete char;
```

Memory becomes fragmented.

---

## 2. Unpredictable Timing

Allocation time varies.

Bad for:

```text
RTOS
Automotive
Medical Devices
```

---

## 3. Heap Exhaustion

```cpp
while(true)
{
    new int;
}
```

Eventually:

```text
Heap Full
```

---

## 4. Allocation Failure

```cpp
new
```

may throw:

```cpp
std::bad_alloc
```

---

# How a Custom Allocator Works

Instead of requesting memory from OS every time:

```text
Preallocate Large Memory Block
            ↓
Manage Internally
            ↓
Give Memory To Users
```

---

Visualization:

```text
Heap

+----------------------+
|      Memory Pool     |
+----------------------+

       ↓

Allocator

       ↓

Objects
```

---

# Types of Custom Allocators

| Allocator             | Use Case             |
| --------------------- | -------------------- |
| Pool Allocator        | Fixed Size Objects   |
| Arena Allocator       | Fast Bulk Allocation |
| Stack Allocator       | LIFO Allocation      |
| Fixed Block Allocator | RTOS                 |
| Slab Allocator        | Linux Kernel         |
| Buddy Allocator       | Operating Systems    |

---

# Memory Pool Allocator

Most popular.

Preallocate memory:

```cpp
char pool[1024];
```

---

Memory:

```text
+----+----+----+----+
|Obj1|Obj2|Obj3|Obj4|
+----+----+----+----+
```

---

Allocation:

```text
Take Next Free Block
```

---

Benefits:

```text
O(1) Allocation
O(1) Deallocation
```

---

# Stack Allocator

Works like stack memory.

---

Allocation:

```text
Push
Push
Push
```

---

Free:

```text
Pop
Pop
Pop
```

---

Rule:

```text
Last Allocated
First Freed
```

(LIFO)

---

# Arena Allocator

Allocate large region:

```text
Arena
```

---

Objects:

```text
Object1
Object2
Object3
Object4
```

---

Free all at once:

```cpp
arena.reset();
```

---

Very fast.

---

# Fixed Block Allocator

Memory split into equal blocks.

Example:

```text
64 bytes
64 bytes
64 bytes
64 bytes
```

---

Good for:

```text
Tasks
Messages
CAN Frames
Buffers
```

---

# Custom Allocator Example in C

Simple Pool Allocator

```c
#include <stdio.h>

#define SIZE 1024

char pool[SIZE];
int offset = 0;

void* my_malloc(size_t size)
{
    if(offset + size > SIZE)
        return NULL;

    void* ptr = &pool[offset];

    offset += size;

    return ptr;
}
```

---

Usage

```c
int* x =
my_malloc(sizeof(int));
```

---

# Custom Allocator Example in C++

```cpp
class PoolAllocator
{
private:
    char memory[1024];
    size_t offset = 0;

public:

    void* allocate(size_t size)
    {
        void* ptr =
            &memory[offset];

        offset += size;

        return ptr;
    }
};
```

---

Usage

```cpp
PoolAllocator pool;

int* ptr =
static_cast<int*>(
    pool.allocate(sizeof(int)));
```

---

# STL Custom Allocators

C++ containers can use custom allocators.

Example:

```cpp
std::vector<int,
            MyAllocator<int>>
vector_data;
```

---

Benefits:

```text
Control Memory
Improve Performance
Track Allocations
```

---

# What Happens When Code Hits It?

Example:

```cpp
PoolAllocator pool;

int* ptr =
static_cast<int*>(
pool.allocate(sizeof(int)));
```

---

Step 1

```text
allocate(4)
```

called.

---

Step 2

Allocator checks:

```text
Enough Space?
```

---

Step 3

Returns address:

```text
memory + offset
```

---

Step 4

Updates:

```text
offset += 4
```

---

Step 5

User receives pointer.

```cpp
*ptr = 100;
```

---

Memory:

```text
Pool Memory

+-----+
|100  |
+-----+
```

---

### Interview Answer

**What happens when code hits a custom allocator?**

The allocator receives a memory request, checks whether free memory is available in its managed memory region, calculates the address of the free block, returns the pointer to the caller, updates its internal bookkeeping information, and avoids calling the operating system or heap manager for every allocation.

---

# Real-Time Examples

## Example 1: Automotive ECU

CAN Messages:

```cpp
CanFrame frame;
```

allocated from:

```text
Memory Pool
```

instead of heap.

Reason:

```text
Deterministic Timing
```

---

## Example 2: RTOS

Task Control Blocks:

```text
TCB
```

allocated from:

```text
Fixed Block Allocator
```

---

## Example 3: Game Engine

Thousands of objects:

```text
Bullets
Particles
Enemies
```

allocated from:

```text
Object Pool
```

---

## Example 4: Network Server

Packet Buffers:

```text
RX Buffers
TX Buffers
```

allocated from:

```text
Memory Pools
```

---

# Custom Allocators in Embedded Systems

Very Important Interview Topic.

---

Why avoid heap?

```text
Heap Fragmentation
Unpredictable Latency
Limited RAM
```

---

Instead:

```text
Static Memory Pool
```

---

Example:

```c
uint8_t uart_pool[4096];
```

Allocator manages:

```text
UART Buffers
DMA Buffers
Sensor Data
```

---

Automotive AUTOSAR systems commonly use:

```text
Memory Pools
Fixed Block Allocators
```

for deterministic behavior.

---

# Advantages and Disadvantages

## Advantages

✔ Faster Allocation

✔ Predictable Execution Time

✔ Reduced Fragmentation

✔ Better Cache Locality

✔ Full Memory Control

✔ Real-Time Safe

---

## Disadvantages

✘ More Complex

✘ Debugging Difficulty

✘ Memory Waste Possible

✘ Application-Specific Design

✘ Maintenance Overhead

---

# Interview Questions

## What is a Custom Allocator?

A custom allocator is a user-defined memory management mechanism that allocates and frees memory without relying entirely on the default heap allocator.

---

## Why Use a Custom Allocator?

To improve performance, reduce fragmentation, and achieve deterministic allocation times.

---

## Why Are Custom Allocators Used in Embedded Systems?

Because dynamic heap allocation may cause fragmentation and unpredictable timing.

---

## What is a Memory Pool Allocator?

A memory pool allocator preallocates a block of memory and serves allocation requests from that block.

---

## Difference Between malloc() and Pool Allocator?

| malloc()               | Pool Allocator        |
| ---------------------- | --------------------- |
| General Purpose        | Application Specific  |
| Slower                 | Faster                |
| Fragmentation Possible | Minimal Fragmentation |
| Non-Deterministic      | Deterministic         |

---

## What Happens When Code Hits It?

The allocator searches for a free block in its managed memory pool, returns the address, updates internal tracking data, and provides memory without invoking the OS allocator.

---

## Which Allocator is Common in RTOS?

```text
Fixed Block Allocator
Memory Pool Allocator
```

---

# Most Asked Interview Question

## Why Are Custom Allocators Preferred in Automotive and Embedded Systems?

Automotive and embedded systems often have strict real-time requirements. Standard heap allocation can cause fragmentation and unpredictable allocation times. Custom allocators such as memory pools and fixed block allocators provide deterministic allocation, faster execution, lower memory overhead, and predictable system behavior, making them suitable for safety-critical applications.

---

# Interview Answer (2-Minute Version)

A custom allocator is a specialized memory management system that replaces or supplements the default heap allocator. It manages a preallocated memory region and provides memory to applications in a controlled manner. Custom allocators improve performance, reduce fragmentation, and provide deterministic allocation times, which are essential in embedded, automotive, RTOS, networking, and game development. Common allocator types include pool allocators, arena allocators, stack allocators, and fixed block allocators. In embedded systems, custom allocators are widely used to avoid heap fragmentation and ensure predictable memory behavior.

---

# Quick Revision

```text
Custom Allocator

Purpose:
Custom Memory Management

Why?
✔ Faster
✔ Deterministic
✔ Less Fragmentation

Types:
1. Pool Allocator
2. Arena Allocator
3. Stack Allocator
4. Fixed Block Allocator
5. Slab Allocator

Flow:

Memory Pool
      ↓
Allocator
      ↓
Object

Embedded Systems:
✔ UART Buffers
✔ CAN Buffers
✔ DMA Buffers
✔ RTOS Tasks

Advantages:
✔ Fast
✔ Predictable
✔ Real-Time Safe

Most Important:
Custom Allocator = Application-Controlled Memory Manager
```

---

# Conclusion

Custom allocators are specialized memory management techniques used to improve performance, reduce memory fragmentation, and provide deterministic behavior. They are heavily used in Embedded Systems, Automotive ECUs, RTOS kernels, Networking, High-Performance Servers, Game Engines, and Linux Kernel development. Understanding custom allocators is essential for advanced C/C++ programming, memory optimization, and technical interviews focused on systems programming and embedded software development.
