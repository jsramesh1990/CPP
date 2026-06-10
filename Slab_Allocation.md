# Slab Allocation

## Table of Contents

1. [Introduction](#introduction)
2. [What is Slab Allocation?](#what-is-slab-allocation)
3. [Why Do We Need Slab Allocation?](#why-do-we-need-slab-allocation)
4. [Problems with Traditional malloc()](#problems-with-traditional-malloc)
5. [History of Slab Allocator](#history-of-slab-allocator)
6. [How Slab Allocation Works](#how-slab-allocation-works)
7. [Slab Allocator Components](#slab-allocator-components)
8. [Cache, Slab, and Object Relationship](#cache-slab-and-object-relationship)
9. [Memory Layout](#memory-layout)
10. [Allocation Process](#allocation-process)
11. [Deallocation Process](#deallocation-process)
12. [Linux Kernel Slab Allocator](#linux-kernel-slab-allocator)
13. [SLAB vs SLUB vs SLOB](#slab-vs-slub-vs-slob)
14. [Implementation Example](#implementation-example)
15. [What Happens When Code Hits It?](#what-happens-when-code-hits-it)
16. [Real-Time Examples](#real-time-examples)
17. [Slab Allocation in Embedded Systems](#slab-allocation-in-embedded-systems)
18. [Advantages and Disadvantages](#advantages-and-disadvantages)
19. [Interview Questions](#interview-questions)
20. [Quick Revision](#quick-revision)
21. [Conclusion](#conclusion)

---

# Introduction

Consider a Linux kernel allocating:

```c
task_struct
```

thousands of times.

Traditional allocation:

```c
malloc(sizeof(task_struct));
```

causes:

```text
Heap Fragmentation
Allocation Overhead
Cache Misses
```

To solve this:

```text
Slab Allocator
```

was introduced.

---

# What is Slab Allocation?

## Definition

Slab Allocation is a memory management technique where memory is divided into caches containing pre-initialized objects of the same type.

Instead of:

```text
Allocate Object Every Time
```

we do:

```text
Create Objects Once
      ↓
Keep Them Ready
      ↓
Reuse Them
```

---

## Simple Definition

> A slab allocator stores pre-created objects in memory and reuses them when needed instead of repeatedly allocating and freeing memory.

---

# Why Do We Need Slab Allocation?

Suppose kernel repeatedly creates:

```c
task_struct
inode
file
socket
```

objects.

Without slab allocation:

```text
Allocate
Initialize
Use
Free

Repeat Thousands Of Times
```

Very expensive.

---

Slab allocation provides:

✔ Faster Allocation

✔ Less Fragmentation

✔ Better Cache Usage

✔ Object Reuse

✔ Deterministic Behavior

---

# Problems with Traditional malloc()

Example:

```c
for(int i=0;i<100000;i++)
{
    malloc(sizeof(task_struct));
}
```

Problems:

---

## Fragmentation

```text
Object A
Object B
Object C
```

Free B:

```text
A _ C
```

Memory becomes fragmented.

---

## Initialization Cost

Every allocation requires:

```text
Allocate Memory
Initialize Memory
```

again.

---

## Cache Misses

Objects may be scattered across memory.

---

# History of Slab Allocator

Slab allocator was introduced for:

* Solaris Operating System

and later adopted in:

* Linux Kernel

to improve kernel memory management.

---

# How Slab Allocation Works

Three important concepts:

```text
Cache
Slab
Object
```

---

Relationship:

```text
Cache
  ↓
Slab
  ↓
Objects
```

---

Example:

```text
Cache (task_struct)

     ↓

+--------------------+
|      Slab 1        |
+--------------------+

task1 task2 task3

+--------------------+
|      Slab 2        |
+--------------------+

task4 task5 task6
```

---

Objects are reused.

---

# Slab Allocator Components

## Cache

Stores objects of one type.

Example:

```c
task_struct
```

Cache:

```text
task_cache
```

---

## Slab

A slab is a collection of objects.

Example:

```text
Slab
 ├─ Object 1
 ├─ Object 2
 ├─ Object 3
```

---

## Object

Actual memory returned to application.

Example:

```c
task_struct
```

---

# Cache, Slab, and Object Relationship

Visualization:

```text
Cache

├── Slab A
│     ├── Object
│     ├── Object
│     └── Object
│
├── Slab B
│     ├── Object
│     ├── Object
│     └── Object
│
└── Slab C
      ├── Object
      ├── Object
      └── Object
```

---

# Memory Layout

Traditional Heap

```text
+----+------+---+-----+
|Obj | Obj  |Obj| Obj |
+----+------+---+-----+
```

Fragmented.

---

Slab Layout

```text
+------------------------+
| Object Object Object   |
| Object Object Object   |
| Object Object Object   |
+------------------------+
```

Contiguous.

---

# Allocation Process

Suppose:

```c
task_struct *task;
```

Allocation request:

```text
task_cache
     ↓
Find Free Object
     ↓
Return Pointer
```

---

No heap search required.

---

Flow:

```text
Request Object
      ↓
Check Cache
      ↓
Free Object Available?
      ↓
Return Object
```

---

# Deallocation Process

Traditional:

```c
free(ptr);
```

returns memory to heap.

---

Slab:

```text
Return Object
       ↓
Mark Free
       ↓
Keep In Cache
```

---

Object remains available for reuse.

---

# Linux Kernel Slab Allocator

Kernel frequently allocates:

```text
task_struct
inode
dentry
file
socket
buffer_head
```

---

Example:

```c
kmem_cache_alloc()
```

allocates from slab cache.

---

Free:

```c
kmem_cache_free()
```

returns object to cache.

---

# SLAB vs SLUB vs SLOB

Linux uses multiple allocators.

| Allocator | Purpose                       |
| --------- | ----------------------------- |
| SLAB      | Original Linux Slab Allocator |
| SLUB      | Modern Linux Default          |
| SLOB      | Small Embedded Systems        |

---

## SLAB

```text
Older
Complex
High Metadata
```

---

## SLUB

```text
Simpler
Faster
Default Linux Allocator
```

---

## SLOB

```text
Tiny Memory Footprint
Embedded Systems
```

---

# Implementation Example

Simple Slab Concept

```c
#define MAX_OBJECTS 10

struct Object
{
    int data;
};

struct Object cache[MAX_OBJECTS];

int free_index = 0;
```

---

Allocate

```c
struct Object* alloc_obj()
{
    return &cache[free_index++];
}
```

---

Free

```c
void free_obj(struct Object* obj)
{
}
```

---

Real slab allocators are much more advanced.

---

# What Happens When Code Hits It?

Example:

```c
task =
kmem_cache_alloc(
    task_cache,
    GFP_KERNEL);
```

---

Step 1

Kernel requests:

```text
task_struct
```

---

Step 2

Slab allocator checks:

```text
Free Object Available?
```

---

Step 3

Finds object inside slab.

---

Step 4

Returns pointer.

---

Memory:

```text
Slab

+----+----+----+
|Used|Free|Free|
+----+----+----+
```

---

After allocation:

```text
+----+----+----+
|Used|Used|Free|
+----+----+----+
```

---

### Interview Answer

**What happens when code hits a slab allocator?**

The allocator checks the cache corresponding to the requested object type, locates a free object inside an existing slab, marks it as used, and returns its address. If no free object exists, a new slab is created. Deallocation does not return memory to the heap immediately; instead, the object is marked free and kept for future reuse.

---

# Real-Time Examples

## Example 1: Linux Task Creation

```c
task_struct
```

allocated from:

```text
task_cache
```

---

## Example 2: File Operations

```c
struct file
```

allocated from:

```text
file_cache
```

---

## Example 3: Networking

```c
socket
```

objects allocated from:

```text
socket_cache
```

---

## Example 4: Automotive Linux ECU

Embedded Linux-based ECUs use slab allocators for:

```text
Socket Buffers
Device Structures
Driver Objects
CAN Interfaces
```

---

# Slab Allocation in Embedded Systems

Large embedded Linux systems use:

```text
SLUB
```

allocator.

---

Small RTOS systems usually use:

```text
Memory Pools
Fixed Block Allocators
```

instead.

---

Reason:

```text
Less Memory
Simpler Implementation
```

---

SLOB allocator was designed for:

```text
Low-Memory Embedded Devices
```

---

# Advantages and Disadvantages

## Advantages

✔ Very Fast Allocation

✔ Very Fast Deallocation

✔ Reduced Fragmentation

✔ Object Reuse

✔ Better CPU Cache Performance

✔ Deterministic Behavior

---

## Disadvantages

✘ More Complex

✘ Memory Overhead

✘ Wasted Space for Unused Objects

✘ Best Suited for Fixed Object Types

---

# Interview Questions

## What is Slab Allocation?

A slab allocator manages memory by keeping caches of preallocated objects and reusing them instead of allocating memory repeatedly.

---

## Why is Slab Allocation Faster?

Because objects are already created and available inside caches, reducing allocation and initialization overhead.

---

## What are the Three Main Components?

```text
Cache
Slab
Object
```

---

## Why Does Linux Use Slab Allocation?

To reduce fragmentation and improve performance for frequently allocated kernel objects.

---

## What is the Difference Between Heap Allocation and Slab Allocation?

| Heap                    | Slab                   |
| ----------------------- | ---------------------- |
| General Purpose         | Object Specific        |
| Fragmentation Possible  | Very Low               |
| Slower                  | Faster                 |
| Repeated Initialization | Reuse Existing Objects |

---

## What Happens When Code Hits It?

The allocator searches the cache, finds a free object in a slab, marks it used, and returns the pointer. If no free object exists, it creates a new slab.

---

## What is SLUB?

SLUB is the modern default slab allocator used by the Linux kernel.

---

# Most Asked Interview Question

## Explain Slab Allocation with an Example.

Slab allocation organizes memory into caches containing objects of the same type. For example, the Linux kernel frequently creates `task_struct` objects. Instead of repeatedly calling a general-purpose allocator, the kernel creates slabs containing many `task_struct` objects. When a new task is needed, a free object is taken from the slab cache. When the task is destroyed, the object is returned to the cache for reuse. This improves performance, reduces fragmentation, and increases cache efficiency.

---

# Interview Answer (2-Minute Version)

Slab allocation is a memory management technique that maintains caches of preallocated objects. Each cache stores objects of a specific type, such as tasks, sockets, or file descriptors. Memory is organized into slabs containing multiple objects. When an allocation request arrives, a free object is returned from an existing slab instead of performing a new heap allocation. When the object is freed, it is returned to the cache for reuse. This approach minimizes fragmentation, improves allocation speed, and provides better CPU cache performance. Linux kernels use slab-based allocators such as SLAB, SLUB, and SLOB for efficient memory management.

---

# Quick Revision

```text
Slab Allocation

Purpose:
Reuse Objects

Components:

Cache
  ↓
Slab
  ↓
Object

Allocation:

Request Object
      ↓
Check Cache
      ↓
Return Free Object

Advantages:
✔ Fast
✔ Reusable
✔ Low Fragmentation
✔ Cache Friendly

Linux:
SLAB
SLUB
SLOB

Used For:
✔ task_struct
✔ inode
✔ socket
✔ file

Most Important:
Slab Allocation =
Preallocated Objects
Stored In Caches
For Fast Reuse
```

---

# Conclusion

Slab allocation is a high-performance memory management technique widely used in operating systems, especially the Linux kernel. By maintaining caches of preallocated objects and reusing them, slab allocators significantly reduce fragmentation, improve allocation speed, and enhance CPU cache efficiency. Understanding slab allocation is essential for Linux Kernel Development, Embedded Linux, Device Drivers, Operating Systems, Automotive Linux Platforms, and advanced memory management interviews.
