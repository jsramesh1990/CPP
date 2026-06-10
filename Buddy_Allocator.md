# Buddy Allocator

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Buddy Allocator?](#what-is-a-buddy-allocator)
3. [Why Do We Need a Buddy Allocator?](#why-do-we-need-a-buddy-allocator)
4. [Problems with Traditional Allocation](#problems-with-traditional-allocation)
5. [How the Buddy Allocator Works](#how-the-buddy-allocator-works)
6. [Power-of-Two Memory Blocks](#power-of-two-memory-blocks)
7. [Splitting Process](#splitting-process)
8. [Buddy Calculation](#buddy-calculation)
9. [Merging Process](#merging-process)
10. [Memory Layout Example](#memory-layout-example)
11. [Buddy Allocator Algorithm](#buddy-allocator-algorithm)
12. [Implementation Example](#implementation-example)
13. [What Happens When Code Hits It?](#what-happens-when-code-hits-it)
14. [Buddy Allocator in Linux](#buddy-allocator-in-linux)
15. [Buddy Allocator in Embedded Systems](#buddy-allocator-in-embedded-systems)
16. [Advantages and Disadvantages](#advantages-and-disadvantages)
17. [Interview Questions](#interview-questions)
18. [Quick Revision](#quick-revision)
19. [Conclusion](#conclusion)

---

# Introduction

Memory allocators must solve two major problems:

```text
1. Fast Allocation
2. Low Fragmentation
```

Traditional heap allocation often causes:

```text
Memory Fragmentation
Slow Allocation
Complex Management
```

To solve this, operating systems commonly use:

```text
Buddy Allocation
```

---

# What is a Buddy Allocator?

## Definition

A Buddy Allocator is a memory allocation algorithm that manages memory in blocks whose sizes are powers of two.

When memory is requested:

```text
Find Smallest Suitable Block
            ↓
Split Larger Blocks If Needed
            ↓
Return Block
```

When memory is freed:

```text
Find Its Buddy
        ↓
Merge If Free
        ↓
Create Larger Block
```

---

## Simple Definition

> A Buddy Allocator divides memory into power-of-two blocks and merges adjacent free blocks (buddies) when possible.

---

# Why Do We Need a Buddy Allocator?

Suppose memory size:

```text
1024 Bytes
```

Request:

```text
100 Bytes
```

Allocator gives:

```text
128 Bytes
```

(nearest power of 2)

Benefits:

✔ Fast Allocation

✔ Fast Deallocation

✔ Easy Merging

✔ Reduced External Fragmentation

---

# Problems with Traditional Allocation

Example:

```c
malloc(100);
malloc(200);
malloc(300);
```

After freeing:

```text
[Used][Free][Used]
```

Memory becomes fragmented.

---

Problem:

```text
Enough Total Memory Exists
But Not Contiguous
```

This is called:

```text
External Fragmentation
```

---

# How the Buddy Allocator Works

Suppose memory:

```text
1024 Bytes
```

Initially:

```text
+----------------------+
|      1024 Bytes      |
+----------------------+
```

---

Request:

```text
100 Bytes
```

Need:

```text
128 Bytes
```

Allocator splits:

```text
1024
 ↓
512 + 512
 ↓
256 + 256
 ↓
128 + 128
```

Returns one:

```text
128 Byte Block
```

---

# Power-of-Two Memory Blocks

Buddy allocators use:

```text
2^0 = 1
2^1 = 2
2^2 = 4
2^3 = 8
2^4 = 16
2^5 = 32
2^6 = 64
2^7 = 128
2^8 = 256
2^9 = 512
2^10 = 1024
```

---

Example Request

| Request   | Allocated  |
| --------- | ---------- |
| 10 Bytes  | 16 Bytes   |
| 50 Bytes  | 64 Bytes   |
| 100 Bytes | 128 Bytes  |
| 300 Bytes | 512 Bytes  |
| 700 Bytes | 1024 Bytes |

---

# Splitting Process

Initial:

```text
1024
```

Request:

```text
128
```

Split:

```text
1024
├── 512
│
└── 512
     ├── 256
     │
     └── 256
          ├── 128
          └── 128
```

Allocate:

```text
128
```

---

Visualization:

```text
+----+----+--------+--------+
|128 |128 | 256    | 512    |
+----+----+--------+--------+
```

---

# Buddy Calculation

Two blocks are buddies if:

```text
Same Size
Adjacent
Created From Same Split
```

---

Example:

```text
256 Bytes
```

split into:

```text
128 A
128 B
```

Then:

```text
A and B are buddies
```

---

# Merging Process

Suppose:

```text
128 A
128 B
```

both free.

---

Merge:

```text
128 + 128
      ↓
256
```

---

Then:

```text
256 + 256
      ↓
512
```

---

Then:

```text
512 + 512
      ↓
1024
```

---

Memory restored.

---

# Memory Layout Example

Initial:

```text
+----------------------+
|      1024 Bytes      |
+----------------------+
```

---

Allocate:

```text
100 Bytes
```

Result:

```text
+----+----+--------+--------+
|128 |128 | 256    | 512    |
+----+----+--------+--------+
```

One 128-byte block used.

---

Allocate:

```text
200 Bytes
```

Need:

```text
256 Bytes
```

Result:

```text
+----+----+----+----+--------+
|128U|128F|256U|256F|512F    |
+----+----+----+----+--------+
```

---

# Buddy Allocator Algorithm

Allocation:

```text
Request Memory
      ↓
Round Up To Power Of Two
      ↓
Find Free Block
      ↓
Split If Necessary
      ↓
Return Block
```

---

Free:

```text
Free Block
      ↓
Find Buddy
      ↓
Buddy Free?
      ↓
Merge
      ↓
Repeat
```

---

# Implementation Example

Simplified Concept:

```c
struct Block
{
    size_t size;
    int free;
};
```

---

Allocation Logic:

```c
void* buddy_alloc(size_t size)
{
    size = next_power_of_two(size);

    // find suitable block
}
```

---

Free Logic:

```c
void buddy_free(void* ptr)
{
    // find buddy

    // merge if free
}
```

---

Real implementations are more complex.

---

# What Happens When Code Hits It?

Example:

```c
void* ptr =
buddy_alloc(100);
```

---

Step 1

Request:

```text
100 Bytes
```

---

Step 2

Round up:

```text
128 Bytes
```

---

Step 3

Search free list:

```text
128 Available?
```

---

Step 4

No?

Split larger block.

```text
1024
 ↓
512
 ↓
256
 ↓
128
```

---

Step 5

Return:

```text
128 Byte Block
```

---

Memory:

```text
+----+----+--------+--------+
|128U|128F|256F|512F|
+----+----+--------+--------+
```

---

### Interview Answer

**What happens when code hits a buddy allocator?**

The allocator rounds the requested size to the nearest power of two, searches for a free block of that size, and if unavailable, splits a larger block into smaller buddy blocks until the required size is obtained. During deallocation, it checks whether the corresponding buddy block is free and merges them recursively to reduce fragmentation.

---

# Buddy Allocator in Linux

Very Important Interview Topic.

Linux memory management uses:

```text
Buddy Allocator
```

for:

```text
Physical Page Allocation
```

---

Example:

```text
4 KB Pages
```

Allocated using buddy system.

---

Kernel APIs:

```c
alloc_pages()

__get_free_pages()

free_pages()
```

---

Flow:

```text
Buddy Allocator
      ↓
Pages
      ↓
Slab Allocator
      ↓
Kernel Objects
```

---

# Buddy Allocator in Embedded Systems

Used when:

```text
Dynamic Memory Required
Large Buffers Required
RTOS Uses Heap
```

---

Applications:

```text
DMA Buffers
Frame Buffers
Network Buffers
Image Processing
```

---

Less common than:

```text
Pool Allocator
Fixed Block Allocator
```

because of memory overhead.

---

# Advantages and Disadvantages

## Advantages

✔ Fast Allocation

✔ Fast Deallocation

✔ Easy Block Merging

✔ Low External Fragmentation

✔ Widely Used in Operating Systems

---

## Disadvantages

✘ Internal Fragmentation

Example:

```text
Request = 100 Bytes

Allocated = 128 Bytes
```

28 bytes wasted.

---

✘ Memory Waste

✘ More Metadata Required

✘ Complex Implementation

---

# Interview Questions

## What is a Buddy Allocator?

A buddy allocator is a memory management algorithm that allocates memory in power-of-two block sizes and merges adjacent free buddy blocks when memory is released.

---

## Why is it Called Buddy Allocator?

Because every block has a matching adjacent block called its "buddy", and the two can be merged when both are free.

---

## Why Use Powers of Two?

They simplify splitting and merging operations.

---

## What Problem Does Buddy Allocation Solve?

It reduces external fragmentation and enables efficient memory allocation.

---

## Difference Between Internal and External Fragmentation?

| Internal                            | External                  |
| ----------------------------------- | ------------------------- |
| Wasted Space Inside Allocated Block | Free Space Scattered      |
| Buddy Allocator Has Some            | Buddy Allocator Minimizes |

---

## What Happens When Code Hits It?

The allocator rounds the size to a power of two, finds or creates a suitable block by splitting larger blocks, and returns the allocated memory.

---

## Where is Buddy Allocation Used?

```text
Linux Kernel
Operating Systems
Memory Managers
Page Allocation Systems
```

---

# Most Asked Interview Question

## Explain Buddy Allocation with an Example.

Suppose a buddy allocator manages a 1024-byte memory block. If an application requests 100 bytes, the allocator rounds the request to 128 bytes. Since no 128-byte block exists initially, the allocator repeatedly splits larger blocks: 1024 → 512 → 256 → 128. One 128-byte block is returned. When the block is freed, the allocator checks whether its adjacent buddy is also free. If so, both blocks are merged into a 256-byte block. This merging continues recursively, reducing fragmentation and restoring larger free blocks.

---

# Interview Answer (2-Minute Version)

The Buddy Allocator is a memory management algorithm that allocates memory in power-of-two block sizes. When a request arrives, the allocator rounds the size up to the nearest power of two and either finds a matching free block or splits a larger block into smaller buddy blocks. When memory is freed, the allocator checks whether the corresponding buddy block is free and merges them recursively. This approach provides fast allocation, fast deallocation, and low external fragmentation. Linux uses the buddy allocator for physical page allocation, making it one of the most important memory management techniques in operating systems.

---

# Quick Revision

```text
Buddy Allocator

Purpose:
Fast Memory Allocation

Memory Sizes:
1
2
4
8
16
32
64
128
256
512
1024

Allocation:
Request
   ↓
Round To Power Of Two
   ↓
Split Blocks
   ↓
Return Memory

Deallocation:
Free Block
   ↓
Find Buddy
   ↓
Merge
   ↓
Repeat

Linux:
Used For Physical Pages

Advantages:
✔ Fast
✔ Low Fragmentation
✔ Easy Merge

Disadvantage:
Internal Fragmentation

Most Important:
Buddy Allocator =
Power-of-Two Memory Blocks
With Automatic Buddy Merging
```

---

# Conclusion

The Buddy Allocator is a highly efficient memory management algorithm used extensively in operating systems and kernels. By allocating memory in power-of-two blocks and automatically merging adjacent free buddies, it provides fast allocation, efficient memory reuse, and reduced external fragmentation. Understanding the Buddy Allocator is essential for Linux Kernel Development, Operating Systems, Embedded Systems, Memory Management, RTOS Internals, and technical interviews involving advanced memory allocation strategies.
