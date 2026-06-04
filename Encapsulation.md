# Encapsulation in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is Encapsulation?](#what-is-encapsulation)
3. [Why do we use Encapsulation?](#why-do-we-use-encapsulation)
4. [Real-Time Example](#real-time-example)
5. [How Encapsulation Works](#how-encapsulation-works)
6. [Data Hiding](#data-hiding)
7. [Access Specifiers](#access-specifiers)
8. [Getter and Setter Methods](#getter-and-setter-methods)
9. [Encapsulation vs Abstraction](#encapsulation-vs-abstraction)
10. [How Encapsulation Works Internally](#how-encapsulation-works-internally)
11. [Encapsulation in Embedded Systems](#encapsulation-in-embedded-systems)
12. [Advantages and Disadvantages](#advantages-and-disadvantages)
13. [Interview Questions](#interview-questions)
14. [Conclusion](#conclusion)

---

# Introduction

Encapsulation is one of the four pillars of Object-Oriented Programming (OOP).

```text
1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism
```

Encapsulation is the foundation of secure and maintainable software design.

---

# What is Encapsulation?

### Definition

> Encapsulation is the process of binding data (variables) and methods (functions) into a single unit and restricting direct access to the data.

---

## Simple Meaning

```text
Data + Functions
       ↓
Single Unit (Class)
       ↓
Controlled Access
```

---

## Key Idea

```text
Hide Data
Protect Data
Control Data Access
```

---

# Why do we use Encapsulation?

✔ Data Protection

✔ Data Hiding

✔ Improved Security

✔ Better Maintainability

✔ Controlled Access

✔ Easier Debugging

✔ Modular Design

---

# Real-Time Example

## ATM Machine

You can:

```text
✔ Withdraw Money
✔ Deposit Money
✔ Check Balance
```

---

You cannot directly access:

```text
✘ Bank Database
✘ Account Memory
✘ Internal Transactions
```

---

This is Encapsulation.

The data is protected and can only be accessed through approved operations.

---

# How Encapsulation Works

Encapsulation combines:

```text
Data Members
+
Member Functions
```

into a single class.

---

## Example

```cpp
class BankAccount
{
private:
    int balance;

public:
    void deposit(int amount)
    {
        balance += amount;
    }

    int getBalance()
    {
        return balance;
    }
};
```

---

## User Access

```cpp
BankAccount acc;

acc.deposit(1000);
```

Allowed.

---

```cpp
acc.balance = 1000;
```

Not Allowed.

---

# Data Hiding

Data hiding is a major benefit of encapsulation.

---

## Example

```cpp
class Employee
{
private:
    int salary;
};
```

---

Attempting:

```cpp
Employee emp;

emp.salary = 50000;
```

---

Compiler Error:

```text
salary is private
```

---

## Why?

The class owner controls how data is modified.

---

# Access Specifiers

Encapsulation is implemented using access specifiers.

---

# 1. Private

Accessible only inside the class.

```cpp
private:
    int balance;
```

---

## Access

| Location      | Accessible |
| ------------- | ---------- |
| Same Class    | Yes        |
| Derived Class | No         |
| Outside Class | No         |

---

# 2. Protected

Accessible inside class and derived classes.

```cpp
protected:
    int speed;
```

---

## Access

| Location      | Accessible |
| ------------- | ---------- |
| Same Class    | Yes        |
| Derived Class | Yes        |
| Outside Class | No         |

---

# 3. Public

Accessible everywhere.

```cpp
public:
    void deposit();
```

---

## Access

| Location      | Accessible |
| ------------- | ---------- |
| Same Class    | Yes        |
| Derived Class | Yes        |
| Outside Class | Yes        |

---

# Getter and Setter Methods

Most common encapsulation technique.

---

## Example

```cpp
class Student
{
private:
    int marks;

public:

    void setMarks(int m)
    {
        marks = m;
    }

    int getMarks()
    {
        return marks;
    }
};
```

---

## Usage

```cpp
Student s;

s.setMarks(95);

cout << s.getMarks();
```

---

## Why Use Getters and Setters?

Allows validation.

---

Example:

```cpp
void setMarks(int m)
{
    if(m >= 0 && m <= 100)
    {
        marks = m;
    }
}
```

---

Benefit:

```text
Invalid Data Rejected
```

---

# Encapsulation vs Abstraction

Most Asked Interview Question

| Encapsulation                    | Abstraction                     |
| -------------------------------- | ------------------------------- |
| Hides Data                       | Hides Implementation            |
| Achieved using Access Specifiers | Achieved using Abstract Classes |
| Focuses on Security              | Focuses on Simplicity           |
| Internal Protection              | External Interface              |

---

## Example

### Encapsulation

```cpp
private:
    int balance;
```

Protecting data.

---

### Abstraction

```cpp
withdraw();
```

Hiding internal working.

---

# How Encapsulation Works Internally

## Example

```cpp
Student s;

s.setMarks(95);
```

---

## Internal Flow

```text
1. Object Created
2. Function Called
3. Validation Performed
4. Data Updated
```

---

## What Happens When Code Hits This?

```cpp
s.setMarks(95);
```

### Internally

```text
1. Address of object found
2. setMarks() called
3. Input validated
4. marks updated
5. Control returns
```

---

# Encapsulation in Embedded Systems

Encapsulation is heavily used in embedded software.

---

# 1. GPIO Driver

```cpp
class GPIO
{
private:
    uint32_t pinNumber;

public:
    void setPin();
};
```

---

User cannot modify:

```cpp
pinNumber
```

directly.

---

# 2. UART Driver

```cpp
class UART
{
private:
    int baudRate;

public:
    void send();
};
```

---

Baud rate protected from accidental modification.

---

# 3. Sensor Drivers

```cpp
class Sensor
{
private:
    float calibrationFactor;
};
```

---

Calibration data protected.

---

# 4. Automotive Systems

Used in:

* AUTOSAR Components
* ECU Services
* CAN Drivers
* Diagnostics
* ADAS Modules

---

# 5. Embedded Linux

Used in:

* Device Drivers
* Middleware
* Framework Design

---

# Advantages and Disadvantages

## Advantages

✔ Data Security

✔ Data Integrity

✔ Controlled Access

✔ Improved Maintainability

✔ Easy Validation

✔ Better Modularity

✔ Reduced Bugs

---

## Disadvantages

✘ More Boilerplate Code

✘ Slightly Larger Classes

✘ Additional Function Calls

✘ Can Increase Complexity

---

# Interview Questions

## What is Encapsulation?

Encapsulation is the process of combining data and functions into a single unit and restricting direct access to the data.

---

## Why is Encapsulation Used?

To protect data and provide controlled access.

---

## How is Encapsulation Achieved?

Using:

```text
Classes
+
Access Specifiers
```

---

## What is Data Hiding?

Restricting direct access to internal data using private or protected members.

---

## What are Getters and Setters?

Functions used to read and modify private data safely.

---

## What Happens When Code Hits This?

```cpp
s.setMarks(95);
```

### Answer

```text
1. Function called
2. Validation performed
3. Private data updated
4. Function returns
```

---

## Difference Between Encapsulation and Abstraction?

```text
Encapsulation:
Hides Data

Abstraction:
Hides Implementation
```

---

## Why is Encapsulation Important in Embedded Systems?

Encapsulation protects hardware configuration data, prevents accidental modification, and provides controlled access to peripherals and drivers.

---

# Most Asked Interview Question

## Explain Encapsulation with a Real-Time Example.

Encapsulation is the process of combining data and functions into a single unit while restricting direct access to the data. For example, in a UART driver, the baud rate can be declared as a private member and accessed only through public methods such as `setBaudRate()` and `getBaudRate()`. This prevents accidental modification of critical configuration parameters and ensures that all updates pass through validation logic. Encapsulation improves security, reliability, and maintainability.

---

# Interview Answer (2-Minute Version)

Encapsulation is an OOP principle that binds data and methods together in a class while restricting direct access to internal data. It is achieved using access specifiers such as private, protected, and public. Encapsulation protects data from unauthorized access and allows validation through getter and setter methods. In embedded systems, encapsulation is commonly used in drivers, HAL layers, sensor interfaces, and automotive software to safeguard hardware configurations and improve software reliability.

---

# Quick Revision

```text
Encapsulation
      ↓
Data + Functions
      ↓
Single Unit (Class)

Purpose:
✔ Data Protection
✔ Data Hiding
✔ Controlled Access

Achieved Using:
✔ Classes
✔ private
✔ protected
✔ public

Common Technique:
✔ Getters
✔ Setters

Difference:
Encapsulation → Hides Data
Abstraction → Hides Implementation

Used In:
- Drivers
- HAL
- Sensors
- AUTOSAR
- Embedded Linux
```

---

# Conclusion

Encapsulation is a core OOP concept that protects data by restricting direct access and enforcing controlled interactions through methods. It improves security, maintainability, and reliability, making it essential for modern software development. In embedded systems, encapsulation is widely used to protect hardware configurations, peripheral settings, and sensor data, making it a frequently asked topic in technical interviews.
