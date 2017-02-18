# Assembly Language

Machine languages consist entirely of numbers and are almost impossible for humans to
read and write. Assembly languages have the same structure and set of commands as
machine languages, but they enable a programmer to use names instead of numbers.


## Data Sizes
|            | Size (bytes) | Size (bits) |
|:----------:|-------------:|------------:|
|    Word    |            2 |          16 |
| Doubleword |            4 |          32 |
|  Quadword  |            8 |          64 |
| Paragraph  |           16 |         128 |
| Kilobytes  |         1024 |        8192 |
| Megabyte   |    1,048,576 |     8388608 |


## Memory

### Addressing Data in Memory
The process through which the processor controls the execution of instructions is 
referred as **fetch-decode-execute cycle** or the **execution cycle**. It consists
of three continuous steps:
* fetching the instruction from memory
* decoding or identifying the instruction
* executing the instruction

There are two kinds of memory addresses:
* absolute address: a direct reference of specific location
* segment address (or offset): starting address of a memory segment with the offset 
value

### Memory Segments
A segmented memory model divides the system memory into groups of independent 
segments referenced by pointers located in the segment registers. Each segment is 
used to contain a specific type of data. 
* data segment: it is represented by **.data** section and **.bss**. It is used to 
declare the memory region, where data elements are stored for the program. 
This section cannot be expanded after the data elements are declared, 
and it remains static throughout the program.
* code segment: it is represented by **.text** section. This defines an area in memory
that stores the instruction codes. This is also a fixed area. 
* stack: it contains values passed to functions and procedures within the program.

## Registers

## Registers
![AX Register](ax.png)

### Data Registers

## Stack 


## References
* [Intel and AT&T Syntax](http://www.imada.sdu.dk/Courses/DM18/Litteratur/IntelnATT.htm)
* [Assembly Programming Tutorial](https://www.tutorialspoint.com/assembly_programming/index.htm)
* [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://software.intel.com/en-us/articles/intel-sdm)
