# Math Practices
Demostrates how to link the shared libraries, standard or non-standard, and how to do basic testing.

## Link Shared Library

## Basic Math Functions

## Testing

### View Dependents of Executable
* on Windows:
```sh
dumpbin -dependents objs/bin/math_shared
```
* on Darwin:
```sh
otool -L objs/bin/math_shared
```
* on Linux:
```sh
# safe
objdump -p objs/bin/math_shared
# or 
ldd objs/bin/math_shared
```

## References
* [Dynamic-link library](https://en.wikipedia.org/wiki/Dynamic-link_library)
* [Static library](https://en.wikipedia.org/wiki/Static_library)
