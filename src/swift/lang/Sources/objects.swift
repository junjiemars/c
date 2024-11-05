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
