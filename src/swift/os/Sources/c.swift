func unsafePointers() {
    rawPointers()
    casting()
}

func rawPointers() {
    // great!
    let p1 = UnsafeMutableRawPointer.allocate(byteCount: 4, alignment: 4)
    p1.storeBytes(of: 0x1122_3344, as: UInt32.self)
    let littleEndian = p1.load(as: UInt8.self) == 0x44
    let x = p1.load(as: UInt8.self)
    assert(littleEndian ? x == 0x44 : x == 0x11)
    let p2 = p1 + 2 // pointer arithmetic
    let y = p2.load(as: UInt16.self)
    assert(littleEndian ? y == 0x1122 : y == 0x4433)
    p1.deallocate()
}

func casting() {
    let a1 = UnsafeMutableRawPointer.allocate(byteCount: 3, alignment: 4)
    a1.storeBytes(of: 65, toByteOffset: 0, as: UInt8.self)
    a1.storeBytes(of: 66, toByteOffset: 1, as: UInt8.self)
    a1.storeBytes(of: 0, toByteOffset: 2, as: UInt8.self)
    a1.deallocate()
}
