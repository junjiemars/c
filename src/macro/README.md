# Macro

## Expression
Expression-type macro will expand to expression, such as the following
macro definition
```c
#define double_v1(x) 2*x
```
Macro call ```double_v1(1+1)*8``` expands to wrong expression ```2*1+1*8```

Use parens to quoted input arguments and final expression:
```c
#define double_v2(x) (2*(x))
```
Now, it expands to ```(2*(1+1))*8```

But, **max** has side-effect that eval the argument twice
```c
#define max(a, b) ((a) > (b) ? (a) : (b))
```
if call it with ```max(a, b++)``` .


## Block
If the macro definition includes ```;``` statatment ending character, we need
to block it.

```c
#define incr(a, b)   \
    (a)++;           \
    (b)++;
```
Call it with
```c
int a=2, b=3;
if (a > b) incr(a, b);
```
just only ```b``` will be incremented. We can block it and convert it to block-type macro
```c
#define incr(a, b) { \
    (a)++;           \
    (b)++;           \
}    
```

## Name Clashs
We can use same machinism like Lisp's ```(gensym)``` to rebind the input arguments to new symbols.

## Check Expansion

```c
$ cc -E <source>
```


