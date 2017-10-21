# C string

C standard library uses the convertion that strings are _null-terminated_: 
a string of _n_ characters is represented as an array of _n+1_ elements, the last 
of which is a _null(\0)_ character.

* [Null-terminated string](#null-terminated string)
* [References](#references)

## Null-terminated string

A __null-terminated string__ is a character string stored as an array containing 
the characters and terminated with a _null character_ (_'\0'_, call NUL in ASCII).
Alternatvie names are _C string_.

The length of a C string is found by searching for the first NUL byte. This can be
slow as it takes _O(n)_ with respect to the string length. It also means that a 
NUL cannot be inside the string, as the only NUL is the one marking the end.

> At the time C (and the languages that it was derived from) was developed, 
memory was extremely limited, so using only one byte of overhead to store 
the length of a string was attractive. The only popular alternative at that time, 
usually called a "Pascal string" (a more modern term is "length-prefixed"), 
used a leading byte to store the length of the string. This allows the string 
to contain NUL and made finding the length need only one memory access O(1) 
constant time, but limited string length to 255 characters (on a machine 
using 8-bit bytes). C designer __Dennis Ritchie__ chose to follow the 
convention of NUL-termination, already established in BCPL, to avoid the 
limitation on the length of a string and because maintaining the count seemed, 
in his experience, less convenient than using a terminator.


## References
* [Null-terminated string](https://en.wikipedia.org/wiki/Null-terminated_string)
