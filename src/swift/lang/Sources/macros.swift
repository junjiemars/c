func macros() {
    macro_trace()
    macro_attached()
}

func macro_trace() {
    // freestanding macro
    // #function and #line from standard library
    print("trace function=\(#function)@line=\(#line)")
}

func macro_attached() {
    assert(Colors1.red == Colors1.red)
    assert(Colors1.red != Colors1.blue)
    #if swift(>=6)
    assert(Colors1.red == Colors2.red)
    #endif
}
