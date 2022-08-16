const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const exe = b.addExecutable("z1", "./");

    const source_files = &[]const u8{ "c.c", "m.c" };

    for (source_files) |source| {
        exe.addSourceFile(source);
    }

    exe.setOutputPath("../../../out/bin/z1");
    b.default_step.dependOn(&exe.step);
}
