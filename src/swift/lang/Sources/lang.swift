func simpleValues() {
    var v1 = 0x11
    v1 += 1
    let c1 = 0x22
    // c1 += 1
    assert(v1 < c1)

    let d1 = 70.0
    let d2: Double = 70.000001
    assert(d1 < d2)

    let f1: Float = 70.0
    let f2: Float = 70.01
    assert(f1 < f2)

    // assert(d1 == f1)
    assert(d1 == Double(f1))

    let apples = 3
    let oranges = 5
    let appleSummary = "I have \(apples) apples."
    let fruitSummary = "I have \(apples + oranges) pieces of fruit."
    assert(appleSummary.count > 0 && fruitSummary.count > 0)

    let quotation = """
      Say your name!
      quote or unquote the `name' is ambiguous
      """
    print(quotation)

    var a1 = ["strawberries", "limes", "tangerines"]
    assert(a1[1] == "limes")
    a1.append("blueberries")
    assert(a1[a1.count-1] == "blueberries")
    a1 = []
    assert(a1.count == 0)

    var dict1 = [
      "a": 1,
      "b": 2,
      "c": 3,
    ]
    assert(dict1["b"] == 2)
    dict1 = [:]
    assert(dict1.count == 0)
}

func controlFlow() {
    let a1 = [75, 43, 103, 87, 12]
    var sum = 0
    for a in a1 {
        sum += a
    }

    // let g50 = if sum > 50 {
    //     "great than 50"
    // } else {
    //     "less or equal to 50"
    // }
    // assert(g50.count > 0)

    let optStr1: String? = "Apple"
    let optStr2: String? = nil
    if let name = optStr1 {
        assert(name.count > 0)
    }
    if let name = optStr2 {
        assert(name.count > 0)
    }

    let vegetable = "red pepper"
    switch vegetable {
    case "celery":
        assert(vegetable == "celery")
    case "cucumber", "watercress":
        assert(vegetable == "cucumber" || vegetable == "watercress")
    case let x where x.hasSuffix("pepper"):
        print("Is it a spicy \(x)?")
    default:
        assert(vegetable.count > 0)
    }

    let interestingNumbers = [
      "Prime": [2, 3, 5, 7, 11, 13],
      "Fibonacci": [1, 1, 2, 3, 5, 8],
      "Square": [1, 4, 9, 16, 25],
    ]
    var largest = 0
    for (_, numbers) in interestingNumbers {
        for number in numbers {
            if number > largest {
                largest = number
            }
        }
    }
    assert(largest == 25)

    var w1 = 2
    while w1 < 5 {
        w1 *= 2
    }
    assert(w1 == 8)

    var r1 = 2
    repeat {
        r1 *= 2
    } while r1 < 5
    assert(r1 == 8)

    var f1 = 2
    for i in 2..<5 {
        f1 += i
    }
    assert(f1 == 11)
}

func functionsAndClosures() {
    func greet(_ person: String, on day: String) -> String {
        return "Hello \(person), today is \(day)."
    }
    let g1 = greet("Bobby", on: "Monday")
    assert(g1.hasPrefix("Hello"))

    let rt1 = functionReturnTuple(a: 3)
    assert(rt1.name == "Integer" && rt1.value == 3)

    let incr10 = makeIncrementer(zero: 1, increment: 10)
    assert(incr10() == 11)
    assert(incr10() == 21)

    assert(hasAnyMatches(list: [1,4,9,25], condition: greatThan20))
    assert(hasAnyMatches(list: [1,4,9,25],
                         condition: {
                             (n: Int) -> Bool in
                             return n == 9
                         }))

    assert([1,2,3,4,5].map({n in return (n * n)}).count == 5)

    assert([1,5,9,2,1].sorted { $0 > $1 }.count == 5)
}


func functionReturnTuple(a: Int) -> (name: String, value: Int) {
    return (name: "Integer", value: a)
}

func makeIncrementer(zero: Int, increment: Int) -> (() -> Int) {
    var i = zero
    func incr() -> Int {
        i += increment
        return i
    }
    return incr
}

func hasAnyMatches(list: [Int], condition: (Int) -> Bool) -> Bool {
    for i in list {
        if condition(i) {
            return true
        }
    }
    return false
}

func greatThan20(n: Int) -> Bool {
    return n > 20
}
