const std = @import("std");

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    try stdout.print("Guess the number!\n", .{});

    var rand = std.rand.DefaultPrng.init(0);
    const secret_number = rand.random().intRangeAtMostBiased(i32, 1, 100);
    // try stdout.print("The secret number is: {}\n", .{secret_number});

    while (true) {
        const stdin = std.io.getStdIn().reader();
        var buf = [_]u8{0} ** 16;
        const n = stdin.read(&buf) catch continue;

        if ('Q' == buf[0]) {
            try stdout.print("Quit!\n", .{});
            return;
        }

        const line = std.mem.trim(u8, buf[0 .. n - 1], " \n");
        try stdout.print("You guessed: {s}\n", .{line});

        var guess = std.fmt.parseInt(i32, line, 10) catch continue;
        if (guess < secret_number) {
            try stdout.print("Too small!\n", .{});
        } else if (guess > secret_number) {
            try stdout.print("Too big!\n", .{});
        } else {
            try stdout.print("You win!\n", .{});
            break;
        }
    }
}
