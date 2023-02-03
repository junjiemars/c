/*
 * https://doc.rust-lang.org/stable/reference/statements.html
 */

pub(crate) fn test() {
    st_declarative();
    st_let();
}

fn st_declarative() {
    fn outer(a: i32) -> () {
        let b: i32;
        b = a + 10;

        fn inner() -> () {
            // `a' and `b' cannot be seen here, because `inner' is a
            // declarative statement.

            // assert!(a > 0);
            // assert!(b > 0);
        }

        assert!(b >= 10);
        inner();
    }

    outer(1);
}

fn st_let() {
    let (/*mut*/ v, s) = (vec![1, 2, 3], 10);
    assert!(v.len() == 3 && s == 10);

    // `E0658': An unstable feature was used.
    // let Some(t) = v.pop() else {
    // 		panic!()
    // };
    // assert!(t == 1);
}
