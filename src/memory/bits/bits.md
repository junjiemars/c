# Bits

## Shift
Logical shift always fill discarded bits with 0s while arithmetic shift fills it with
0s only for left shift, but for right shift it copies the most significant bit (MSB)
thereby preserving the sign of the operand.

### On Unsigned Integers

Left shift on unsigned integers. ```x << y```
* shift bit-vector ```x``` left by ```y``` positions
* throw away extra bits on left
* fill with 0s on right

Right shift on unsigned integers. ```x >> y```
* shift bit-vector ```x``` right by ```y``` positions
* throw away extra bits on right
* fill with 0s on left

### On Signed Integers

Left shift, ```x << y```
* equivalent to multiplying by ```2^y```
* if resulting value fits, no 1s are lost

Right shift, ```x >> y```
* logical shift for unsigned values
	* fill with 0s on left
* arithmetic shift for signed values
	* replicate most significant on left
	* maintains sign of ```x```
* equivalent to ```floor(2^y)```
	* correct rounding towards 0 requires some care with signed numbers.
	* ```(unsigned)x >> y | ~(~0u >> y)```


## References
* [Logical shift](https://en.wikipedia.org/wiki/Logical_shift)
* [Arithmetic shift](https://en.wikipedia.org/wiki/Arithmetic_shift)
* [Are the shift operators arithmetic or logical in C?](https://stackoverflow.com/questions/7622/are-the-shift-operators-arithmetic-or-logical-in-c)
