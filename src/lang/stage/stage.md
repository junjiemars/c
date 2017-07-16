# Stage
Preprocessor, Compiler, Assembler, Linker and Loader


### Preprocessor
* cc -E calr.c -o calr.i

### Assembler
* cc -S calr.i -o calr.s

### Compiler
* cc -c calr.s -o calr.o

### Linker
* cc calr.o -o calr

### Loader

## Tools

### Darwin

* objdump: llvm object file dumper
* otool: object file displaying tool
* nm: llvm symbol table dumper

### Linux

* objdump
* ldd
* readelf

### Windows

## References
* clang man page
* [What is compiler, linker, loader?](http://stackoverflow.com/questions/3996651/what-is-compiler-linker-loader) by [martinkunev](http://stackoverflow.com/users/515212/martinkunev)
* [Compiler, Assembler, Linker and Loader: A Brief Story](http://www.tenouk.com/ModuleW.html)

