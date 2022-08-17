const c = @cImport({
    @cInclude("c.h");
});

export fn incr1(a: c_int) c_int {
    return a + 1;
}
