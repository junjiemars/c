;; int factorial(int arg)
;; {
;;    if (arg < 2)
;;      return arg
;;    return arg * factorial(arg - 1)
;; }

.1:
	dup
.2:
	push_const 2
.3:
	binary_comp_lt
.4:
	jump_abs_if_true .9
.5:
	push_const 1
.6:
	binary_sub
.7:
	recurse
.8:
	binary_mult
.9:
	return


