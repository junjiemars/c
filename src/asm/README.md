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

![AX Register](ax.png)

### Data Registers
* AX: is the primary **accumulator**, it is used in input/output and most arithmetic 
instructions.
* BX: is known as the **base** register, as it could be used in indexed addressing. 
* CX: is known as the **counter** register, store the loop count in iterative 
operations.
* DX: is known as the **data** register, it is also used in input/output operations.
And also used with AX register along with DX for multiply and divde operations 
involving large values.

### Pointer Registers
* IP: **instruction pointer** register stores the offset address of the next instruction to be executed. IP in association with CS register (as CS:IP) gives the complete 
address of the current instruction in the code segment.
* SP: **stack pointer** register provides the offset value within the program stack.
* BP: **basic pointer** mainly helps in referencing the parameter variables passed 
to a subroutine. The address in SS register is combined with the offset in BP to get
the location of the parameter. BP can also be combined with DI and SI as base registerfor special addressing.

### Index Registers
Are used for indexed addressing and sometimes used in addition and subtraction.
* SI: **source index** it is used as source index for string operations.
* DI: **destination index** it is used as destination index for string operations.

### Segment Registers
Segments are specific areas defined in a program for containing data, code and stack.
Thre are thre main segments:
* CS: **code segment** it contains all the instructions to be executed. Stores the 
starting address of the code segment.
* DS: **data segment** it contains data, contains and work areas. Stores the starting
address of the data segment.
* SP: **stack segment** it contains data and return addresses of procedure or 
subroutines. It is implemented as a **stack** data structure. Stores the starting
address of the stack.

All memory locations within a segment are relative to the starting address of the 
segment. To get the exact location of data or instruction within a segment, an offset
value (or displacement) is required.


### Control Registers
Many instructions involve comparisons and mathematical calculations and change the
status of the flags and some other conditional instructions test the value of these
status flags to take the control flow to ther location.

|  Flag:  |    |    |    |    |  O |  D | I | T | S | Z |   | A |   | P |   | C |
|:-------:|:--:|:--:|:--:|:--:|:--:|:--:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Bit No: | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |


## Stack 


## How to Taste
LLDB/GDB debugging or **otool** :
```sh
$ ./configure --has-asm --with-optimize=NO
$ make
$ lldb objs/bin/asm
$ otool -tv objs/bin/asm
```


## References
* [Intel and AT&T Syntax](http://www.imada.sdu.dk/Courses/DM18/Litteratur/IntelnATT.htm)
* [Assembly Programming Tutorial](https://www.tutorialspoint.com/assembly_programming/index.htm)
* [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://software.intel.com/en-us/articles/intel-sdm)
