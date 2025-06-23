func enumerations() {
  let ace = Rank.ace
  assert(ace.rawValue == 1)

  if let r1 = Rank(rawValue: 9) {
    assert(r1 == Rank.nine)
  }

  let spades3 = Card(rank: .three, suit: .spades)
  assert(spades3.rank == Rank.three && spades3.suit == Suit.spades)
}
