const ffi = require('ffi-napi');

const m = ffi.Library('libm', {
		'ceil': [ 'double', [ 'double' ] ]
});
console.log('ceil(%s) = %s', 1.5, m.ceil(1.5));

function on_sigint(x) {
		console.log('on_sigint(%s)', x);
}

const signal_cb = ffi.Callback('void', [ 'int' ], on_sigint);
const signal_fn = ffi.ForeignFunction(signal_cb, 'void', [ 'int' ]);

signal_fn(2 /* SIGINT */);
