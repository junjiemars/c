func controlFlow() {
  let a1 = [75, 43, 103, 87, 12]
  var sum = 0
  for a in a1 {
    sum += a
  }
  assert(sum > 0)

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
