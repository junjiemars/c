# Notes of Mastering Algorithms with C

## Worst-Case Analysis 
Most algorithms do not perform the same in all cases; normally an algorithm's 
performance varies with the data passed to it.

The worst case gives us an upper bound on performance.

## O-Notation
O-Notation expresses the upper bound of a function within a constant factor, and 
reflects an algorithm's order of growth.

### Simple Rules for O-Notation 
* Constant terms are expressed as ```O(1) => O(c) = O(1)```
* Multiplicative constants are omitted: ```O(cT) = cO(T) = O(T)```
* Addition is performed by taking the maximum: ```O(T1) + O(T2) = max(O(T1), O(T2))```
* Multiplication: ```O(T1) * O(T2) = O(T1*T2)```

### Computational Complexity
Complexity is the growth rate of the resources usually time it requires with respect
to the size of the data it processes.
