# IO

## What

## Buffered
Buffered output streams will accumulate write result into immediate
buffer, sending it to the OS file system only when enough data has
accumulated (or ```flush()``` is requested). 

C RTL buffers, OS buffers, Disk buffers.

## Unbuffered
Unbuffered output has nothing to do with ensuring your data reaches the disk, that functionality is provided by ```flush()```, and 
works on both buffered and unbuffered steams. Unbuffered IO writes don't gurantee the data has reached the physical disk.

 ```close()``` will call ```flush()```.


## References
