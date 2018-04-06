# IO

* [Stream](#stream)
  * [Predefined Streams](#predefined-streams)
  * [Redirection](#redirection)
* [Buffered vs. Unbuffered](#buffered-vs.-unbuffered)
* [ASCII vs. Binary](#ascii-vs.-binary)


## Stream

> Streams are a portable way of reading and writing data. They 
provide a flexible and efficient means of I/O.

> A Stream is a file or a physical device (e.g. printer or monitor) 
which is manipulated with a __pointer__ to the stream.

> There exists an internal C data structure, __FILE__, which represents
all streams and is defined in ```stdio.h```. 

> Stream I/O is __BUFFERED__: That is to say a fixed __chunk__ is read
from or written to a file via some temporary storage area (the buffer).

### Predefined Streams

There are ```stdin```, ```stdout```, and ```stderr``` predefined 
streams.

### Redirection

* ```>```: redirect ```stdout``` to a file;
* ```<```: redirect ```stdin``` from a file to a program;
* ```|```: puts ```stdout``` from one program to ```stdin``` of another.


## Buffered vs. Unbuffered

All ```stdio.h``` functions for reading from ```FILE``` may exhibit 
either __buffered__ or __unbuffered__ behavior, and either __echoing__ 
or __non-echoing__ behavior.

The standard library function ```setvbuf``` can be used to enable or 
disable buffering of IO by the C library. There are three possible 
modes: __block buffered__, __line_buffered__, and __unbuffered__.


### Buffered

Buffered output streams will accumulate write result into immediate
buffer, sending it to the OS file system only when enough data has
accumulated (or ```flush()``` is requested). 

C RTL buffers, OS buffers, Disk buffers.

The function ```fflush()``` forces a write of all buffered data for the
given output or update stream via the stream's underlying write function.
The open status of the steam is unaffected.

The function ```fpurge()``` erases any input or output buffered in the
given steam. For output streams this discards any unwritten output. 
For input streams this discards any input read from the underlying object 
but not yet obtained via ```getc()```; this includes any text pushed back 
via ```ungetc()```



### Unbuffered

Unbuffered output has nothing to do with ensuring your data reaches the disk,
that functionality is provided by ```flush()```, and works on both buffered
and unbuffered steams. Unbuffered IO writes don't gurantee the data has
reached the physical disk.

 ```close()``` will call ```flush()```.

The ```open``` system call is used for opening an unbuffered file. 


## ASCII vs. Binary

### ASCII

Terminals, keyboards, and printers deal with character data. When you want 
to write a number like ```1234``` to the screen, it must be converted to 
four characters ```{'1', '2', '3', '4'}``` and written. Similarly, when you 
read a number from the keyboard, the data must be converted from characters 
to integers. This is done by the ```sscanf``` routine.

### Binary

Binary files require no conversion. They also generally take up less space 
than ASCII files. The drawback is that they cannot be directly printed on 
a terminal or printer.


## References
* [ASCII](https://en.wikipedia.org/wiki/ASCII)
* [Buffered and Unbuffered inputs in C](https://stackoverflow.com/questions/20342772/buffered-and-unbuffered-inputs-in-c)
* [Input and Output:stdio.h](https://users.cs.cf.ac.uk/Dave.Marshall/C/node18.html)
* [printf format string](https://en.wikipedia.org/wiki/Printf_format_string)
