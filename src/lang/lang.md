# C Language


* [Build and Run](#build-and-run)
* [Assertion](#assertion)
* [Enum](#enum)
* [Error](#error)
* [Function](#function)
* [main Function](#main-function)
* [Macro](#macro)
* [Pointer](#pointer)
* [Scope](#scope)
* [Type](#type)


## Build and Run
* on Unix-like platform:
```sh
./configure --has-lang --with-std=c11
```
* on Windows:
```sh
./configure --has-lang
```

## Assertion

No, there's nothing wrong with ```assert``` as long as  you use it as intended.
* Assert: A failure in the program's logic itself.
* Error Handling: An erroneous input or system state not due to a
bug in the program.

Assertions are primarily intended for use during debugging and are generally
turned off before code is deployed by defining the ```NDEBUG``` macro.

```sh
# erase assertions: simple way
./configure --has-lang --with-std=c11 --without-debug
# or via make
make NDEBUG=1
```

An _assertions_ specifies that a program statisfies certain conditions at 
particular points in its execution. There are three types of assertion:
* Preconditions: specify conditions at the start of a function.
* Postconditions: specify conditions at the end of a function.
* Invaiants: specify conditions over a defined region of a program.


## enum



## Error 

* __fail safe__ pertaining to a system or component that automatically places
itself in a safe operating mode in the event of a failue:
> a traffic light that reverts to blinking red in all directions when normal
operation fails.
* __fail soft__ pertaining to a system or component that continues to provide
partial operational capability in the event of certain failues:
> a traffic light that continues to alternate between red and green if the 
yellow light fails.
A static variable ```errno``` (or data structure ```feraiseexcept```) indicating
the error status of a function call or object. These indicators are __fail soft__.
* __fail hard__ aka fail fast or fail stop. The reaction to a detected fault
is to immediately halt the system.
Termination is __fail hard__.


Error handling is often separated into detection and recovery:
* __detection__: discovering that an error has occurred.
* __recovery__: determining how to handle the error.


### errno

Before C11, ```errno``` was a global variable, with all the inherent disadvantages:
* later system calls overwrote earlier system calls;
* global map of values to error conditions (```ENOMEM```, ```ERANGE```, etc);
* behavior is underspecified in ISO C and POSIX;
* technically ```errno``` is a __modifiable lvalue__ rather than a global variable, so expressions like ```&errno``` may not be well-defined;
* thread-unsafe;

In C11, ```errno``` is thread-local, so it is thread-safe.


### Disadvantages of Function Return Values
* functions that return error indicators cannot use return value 
for other uses;
* checking every function call for an error condition increases code
by 30%-40%;
* impossible for library function to enforce that callers check for 
error condition.

## Function


## main Function

C90 ```main()``` declarations:
```c
int main(void);

int main(int argc, char **argv);

/* samed with above */
int main(int argc, char *argv[]);

/* classicaly, Unix system support a third variant */
int main(int argc, char **argv, char**envp);
```

C99 the value ```return``` from ```main()```:
* the ```int``` return type may not be omitted.
* the ```return``` statement may be omitted, if so and ```main()``` 
finished, there is an implicit ```return 0```.

In arguments:
* ```argc``` > 0
* ```argv[argc]``` == 0
* ```argv[0]``` through to ```argv[argc-1]``` are pointers to string 
whose meaning will be determined by the program.
* ```argv[0]``` will be a string containing the program's name or a null 
string if that is not avaiable.
* ```envp``` is not specified by POSIX but widely supported, ```getenv``` is 
the only one specified by the C standard, the ```putenv``` 
and ```extern char **environ``` are POSIX-specific.


## Macro

### Expression
Expression-type macro will expand to expression, such as the following
macro definition
```c
#define double_v1(x) 2*x
```
Macro call ```double_v1(1+1)*8``` expands to wrong expression ```2*1+1*8```

Use parens to quoted input arguments and final expression:
```c
#define double_v2(x) (2*(x))
```
Now, it expands to ```(2*(1+1))*8```

But, **max** has side-effect that eval the argument twice
```c
#define max(a, b) ((a) > (b) ? (a) : (b))
```
if call it with ```max(a, b++)``` .


### Block
If the macro definition includes ```;``` statatment ending character, we need
to block it.

```c
#define incr(a, b)   \
    (a)++;           \
    (b)++;
```
Call it with
```c
int a=2, b=3;
if (a > b) incr(a, b);
```
just only ```b``` will be incremented. We can block it and convert it to block-type macro
```c
#define incr(a, b) { \
    (a)++;           \
    (b)++;           \
}
```

### Name Clashs
We can use same machinism like Lisp's ```(gensym)``` to rebind the input arguments to new symbols.

### Check Expansion

```c
$ cc -E <source>
```


## Pointer


### sizeof Pointer

Depends on compiler and machine, all types of pointers on specified machine and 
compiled via specified compiler has same the size, generally occupy one machine word.


### Address of and Dereference 

The ```*``` has two distinct meanings within C in relation to pointers, depending on where it's used. When used within a __variable declaration__, the value on the right hand side of the equals side should be a __pointer value__ to an __address__ in memory. When used with an already __declared variable__, the ```*``` will **deference** the pointer value, following it to the pointer-to place in memory, and allowing the value stored there to be assigned or retrived.


### const and Pointer

Threre is a technique known as the __Clockwise/Spiral Rule__ enables any C programmer to parse in their head any C declaration.

* pointer to const object
```c
int v = 0x11223344;
const int* p = &v;
*p = (*p)+10; /* error: l-value specifies const object */
**(int**)&p = *p+10; /* skip, dangerous */
```

* const pointer to object
```c
int v1=0x11223344, v2=0x44332211;
int* const p = &v1;
p = &v2; /* error: l-value specifies const object */
*(int**)&p = &v2; /* skip, dangerous */
```

* const pointer to const object
```c
int v1=0x11223344, v2=0x44332211;
const int* const p = &v1;
*(int**)&p = &v2;
**(int**)&p = v2;
```

* pointer to pointer to const object
```c
const int** p;
```

* pointer to const pointer to object
```c
int* const* p;
```

* const pointer to pointer to object
```c
int** const p;
```

* pointer to const pointer to const object
```c
const int* const* p;
```

* const pointer to pointer to const object
```c
const int* const* p;
```

* const pointer to const pointer to object
```c
int* const* const p;
```

### function Pointer

```c
return_type_of_fn (*fn)(type_of_arg1 arg1, type_of_arg2 arg2 ...);
```

### void Pointer
The ```void*``` is a catch all type for pointers to object types, via __void__ pointer can get some ploymorphic behavior. see ```qsort``` in ```stdlib.h```

### Dangling Pointer

Pointers that point to invalid addresses are sometimes called dangling pointers.

### Pointer and Array

### Decay

Decay refers to the implicit conversion of an expression from an array type to 
a pointer type. In most contexts, when the compiler sees an array expression it 
converts the type of the expression from __N-element array of T__ to __const pointer to T__ and set the value of the expression to the address of the first element of the array.
The exceptions to this rule are when an array is an operand of either 
the ```sizeof``` or ```&``` operators, or the array is a string literal being used as an initializer in a declaration. More importantly the term decay signifies loss of type and dimension.

### volatile Pointer
The ```volatile``` is to tell the compiler not to optimize the reference, so that every read/write does not use the value stored in register but does a real memory access.

```c
volatile int v1;
int *p_v1 = &v1; /* bad */
volatile int *p_v1 = &v1; /* better */
```


## Scope

### Declarations and Definitions
* All declarations with no [linkage](#linkage) are also definitions. Other 
declarations are definitions if they have an initializer.
* A [file scope](#file-scope) variable declaration without the 
[extern](#extern) storage class specifier or initializer is a tentative definition.
* All definitions are declarations but not vice-versa.
* A definition of an identifier is a declaration for that identifier that:
for an object, causes storage to be reserved for that object.
 
## Scope
The scope of a [declaration](#declaration-and-definition) is the part of the code 
where the declaration is seen and can be used. Note that this says nothing about 
whether the object associated to the declaration can be accessed from some other part of the code via another declaration. We uniquely identify an object by its memory: 
the storage for a variable or the function code.

Finally, note that a [declaration](#declaration-and-definition) in a nested scope can hide a declaration in an outer scope; but only if one of two has no 
[linkage](#linkage).


#### Duration
Indicates whether the object associated to the 
[declaration](#declaration-and-definition) persists throughout the program's 
execution or whether it is allocated dynamically when the declaration's scope 
is entered.

#### Linkage
**Linkage** is what determines if multiple declarations of the same object refer to
the same object, or to separate ones. Each declaration can only have one of five 
[storage](#storage) class specifier: 
**static**, **extern**, **auto**, **register** and **typedef**.

**No Linkage**: A declaration with no linkage is associated to an object that
is not shared with any other declaration. All declarations with no linkage
happen at block scope: all block scope declarations without the extern storage
class specifier have no linkage.

**Internal Linkage**: within the compilation unit, all declarations with internal 
linkage for the same identifier refer to the same object.

**External Linkage**: within the whole program, all declarations with external
linkage for the same identifier refer to the same object.


#### Block Scope 
Every variable or function declaration that appears inside a block
(including a function body) has block scope. The scope goes from the declaration to
the end of the innermost block in which the declaration appears. Function parameter
declarations in function definitions (but not in prototypes) also have block scope.
The scope of a parameter declaration therefore includes the parameter declarations
that appears after it.

### Function Scope
**goto** label is a bit special, which are implicitly declared at the place where 
they appears, but they are visible throughout the function, even if they appear 
inside a block.

**function prototype scope** is the scope for function parameters that appears
inside a function prototype. It extends until the end of the prototype. This
scope exists to ensure that function parameters have distinct names.

#### File Scope
All vairables and functions defined ouside functions have [file scope](#file-scope).
They are visible from their [declaration](#declaration-and-definition) until the 
end of the file. Here, the term **file** should be understood as the source file 
being compiled, after all includes have been resolved.


### Storage

#### auto 
This storage class denotes that an identifier has automatic storage duration. This
means once the scope in which the identifier was defined ends, the object denoted
by the identifier is no longer valid.

Since all objects, not living in **global** scope or being declared **static**, have
automatic storage duration by default when defined, this keyword is mostly of 
historical interest and should not be used.

* **auto** can't apply to parameter declarations. It is the default for variable
declared inside a function body, and is in fact a historic leftover 
from C predecessor's B.
* automatic variables includes global_auto_i0/i1, i0/i1;
* uninitialized variables will be set to 0;


#### register 
Hints to the compiler that access to an object should as fast as possible. 
Whether the compiler actually uses the hint is implementation-defined; it may simply
treat it as equivalent to **auto**.

The compiler does make sure that you do not take the address of a vairable with
the register storage class.

The only property that is definitively different for all objects that are declared 
with **register** is that they cannot have their address computed. 
Thereby **register** can be a good tool to ensure centain optimizations:


```c
/* error: address of register variable requested */
register int i4 = 0x10;
int* p = &i4;
sqr(*(&i4));
```

```i4``` that can never alias because no code can pass its address to another 
function where it might be changed unexpectedly.

This property also implies that an array
```c
register int a[5];
```
cannot decay into a pointer to its first element (i.e. turning into ```&a[0]```).
This means that the elements of such an array cannot be accessed and the array itself
cannot be passed to a function.

In fact, the only legal usage of an array declared with a ```register``` storage class
is the ```sizeof``` operator; Any other operator would require the address of the
first element of the array. For that reason, arrays generally should not be declared
with the ```register``` keyword since it makes them useless for anything other than
size computation of the entire array, which can be done just as easily without 
```register``` keyword.

The ```register``` storage class is more appropriate for variables that are defined 
inside a block and are accessed with high frequency.


#### static 

The **static** storge class serves different purposes, depending on the location
of the declaration in the file:
* Confine the identifier to that **translation unit** only (scope=file);
* Save data for use with the next call of a function (scope=block); 
* >=C99, used in function parameters to denote an array is expected to have a 
constant minimum number of elements and a non-null parameter.


#### extern 

**extern** keyword used to declare an object or function that is defined 
elsewhere (and that has **external linkage**). In general, it is used to
declare an object or function to be used in a module that is not the one
in which the corresponding object or function is defined. 


## Type

All C types be represented as binary numbers in memory, the way how to
interprete those numbers is what type does.

### Basic types

C provides the four basic arithmetic __type__ specifiers ```char```, ```int```, ```float``` and ```double```,
and the __modifiers__ ```signed```, ```unsigned```, ```short```
and ```long```.

### Size and pointer difference types

The C language specification include the __typedefs__ ```size_t``` 
and ```ptrdiff_t``` to represent memory-related quantities. Their size 
is defined according to the target processor's arithmetic capabilities, 
not the memory capabilities, such as avaialable address space. Both of 
these types are defined in the ```<stddef.h>``` header.

* ```size_t``` is an unsigned integer type used to represent the size of any 
object in the particular implementation. The ```sizeof``` operator yields
a value of the type ```size_t```. The maximum size of ```size_t``` is provided 
via ```SIZE_MAX```, a macro constant which is defined in the ```<stdint.h>```
header. 

* ```ptrdiff_t``` is a signed integral type used to reprensent the difference 
between pointers. It is only guranteed to be valid against pointers of the
same type;


### Literal suffix

* ```l``` or ```L``` for ```long```, ```123l```, ```3.14L```;
* ```f``` for ```float```, ```2.718f```;

## References
* [array](../array/README.md)
* [Beyond errno Error Handling in C](https://resources.sei.cmu.edu/asset_files/Presentation/2016_017_101_484207.pdf)
* [C data types](https://en.wikipedia.org/wiki/C_data_types)
* [C Language: Storage Classes](http://stackoverflow.com/documentation/c/3597/storage-classes#t=201702091201208256422)
* [C: Scope, Duration & Linkage](http://norswap.com/c_scope_duration_linkage/)
* [Clockwise/Spiral Rule](http://c-faq.com/decl/spiral.anderson.html)
* [How to use assertions in C](https://ptolemy.eecs.berkeley.edu/~johnr/tutorials/assertions.html)
* [http parser](https://github.com/nodejs/http-parser)
* [Pointers](http://stackoverflow.com/documentation/c/1108/pointers#t=201702060822544818513)
* [printf size_t](http://stackoverflow.com/questions/2524611/how-can-one-print-a-size-t-variable-portably-using-the-printf-family)
* [The Development of the C Lanuage](https://www.bell-labs.com/usr/dmr/www/chist.html)
* [What is array decaying?](http://stackoverflow.com/questions/1461432/what-is-array-decaying)
* [What should main() return in C and C++?](https://stackoverflow.com/questions/204476/what-should-main-return-in-c-and-c)

