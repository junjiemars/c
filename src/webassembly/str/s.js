// hello fn
var ptr1 = _hello();
console.log(ptr1);
console.log(UTF8ToString(ptr1));

// mark_a fn
var ss = "I'm a JS string";
var ptr2 = allocate(intArrayFromString('w1.h'), 'i8', ALLOC_NORMAL);
console.log(ss, ptr2);
var ptr3 = _mark_a(ptr2);
console.log(ptr3, UTF8ToString(ptr3));
_free(ptr2);

var ss1 = ccall('mark_a', 'string', ['string'], ['mark it']);
console.log(ss1);
console.time('mark_a');
console.log(ccall('mark_a', 'string', ['string'], ['mark it']));
console.timeEnd('mark_a');


