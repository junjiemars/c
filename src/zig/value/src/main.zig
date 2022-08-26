const std = @import("std");
const print = std.debug.print;
const assert = std.debug.assert;
const mem = std.mem;

pub fn main() anyerror!void {
    // integers
    const one_plus_one: i32 = 1 + 1;
    print("1 + 1 = {}\n", .{one_plus_one});

    // floats
    const seven_div_three: f32 = 7.0 / 3.0;
    print("7.0 / 3.0 = {}\n", .{seven_div_three});

    // boolean
    print("{}\n{}\n{}\n", .{
        true and false,
        true or false,
        !true,
    });

    // optional
    var optional_value: ?[]const u8 = null;
    assert(optional_value == null);

    print("\noptional #1\ntype: {s}\nvalue: {any}\n", .{
        @typeName(@TypeOf(optional_value)),
        optional_value,
    });

    optional_value = "hi";
    assert(optional_value != null);

    print("\noptional #2\ntype: {s}\nvalue: {any}\n", .{
        @typeName(@TypeOf(optional_value)),
        optional_value,
    });

    // error union
    var number_or_error: anyerror!i32 = error.ArgNotFound;

    print("\nerror union #1\ntype: {s}\nvalue: {any}\n", .{
        @typeName(@TypeOf(number_or_error)),
        number_or_error,
    });

    number_or_error = 1234;

    print("\nerror union #2\ntype: {s}\nvalue: {!}\n", .{
        @typeName(@TypeOf(number_or_error)),
        number_or_error,
    });

    // string literal
    const bytes = "hello";
    print("{s}\n", .{@typeName(@TypeOf(bytes))}); // *const [5:0]u8
    print("{d}\n", .{bytes.len}); // 5
    print("{c}\n", .{bytes[1]}); // 'e'
    print("{d}\n", .{bytes[5]}); // 0
    print("{}\n", .{'e' == '\x65'}); // true
    print("{d}\n", .{'\u{1f4a9}'}); // 128169
    print("{d}\n", .{'💯'}); // 128175
    print("{}\n", .{mem.eql(u8, "hello", "h\x65llo")}); // true
    // non-UTF-8 strings are possible with \xNN notation.
    print("0x{x}\n", .{"\xff"[0]});
    print("{u}\n", .{'⚡'});

    // multiline string literal
    const multiline_string =
        \\
        \\#include <stdio.h>
        \\
        \\int main(int argc, char **argv) {
        \\    printf("hello world\n");
        \\    return 0;
        \\}
    ;
    print("multiline string = {s}\n", .{multiline_string});
}
