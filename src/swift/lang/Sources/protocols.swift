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
