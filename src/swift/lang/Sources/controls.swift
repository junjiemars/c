func controls() {
    for_in()
    for_in_destruct()
    conditional_assign()
    optional_assign()
    switch_case()
    while_repeat()
}

func for_in() {
    let a1 = [75, 43, 103, 87, 12]
    var sum = 0
    for a in a1 {
        if a >= 50 {
            sum += 3
        } else {
            sum += 1
        }
    }
    assert(sum > 0)

    var f1 = 2
    for i in 2..<5 {
        f1 += i
    }
    assert(f1 == 11)
}

func for_in_destruct() {
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
}

func conditional_assign() {
    #if swift(>=6)
    let sum = 51
    let g50 = if sum > 50 {
        "great than 50"
    } else {
        "less or equal to 50"
    }
    assert(g50.count > 0)
    #endif
}

func optional_assign() {
    let optStr1: String? = "Apple"
    let optStr2: String? = nil
    if let name = optStr1 {
        assert(name.count > 0)
    }
    if let name = optStr2 {
        assert(name.count > 0)
    }
}

func switch_case() {
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
}

func while_repeat() {
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
}
