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

## ASCII vs. Binary



## References
* [Input and Output:stdio.h](https://users.cs.cf.ac.uk/Dave.Marshall/C/node18.html)
* [printf format string](https://en.wikipedia.org/wiki/Printf_format_string)
