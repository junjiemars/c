const ffi = require('ffi-napi');

const libm = ffi.Library('libm', {
		'ceil': [ 'double', [ 'double' ] ]
});
console.log('ceil(%s) = %s', 1.5, libm.ceil(1.5));

