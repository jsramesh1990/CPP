# Constructors in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Constructor?](#what-is-a-constructor)
3. [Why do we use Constructors?](#why-do-we-use-constructors)
4. [Characteristics of Constructors](#characteristics-of-constructors)
5. [How Constructors Work Internally](#how-constructors-work-internally)
6. [Syntax](#syntax)
7. [Types of Constructors](#types-of-constructors)

   * [Default Constructor](#default-constructor)
   * [Parameterized Constructor](#parameterized-constructor)
   * [Copy Constructor](#copy-constructor)
   * [Move Constructor (C++11)](#move-constructor-c11)
8. [Constructor Overloading](#constructor-overloading)
9. [Constructor Initialization List](#constructor-initialization-list)
10. [Constructor Call Order](#constructor-call-order)
11. [Constructors in Embedded Systems](#constructors-in-embedded-systems)
12. [Advantages and Disadvantages](#advantages-and-disadvantages)
13. [Interview Questions](#interview-questions)
14. [Conclusion](#conclusion)

---

# Introduction

When an object is created, it often needs initial values before being used.

For example:

* UART needs baud rate
* GPIO needs pin number
* Sensor needs configuration

Constructors are used to initialize objects automatically.

---

# What is a Constructor?

### Definition

> A constructor is a special member function of a class that is automatically called when an object is created.

---

## Simple Meaning

```text
Constructor = Object Initialization Function
```

It prepares the object for use.

---

# Why do we use Constructors?

✔ Automatic initialization

✔ Avoid uninitialized variables

✔ Simplify object creation

✔ Improve code reliability

✔ Resource allocation

---

## Without Constructor

```cpp
class UART
{
public:
    int baudRate;
};

UART uart1;

uart1.baudRate = 115200;
```

---

## With Constructor

```cpp
class UART
{
public:
    int baudRate;

    UART()
    {
        baudRate = 115200;
    }
};
```

Object is automatically initialized.

---

# Characteristics of Constructors

### Rules

✔ Name must be same as class name

✔ No return type

✔ Called automatically

✔ Can be overloaded

✔ Cannot be static

✔ Can have parameters

---

# How Constructors Work Internally

## Example

```cpp
class Car
{
public:
    Car()
    {
        cout << "Constructor Called";
    }
};

Car c1;
```

---

## What Happens When Code Hits This?

```cpp
Car c1;
```

### Internal Steps

```text
1. Compiler allocates memory for c1
2. Constructor address identified
3. Constructor called automatically
4. Data members initialized
5. Object becomes ready for use
```

---

# Syntax

```cpp
class ClassName
{
public:
    ClassName()
    {
        // Initialization Code
    }
};
```

---

# Types of Constructors

# Default Constructor

### Definition

A constructor with no parameters.

---

## Example

```cpp
class Car
{
public:
    Car()
    {
        cout << "Default Constructor";
    }
};
```

---

## Usage

```cpp
Car c1;
```

---

## What Happens?

```text
Object Created
↓
Default Constructor Called
↓
Initialization Done
```

---

# Parameterized Constructor

### Definition

A constructor that accepts arguments.

---

## Example

```cpp
class Car
{
public:
    int speed;

    Car(int s)
    {
        speed = s;
    }
};
```

---

## Usage

```cpp
Car c1(100);
```

---

## What Happens?

```text
Object Created
↓
Parameter Passed
↓
speed = 100
↓
Object Ready
```

---

# Copy Constructor

### Definition

Creates a new object from an existing object.

---

## Syntax

```cpp
ClassName(const ClassName &obj)
{
}
```

---

## Example

```cpp
class Car
{
public:
    int speed;

    Car(int s)
    {
        speed = s;
    }

    Car(const Car &obj)
    {
        speed = obj.speed;
    }
};
```

---

## Usage

```cpp
Car c1(100);
Car c2 = c1;
```

---

## What Happens?

```text
c1 Created
↓
c2 Created
↓
Copy Constructor Called
↓
speed copied
```

---

# Move Constructor (C++11)

### Definition

Transfers ownership of resources from one object to another.

---

## Syntax

```cpp
ClassName(ClassName &&obj)
{
}
```

---

## Example

```cpp
class Buffer
{
public:
    Buffer(Buffer&& obj)
    {
        // Move resources
    }
};
```

---

## Why Use It?

```text
Copy = Duplicate Data
Move = Transfer Ownership
```

Move is faster.

---

# Constructor Overloading

Multiple constructors in same class.

---

## Example

```cpp
class Car
{
public:
    Car()
    {
    }

    Car(int speed)
    {
    }

    Car(int speed, int gear)
    {
    }
};
```

---

## Benefit

Different ways to create objects.

---

# Constructor Initialization List

Preferred way to initialize members.

---

## Example

```cpp
class Car
{
    int speed;

public:
    Car(int s) : speed(s)
    {
    }
};
```

---

## Why Use It?

✔ Faster

✔ Required for const members

✔ Required for references

---

# Constructor Call Order

## Single Class

```cpp
Car c1;
```

```text
Constructor Called
↓
Object Ready
```

---

## Inheritance

```cpp
class Vehicle {};
class Car : public Vehicle {};
```

---

### Call Order

```text
Base Constructor
↓
Derived Constructor
```

---

# Constructors in Embedded Systems

Constructors are heavily used in embedded C++ projects.

---

## 1. GPIO Driver

```cpp
class GPIO
{
public:
    GPIO(int pin)
    {
        // Configure Pin
    }
};
```

---

## Usage

```cpp
GPIO led(13);
```

---

# 2. UART Driver

```cpp
class UART
{
public:
    UART(int baudRate)
    {
        // Configure UART
    }
};
```

---

# 3. Sensor Drivers

```cpp
class TemperatureSensor
{
public:
    TemperatureSensor()
    {
        // Sensor Init
    }
};
```

---

# 4. Automotive Systems

Used in:

* ECU initialization
* CAN controllers
* ADAS modules
* Diagnostics

---

# Advantages and Disadvantages

## Advantages

✔ Automatic initialization

✔ Cleaner code

✔ Improved reliability

✔ Supports OOP principles

✔ Resource management

---

## Disadvantages

✘ Constructor overhead

✘ Complex constructors reduce readability

✘ Dynamic allocation inside constructors can be risky in embedded systems

---

# Interview Questions

## What is a Constructor?

A constructor is a special member function automatically called when an object is created.

---

## Why is Constructor Used?

To initialize object data automatically.

---

## Can Constructor Have Return Type?

No.

Not even `void`.

---

## Can Constructors Be Overloaded?

Yes.

Multiple constructors can exist with different parameters.

---

## What is Copy Constructor?

A constructor that creates a new object from an existing object.

---

## What is Move Constructor?

A constructor that transfers resources from one object to another without copying.

---

## What Happens When an Object is Created?

```text
1. Memory allocated
2. Constructor called
3. Members initialized
4. Object ready
```

---

## Why Are Constructors Important in Embedded Systems?

Constructors ensure peripherals, drivers, and hardware interfaces are initialized correctly before use.

---

# Most Asked Interview Question

## Explain Constructors with a Real-Time Example.

A constructor is a special member function automatically called when an object is created. It is used to initialize object data and resources. For example, in an embedded UART driver, a constructor can configure the baud rate and communication settings when the UART object is created. This ensures the hardware is properly initialized before any data transmission occurs, improving reliability and reducing initialization errors.

---

# Quick Revision

```text
Constructor = Automatic Initialization Function

Rules:
✔ Same name as class
✔ No return type
✔ Called automatically

Types:
1. Default Constructor
2. Parameterized Constructor
3. Copy Constructor
4. Move Constructor

Used in:
- Drivers
- GPIO
- UART
- Sensors
- Automotive ECUs
```

---

# Conclusion

Constructors are one of the most important features of C++ and form the foundation of object initialization. They ensure that objects are properly configured before use, making code safer, cleaner, and easier to maintain. In embedded systems, constructors are widely used for driver initialization, peripheral configuration, and hardware abstraction, making them a critical interview topic.
