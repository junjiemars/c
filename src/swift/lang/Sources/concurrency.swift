#if swift(>=6)
func concurrency() async {
  let r1 = await slowFetch(from: "xxx")
  assert(r1 == 501)

  let r2 = await slowFetch(from: "primary")
  assert(r2 == 200)
}
#else
func concurrency() {
    // missing
}
#endif
