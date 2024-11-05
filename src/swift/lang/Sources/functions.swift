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
}
