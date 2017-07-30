# C Array

A C array is formed by laying out all the elements contiguously in memory from low
to high. The array as a whole is referred to by the address of the first element.


The programmer can refer to elements in the array with the simple ```[]``` syntax 
such as ```intArray[1]```. This scheme works by combing the base address of the array 
with the simple arithmetic. Each element takes up a fixed number of bytes known at 
compile-time. So address of the _nth_ element in the array (0-based indexing) will 
be at an offset of ```(n * element_size)``` bytes from the base address of the whole 
array.


## [] Operator
The square bracket syntax ```[]``` deals with this address arithmetic for you, but 
it's useful to know what it's doing. The ```[]``` multiplies the integer index byt 
the element size, adds the resulting offset to the array base address, and finally
deferences the resulting pointer to get to the desired element.


```c
a[3] == *(a + 3);
a+3 == &a[3]; 

a[b] == b[a];
```


The C standard defines the ```[]``` operator as follows:
```a[b] => *(a+b)```, then ```b[a] => *(b+a) => *(a+b)```,
so ```a[b] == b[a]```



In a closely related piece of syntax, adding an integer to a pointer does the same 
offset computation, but leaves the result as a pointer. The square bracket syntax 
dereferences that pointer to access the _nth_ element while the ```+``` syntax just 
computes the pointer to the _nth_ element.

Any ```[]``` expression can be written with the ```+``` syntax instead. We just need 
to add in the pointer dereference. For most purposes, it's easiest and most readable 
to use the ```[]``` syntax. Every once in a while the ```+``` is convenient if you 
needed a pointer to the element instread of the element itself.


## Pointer++



## Passing multidimensional arrays to a function


## Iteration
* row-major order, so load a[0][0] would potentially load a[0][1], but load a[1][0] would generate a second cache fault.

## References
* [The Ins and Outs of C Arrays](https://see.stanford.edu/materials/icsppcs107/07-Arrays-The-Full-Story.pdf)
* [Array](http://stackoverflow.com/documentation/c/322/arrays#t=20170207121645271737)
