# Notes of Mastering Algorithms with C

## Notations
Everything that is ```Ө(f(n))``` is also ```O(f(n))```, but not the other way around.
```T(n)``` is said to be in ```Ө(f(n))``` if it is both in ```O(f(n))``` and in
```Ω(f(n))```

```O(n)``` is asymptotic upper bound. If ```T(n)``` is ```O(f(n))```, it means that
from a certain ```n0```, there is a constant ```c``` such that ```T(n) <= c * f(n)```.
On the other hand, big-Omega says there is a constant ```c'``` such that
```T(n) >= c' * f(n)```.


### Big-O notation
O-notation expresses the upper bound of a function within a constant factor, and 
reflects an algorithm's order of growth.

## Worst-Case Analysis 
Most algorithms do not perform the same in all cases; normally an algorithm's 
performance varies with the data passed to it.

The worst case gives us an upper bound on performance.

#### Simple Rules for big-O notation 
* Constant terms are expressed as ```O(1) => O(c) = O(1)```
* Multiplicative constants are omitted: ```O(cT) = cO(T) = O(T)```
* Addition is performed by taking the maximum: ```O(T1) + O(T2) = max(O(T1), O(T2))```
* Multiplication: ```O(T1) * O(T2) = O(T1*T2)```

#### Computational Complexity
Complexity is the growth rate of the resources usually time it requires with respect
to the size of the data it processes.

### Big-Omega notation
Ω-notation expresses the lower bound of a function within a constant factor, and 
reflects an algorithm's order of growth.


### Big-Theta notation
Ө-notation says once n gets large enough, the running time is at least ```k1*n``` and
at most ```k2*n``` for some constants ```k1``` and ```k2```.

A function ```f(n)``` belongs to ```Theta(g(n))```, if there exists positive constant
```c1``` and ```c2``` such that ```f(n)``` can be sandwiched between ```c1(g(n))```
and ```c2(g(n))```.


## References
* asymptote: a line that continually approaches a given curve but doest not meet it
at any finit distance.
* [What exactly does big Ө notation represent?](http://stackoverflow.com/questions/10376740/what-exactly-does-big-Ө-notation-represent)

