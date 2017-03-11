# Calling Conversion

## Machine

### Darwin
The **stack** growth from high to low, and **memory** growth from low to high.

## cdecl
* Arguments are passed on the stack in Right-to-Left order, and return values are 
passed in _eax_
* The caller cleans the stack. This allows _cdecl_ functions to have 
variable-length argument lists (aka variadic function). For this reason the number
of arguments is not appended to the name of the function by the compiler, and the
assembler and the linker are therefore unable to detemine if an incorrect number
of arguments is used.

![stack frame](frame-cdecl.gif)

|  32 bits  |  64 bits  |                                                     |
|----------:|----------:|:----------------------------------------------------|
|  16(%ebp) |  32(%rbp) |  third function parameter                           |
|  12(%ebp) |  24(%rbp) |  second function parameter                          |
|   8(%ebp) |  16(%rbp) |  first function parameter                           |
|   4(%ebp) |   8(%rbp) |  old %eip|%rip (the function's return address)      |
|   0(%ebp) |   0(%rbp) |  old %ebp|%rbp (previous function's base pointer)   |
|  -4(%ebp) |  -8(%rbp) |  first local variable                               |
|  -8(%ebp) | -16(%rbp) |  second local variable                              |
| -12(%ebp) | -24(%rbp) |  third local variable                               |




## stdcall
* Passes arguments Right-to-Left, and returns the value in _eax_.
* The callee cleans the stack, unlike _cdecl_.

## fastcall
* The first 2 or 3 arguments are passed in registers (aka edx, eax, ecx)
* Additional arugments, or arguments larger than 4-bytes are passed on the stack, 
often in Right-to-Left order.
* The caller is responsible for cleaning the stack, if needed.


## References
* [x86 Disassembly/Calling Conversions](https://en.wikibooks.org/wiki/X86_Disassembly/Calling_Conventions)
* [x86 calling conversions](https://en.wikipedia.org/wiki/X86_calling_conventions)
* [Intel x86 Function-call conversions - Assembly View](http://unixwiz.net/techtips/win32-callconv-asm.html)
* [Procedures, Video 4: Linux stack frame](https://www.youtube.com/watch?v=PrDsGldP1Q0)
