func functions() {
    nest_function()

    let frt1 = function_return_tuple(a: 3)
    assert(frt1.name == "Integer" && frt1.value == 3)

    assert(has_any_match(list: [1, 4, 9, 25], condition: great_than_20)
             &&
             has_any_match(
               list: [1, 4, 9, 25],
               condition: {
                   (n: Int) -> Bool in
                   return n > 9
               }))

    assert([1, 2, 3, 4, 5].map({ n in return (n * n) }).count == 5)

    assert([1, 5, 9, 2, 1].sorted { $0 > $1 }.count == 5)

    let mean1 = variadic_parameters(1.0, 2.0, 3.0)
    assert(mean1 == 2.0)

    var si1 = 1
    var si2 = 2
    inout_parameters(&si1, &si2)
    assert(si1 == 2 && si2 == 1)

    let add3 = function_return_function(zero: 1, 3)
    assert(add3() == 4)
    assert(add3() == 7)
}

func nest_function() {
    func greet(_ person: String, on day: String) -> String {
        return "Hello \(person), today is \(day)."
    }
    let g1 = greet("Bobby", on: "Monday")
    assert(g1.hasPrefix("Hello"))
}

func variadic_parameters(_ numbers: Double...) -> Double {
    var sum = 0.0
    for n in numbers {
        sum += n
    }
    return sum / Double(numbers.count)
}

func inout_parameters(_ a: inout Int, _ b: inout Int) {
    let temp = a
    a = b
    b = temp
}
