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
  assert(f1 < f2, "f1 should less than f2")

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
  assert(!quotation.isEmpty)
  print(quotation)

  var a1 = ["strawberries", "limes", "tangerines"]
  assert(a1[1] == "limes")
  a1.append("blueberries")
  assert(a1[a1.count - 1] == a1.last && a1.last == "blueberries")
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
