# Pointer

## Pointer and Array

## sizeof Pointer
Depends on compiler and machine

## const Pointer

### Pointer to const object
```c
int v = 0x11223344;
const int* p = &v;
*p = (*p)+10; /* error: l-value specifies const object */
*(int**)&p = (*p)+10; /* skipt, dangerous */
```

### const Point to object
```c
int v1=0x11223344, v2=0x44332211;
int* const p = &v1;
p = v2; /* error: l-value specifies const object */
**(const int**)&p = (*p)+10; /* skipt, dangerous */
```

### const Point to const object
```c
int v1=0x11223344, v2=0x44332211;
const int* const p = &v1;
*(int**)&p = &v2;
**(int**)&p = v2;
```

## References
* [Pointers](http://stackoverflow.com/documentation/c/1108/pointers#t=201702060822544818513)
