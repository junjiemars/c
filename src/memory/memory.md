# Memory

## malloc
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

> Compare with ```malloc(sizeof *x * length * width)``` vs. 
```malloc(length * width * sizeof *x)``` the second may overflow the 
```length * width``` when ```length``` and ```width``` are smaller types than 
```size_t```.

## References
[Do I cast the result of malloc](http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc)
