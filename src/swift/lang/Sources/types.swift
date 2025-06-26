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
        case .ace: return "A"
        case .jack: return "J"
        case .queen: return "Q"
        case .king: return "K"
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

// errorHandling
enum PrinterError: Error {
    case outOfPaper
    case noToner(percent: Int)
    case onFire
}


// generic functions
func makeArray<T>(repeating item: T, numberOfTimes: Int) -> [T] {
    var result: [T] = []
    for _ in 0..<numberOfTimes {
        result.append(item)
    }
    return result
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

// enumerations
enum OptionalValue<Wrapped> {
    case none
    case some(Wrapped)
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

// macros
struct Colors1: OptionSet {
    let rawValue: Int
    static let red = Colors1(rawValue: 1 << 0)
    static let green = Colors1(rawValue: 1 << 1)
    static let blue = Colors1(rawValue: 1 << 2)
}

#if swift(>=6)
@OptionSet<Int>
struct Colors2 {
    private enum Options: Int {
        case red
        case green
        case blue
    }
}
#endif
