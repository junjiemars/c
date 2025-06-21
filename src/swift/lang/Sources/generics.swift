func generics() {
    let a1 = makeArray(repeating: "A", numberOfTimes: 3)
    assert(a1.count == 3 && a1[0] == "A")

    var o1: OptionalValue<Int> = .none
    o1 = .some(100)
    assert(o1 != .init(nilLiteral: ()))

    let o2 = Optional.some(100)
    assert(o2 != nil)

    assert(anyOverlapped([1, 2, 3], [3]))
    assert(anyOverlapped(["A", "B", "C"], ["B"]))
}

// functions
func function_return_tuple(a: Int) -> (name: String, value: Int) {
    return (name: "Integer", value: a)
}

func function_return_function(zero: Int, _ increment: Int) -> (() -> Int) {
    var i = zero
    func incr() -> Int {
        i += increment
        return i
    }
    return incr
}

func has_any_match(list: [Int], condition: (Int) -> Bool) -> Bool {
    for i in list {
        if condition(i) {
            return true
        }
    }
    return false
}

func great_than_20(n: Int) -> Bool {
    return n > 20
}

// objects & classes
