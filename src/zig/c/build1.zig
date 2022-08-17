const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const exe = b.addExecutable("z1", null);
    exe.addCSourceFile("c.c", &[_][]const u8{});
    exe.addCSourceFile("m.c", &[_][]const u8{});

    exe.setTarget(b.standardTargetOptions(.{}));
    exe.setBuildMode(b.standardReleaseOptions());
    exe.linkLibC();
    exe.install();

    const run_cmd = exe.run();
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run z1");
    run_step.dependOn(&run_cmd.step);
}
