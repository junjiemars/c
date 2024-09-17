pub fn test_marker() {
    test_sized();
}

struct A<T>(T);

struct B<T: ?Sized>(T);

struct A1(A<[u8; 4]>);

struct B1(B<[u8; 1]>);

fn test_sized() {
    let a1 = A1(A([1, 2, 3, 4]));
    assert_eq!(a1.0 .0[0], 1);
    let b = B([1u8]);
    assert_eq!(b.0[0], 1);
    let b1 = B1(B([1]));
    assert_eq!(b1.0 .0[0], 1);
}
