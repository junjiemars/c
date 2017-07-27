# Memory

## Bits and Bytes

### Bits

The smallest unit of memory is the *bi*. A bit can be in one of two states
-- *on* vs. *off*, or alternately, *1* vs. *0*.

Most computers don't work with bits individually, but instead group eight 
bits together to form a *byte*. Eash byte maintains one eight-bit pattern.
A group of N bits can be arranged in 2^N different patterns.

Strictly speaking, a program can interpret a bit pattern any way it chooses.

### Bytes

The byte is sometimes defined as the *smallest addressable unit* of memory.
Most computers also support reading and writting larger units of memory-- 2bytes *half-words* (sometimes known as a *short* word) and 4 byte *word*.

Most computers restrict half-word and word accesses to be *aligned*-- 


## Allocation


### malloc
> don't cast the result of malloc
> It is unneccessary, as ```void *``` is automatically and safely prompted to any
other pointer type in this case.
> It adds clutter to the code, casts are not very easy to read (especially if the
pointer type is long).
> It makes you repeat yourself, which is generally bad.
> It can hide an error, if you forgot to include ```<stdlib.h>```. This can crashes 
(or, worse, not cause a crash until way later in some totally different part of the
code). Consider what happens if pointers and integers are differently sized; then
you're hiding a warning by casting and might lose bits of your returned address. 
Note: as of C11 implicit functions are gone from C, and this point is no longer 
relevant since there's no automatic assumption that undeclared functions return 
```int```

> To add further, your code needlessly repeats the type information (```int```) which
can cause errors. It's better to dereference the pointer being used to store the 
return value, to __lock__ the two together:
> ```int *x = malloc(length * sizeof *x);```
> This also moves the ```lengh``` to the front for increased visibility, and drops
the redundant parentheses with ```sizeof()```; they are only needed when the argument 
is a type name. Many people seem to not know or ignore this, which makes their code
move verbose. Remember: ```sizeof``` is not a function!

> While moving length to the front may increase visibility in some
rare cases, one should also pay attention that in the general case, 
it should be better to write the expression as:
```int *x = malloc(sizeof *x * length);```

> Compare with ```malloc(sizeof *x * length * width)``` vs. 
```malloc(length * width * sizeof *x)``` the second may overflow the 
```length * width``` when ```length``` and ```width``` are smaller types than 
```size_t```.

### free

## References
* [Programming Paradigms](https://see.stanford.edu/Course/CS107)
* [Do I cast the result of malloc](https://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc)
