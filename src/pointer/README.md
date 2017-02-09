# Pointer

## Pointer and Array

## sizeof Pointer
Depends on compiler and machine

## Address of and Dereference 
The ```*``` has two distinct meanings within C in relation to pointers, depending on 
where it's used. When used within a **variable declaration**, the value on the right 
hand side of the equals side should be a **pointer value** to an **address** in
memory. When used with an already **declared variable**, the ```*``` will 
**deference** the pointer value, following it to the pointer-to place in memory, and
allowing the value stored there to be assigned or retrived.


## const and Pointer

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


## References
* [printf size_t](http://stackoverflow.com/questions/2524611/how-can-one-print-a-size-t-variable-portably-using-the-printf-family)
* [Pointers](http://stackoverflow.com/documentation/c/1108/pointers#t=201702060822544818513)
