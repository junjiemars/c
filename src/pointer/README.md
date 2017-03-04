# Pointer


## sizeof Pointer
Depends on compiler and machine, all types of pointers on specified machine and 
compiled via specified compiler has same the size, generally occupy one machine word.
```sizeof(size_t)```

## Address of and Dereference 
The ```*``` has two distinct meanings within C in relation to pointers, depending on 
where it's used. When used within a **variable declaration**, the value on the right 
hand side of the equals side should be a **pointer value** to an **address** in
memory. When used with an already **declared variable**, the ```*``` will 
**deference** the pointer value, following it to the pointer-to place in memory, and
allowing the value stored there to be assigned or retrived.


## const and Pointer
Threre is a technique known as the **Clockwise/Spiral Rule** enables any C programmer to parse in their head any C declaration.

![const and pointer](./const-point.png)

### Pointer to const object
```c
int v = 0x11223344;
const int* p = &v;
*p = (*p)+10; /* error: l-value specifies const object */
**(int**)&p = *p+10; /* skip, dangerous */
```

### const Pointer to object
```c
int v1=0x11223344, v2=0x44332211;
int* const p = &v1;
p = &v2; /* error: l-value specifies const object */
*(int**)&p = &v2; /* skip, dangerous */
```

### const Pointer to const object
```c
int v1=0x11223344, v2=0x44332211;
const int* const p = &v1;
*(int**)&p = &v2;
**(int**)&p = v2;
```

### Pointer to Pointer to const object
```c
const int** p;
```

### Pointer to const Pointer to object
```c
int* const* p;
```

### const Pointer to Pointer to object
```c
int** const p;
```

### Pointer to const Pointer to const object
```c
const int* const* p;
```

### const Pointer to Pointer to const object
```c
const int* const* p;
```

### const Pointer to const Pointer to object
```c
int* const* const p;
```

## function Pointer

```c
return_type_of_fn (*fn)(type_of_arg1 arg1, type_of_arg2 arg2 ...);
```

## void Pointer
```void*``` is a catch all type for pointers to object types, via **void** pointer 
can get some ploymorphic behavior. see ```qsort``` in ```stdlib.h```

## volatile pointer


## Dangling Pointer
Pointers that point to invalid addresses are sometimes called dangling pointers.

## Pointer and Array

### Decay
Decay refers to the implicit conversion of an expression from an array type to 
a pointer type. In most contexts, when the compiler sees an array expression it 
converts the type of the expression from **N-element array of T** to 
**const pointer to T** and set the value of the expression to the address of the first element of the array.
The exceptions to this rule are when an array is an operand of either the 
```sizeof``` or ```&``` operators, or the array is a string literal being used as an
initializer in a declaration. More importantly the term decay signifies loss of type 
and dimension.


## References
* [printf size_t](http://stackoverflow.com/questions/2524611/how-can-one-print-a-size-t-variable-portably-using-the-printf-family)
* [Pointers](http://stackoverflow.com/documentation/c/1108/pointers#t=201702060822544818513)
* [What is array decaying?](http://stackoverflow.com/questions/1461432/what-is-array-decaying)
* [The Development of the C Lanuage](https://www.bell-labs.com/usr/dmr/www/chist.html)
* [array](../array/README.md)
* [Clockwise/Spiral Rule](http://c-faq.com/decl/spiral.anderson.html)
