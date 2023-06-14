func values() {
    integers()
}


func integers() {
    let i1 = Int.init(0)
    assert(i1 == 0)

    let i2 = Int.init("11223344", radix: 16)
    assert(i2 == 0x11223344)

    let i3 = Int.init("abc", radix: 10)
    assert(i3 == nil)

    let r1 = Int.random(in: 1..<100)
    print("r1 = \(r1)")
}
