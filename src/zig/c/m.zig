const c = @cImport({
    @cInclude("c.h");
    @cInclude("stdio.h");
});

pub fn main() void {
    const a: c_int = c.incr1(3);
    _ = c.printf("incr1: %d\n", a);
}
