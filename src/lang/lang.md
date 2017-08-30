# C Language

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


## Type
All C types be represented as binary numbers in memory, the way how to interprete those numbers is what type does.

### Basic types
C provides the four basic arithmetic __type__ specifiers ```char```, ```int```, ```float``` and ```double```, and the __modifiers__ ```signed```, ```unsigned```,
```short``` and ```long```.

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
* [C data types](https://en.wikipedia.org/wiki/C_data_types)
* [printf format string](https://en.wikipedia.org/wiki/Printf_format_string)
