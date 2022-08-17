const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const obj = b.addObject("c", "c.zig");
    const exe = b.addExecutable("zig_z3", null);

    exe.addCSourceFile("m.c", &[_][]const u8{});
    exe.addObject(obj);

    exe.setTarget(b.standardTargetOptions(.{}));
    exe.setBuildMode(b.standardReleaseOptions());
    exe.addIncludeDir("./");

    exe.linkLibC();
    exe.install();

    const run_cmd = exe.run();
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run z3");
    run_step.dependOn(&run_cmd.step);
}
