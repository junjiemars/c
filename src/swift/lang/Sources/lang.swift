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
