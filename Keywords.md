````md
# Keywords in C Programming

Keywords are reserved words in C that have predefined meanings and cannot be used as identifiers (variable names, function names, etc.).

## 1. Data Type Keywords

Used to declare data types.

```c
int
char
float
double
void
short
long
signed
unsigned
````

## 2. Storage Class Keywords

Control variable lifetime, scope, and linkage.

```c
auto
register
static
extern
typedef
```

## 3. Control Flow Keywords

Used for decision-making and looping.

```c
if
else
switch
case
default
for
while
do
break
continue
goto
return
```

## 4. Type Qualifier Keywords

Modify how variables can be accessed.

```c
const
volatile
```

## 5. User-Defined Type Keywords

Used to create custom data types.

```c
struct
union
enum
typedef
```

## 6. Special Keywords

Used for specific language features.

```c
sizeof
```

## 7. Modern C Keywords (C99 and Later)

Added in newer C standards.

```c
inline
_Bool
_Complex
_Imaginary
restrict
```

---

# The Original 32 ANSI C Keywords (C89/C90)

```c
auto      break     case      char
const     continue  default   do
double    else      enum      extern
float     for       goto      if
int       long      register  return
short     signed    sizeof    static
struct    switch    typedef   union
unsigned  void      volatile  while
```

## Example Program

```c
#include <stdio.h>

int main() {
    int i;

    for(i = 0; i < 5; i++) {
        if(i == 3)
            break;
    }

    return 0;
}
```

### Keywords Used in the Example

* `int`
* `for`
* `if`
* `break`
* `return`

## Notes

* Keywords are reserved words and cannot be used as identifiers.
* ANSI C (C89/C90) defines 32 keywords.
* Later standards such as C99 and C11 introduced additional keywords.
* Memorizing the 32 ANSI C keywords is useful for exams and interviews.

```
```
