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
  assert(a1[a1.count - 1] == "blueberries")
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

func objectsAndClasses() {
  let shape1 = Shape(name: "unnamed")
  assert(shape1.name == "unnamed")

  let square1 = Square(sideLength: 2.0, name: "Square")
  assert(square1.area() == 4.0)

  let triangle1 = EquilateralTriangle(sideLength: 3.0, name: "Triangle")
  assert(triangle1.perimeter == 3.0 * 3.0)
  triangle1.perimeter = 24.0
  assert(triangle1.sideLength == 8.0)

  let st1 = SquareAndTriangle(size: 3, name: "square & triangle")
  assert(st1.square.sideLength == 3.0 && st1.triangle.sideLength == 3.0)
  st1.square = Square(sideLength: 4.0, name: "larger square")
  assert(st1.triangle.sideLength == 4.0)
}

func enumerationsAndStructures() {
  let ace = Rank.ace
  assert(ace.rawValue == 1)

  if let r1 = Rank(rawValue: 9) {
    assert(r1 == Rank.nine)
  }

  let spades3 = Card(rank: .three, suit: .spades)
  assert(spades3.rank == Rank.three && spades3.suit == Suit.spades)
}

func concurrency() async {
  let r1 = await slowFetch(from: "xxx")
  assert(r1 == 501)

  let r2 = await slowFetch(from: "primary")
  assert(r2 == 200)
}

func protocolsAndExtensions() {
  let c1 = SimpleClassExample()
  c1.adjust()
  assert(c1.desc.count > 0)

  var s1 = SimpleStructExample()
  s1.adjust()
  assert(s1.desc.count > 0)

  var i1 = 0
  i1.adjust()
  assert(i1 == 1)
}

func errorHandling() {
  do {
    let p1 = try send(job: 101, toPrinter: "HP2210")

    defer {
      assert(p1.count > 0)
    }

    // error: Initializer for conditional binding must have Optional
    // type, not 'String'.
    // if let p2 = try send(job: 103, toPrinter: "HP2211") {
    //   assert(p2.count > 0)
    // }

    if let p3 = try? send(job: 103, toPrinter: "HP3211") {
      assert(p3.count > 0)
    }

    // should stopped
    // let p4: String? = try! send(job: 104, toPrinter: "HP2211")
    // assert(p4 == nil)

    let _ = try send(job: 102, toPrinter: "HP2211")

  } catch PrinterError.noToner(let percent) {
      print("noToner:", percent)
  } catch {
    print(error)
  }
}

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

// objects & classes

class Shape {
  var name: String
  var numberOfSides = 0
  init(name: String) {
    self.name = name
  }
  func simpleDescription() -> String {
    return "A shape with \(numberOfSides) sides."
  }
}

class Square: Shape {
  var sideLength: Double
  init(sideLength: Double, name: String) {
    self.sideLength = sideLength
    super.init(name: name)
    numberOfSides = 4
  }
  func area() -> Double {
    return sideLength * sideLength
  }
  override func simpleDescription() -> String {
    return "A square with sides of length \(sideLength)."
  }
}

class EquilateralTriangle: Shape {
  var sideLength: Double
  init(sideLength: Double, name: String) {
    self.sideLength = sideLength
    super.init(name: name)
    numberOfSides = 3
  }
  var perimeter: Double {
    get {
      return 3.0 * sideLength
    }
    set {
      sideLength = newValue / 3.0
    }
  }
  override func simpleDescription() -> String {
    return "An equilateral triangle with sides of length \(sideLength)."
  }
}

class SquareAndTriangle {
  var square: Square {
    willSet {
      triangle.sideLength = newValue.sideLength
    }
  }
  var triangle: EquilateralTriangle {
    willSet {
      square.sideLength = newValue.sideLength
    }
  }
  init(size: Double, name: String) {
    square = Square(sideLength: size, name: name)
    triangle = EquilateralTriangle(sideLength: size, name: name)
  }
}

// enumerations & structures

enum Rank: Int {
  case ace = 1
  case two, three, four, five, six, seven, eight, nine, teen
  case jack, queen, king
  func simpleDescription() -> String {
    switch self {
    case .ace: return "ace"
    case .jack: return "jack"
    case .queen: return "queen"
    case .king: return "king"
    default: return String(self.rawValue)
    }
  }
}

enum Suit {
  case spades, hearts, diamonds, clubs
}
struct Card {
  var rank: Rank
  var suit: Suit
}

// concurrency

func slowFetch(from server: String) async -> Int {
  if server == "primary" {
    return 200
  }
  return 501
}

// errorHandling
enum PrinterError: Error {
  case outOfPaper
  case noToner(percent: Int)
  case onFire
}

// how to qualify the throws type
func send(job: Int, toPrinter printerName: String) throws -> String {
  if printerName == "HP2211" {
    throw PrinterError.noToner(percent: 7)
  }
  return "Job sent"
}

// generics
func makeArray<T>(repeating item: T, numberOfTimes: Int) -> [T] {
  var result: [T] = []
  for _ in 0..<numberOfTimes {
    result.append(item)
  }
  return result
}

enum OptionalValue<Wrapped> {
  case none
  case some(Wrapped)
}

func anyOverlapped<T: Sequence, U: Sequence>(_ lhs: T, _ rhs: U) -> Bool
where T.Element: Equatable, T.Element == U.Element {
  for lhsItem in lhs {
    for rhsItem in rhs {
      if lhsItem == rhsItem {
        return true
      }
    }
  }
  return false
}

// protocols
protocol ExampleProtocol {
  var desc: String { get }
  mutating func adjust()
  // mutating func newFeature(a: Int) -> Int
}

class SimpleClassExample: ExampleProtocol {
  var desc = "A simple class example."
  func adjust() {
    desc += " Now adjusted."
  }
}

struct SimpleStructExample: ExampleProtocol {
  var desc = "A simple struct example."
  mutating func adjust() {
    desc += " Now it doesn't look like ancient."
  }
}

// extensions
extension Int: ExampleProtocol {
  var desc: String {
    return "The number \(self)."
  }
  mutating func adjust() {
    self += 1
  }
}
