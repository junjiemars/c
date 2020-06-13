// ver fn
console.log(_ver());

// double_elem
var ii1 = [1,2,3,4,5];
ii1;
var ii1ptr = _malloc(ii1.length*4);
ii1ptr;
Module.HEAP32.set(new Int32Array(ii1, ii1ptr/4));
ccall('double_elem', 'number', ['number', 'number'], [ii1ptr, ii1.length]);
// _free(ii1ptr);

// // sort_str fn
// var ss1 = [
// 	"a1 9 2 3 1",
// 	"g1 act car",
// 	"zo4 4 7",
// 	"ab1 off key dog",
// 	"a8 act zoo",
// ];
// console.log(ss1);
// ccall('sort_str', 'void', ['array', 'number'],
//       [ss1, ss1.length],
//       { heapIn: "HEAP8",
//         heapOut: "HEAP8"
//       }
//      );

