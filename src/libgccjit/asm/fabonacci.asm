;; int fibonacci(int n)
;; {
;;   if (n == 0 || n == 1) {
;;   	return 1;
;;   }
;;   return fibo1(n-1) + fibo1(n-2);	
;; }
	
.1:
	push_const 0
.2:
	binary_comp_eq
.3:
	jump_abs_if_true .X
.4:
	push_const 1
.5:
	binary_comp_eq
.6:
	jump_abs_if_true .X
.7:
	binary_sub
.8:
	recurse
.9:
	binary_sub
.10:
	recurse
.11:
	binary_mult

.X:
	push_const 1
	return
