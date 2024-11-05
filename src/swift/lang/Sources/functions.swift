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

  assert(hasAnyMatches(list: [1, 4, 9, 25], condition: greatThan20))
  assert(
    hasAnyMatches(
      list: [1, 4, 9, 25],
      condition: {
        (n: Int) -> Bool in
        return n == 9
      }))

  assert([1, 2, 3, 4, 5].map({ n in return (n * n) }).count == 5)

  assert([1, 5, 9, 2, 1].sorted { $0 > $1 }.count == 5)

  let mean1 = arithmeticMean(1.0, 2.0, 3.0)
  assert(mean1 == 2.0)

  var si1 = 1
  var si2 = 2
  swapTwoInts(&si1, &si2)
  assert(si1 == 2 && si2 == 1)

  // function type
  let doOnInts1 = addInts
  let doOnInts2 = mulInts
  let sumInts = doOnInts1(1, 2, 3)
  assert(sumInts == 6)
  let mulInts = doOnInts2(1, 2, 3)
  assert(mulInts == 6)
}

// variadic parameters
func arithmeticMean(_ numbers: Double...) -> Double {
  var sum = 0.0
  for n in numbers {
    sum += n
  }
  return sum / Double(numbers.count)
}

func swapTwoInts(_ a: inout Int, _ b: inout Int) {
  let temp = a
  a = b
  b = temp
}

func addInts(_ integers: Int...) -> Int {
  var sum = 0
  for i in integers {
    sum += i
  }
  return sum
}

func mulInts(_ integers: Int...) -> Int {
  var sum = 0
  for i in integers {
    sum *= i
  }
  return sum
}
