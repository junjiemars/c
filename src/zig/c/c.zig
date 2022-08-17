const c = @cImport({
    @cInclude("c.h");
});

pub fn incr1(a: c_int) c_int {
    return a + 1;
}
