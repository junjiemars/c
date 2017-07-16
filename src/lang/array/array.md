# Array

## Declaration and Definition

## Variable Length Array

## Dimensions

## [] Operator
```c
a[b] == b[a]
```
The C standard defines the ```[]``` operator as follows:
```a[b] => *(a+b)```, then ```b[a] => *(b+a) => *(a+b)```,
so ```a[b] == b[a]```

## Passing multidimensional arrays to a function


## Iteration
* row-major order, so load a[0][0] would potentially load a[0][1], but load a[1][0] would generate a second cache fault.

## References
* [Array](http://stackoverflow.com/documentation/c/322/arrays#t=20170207121645271737)
