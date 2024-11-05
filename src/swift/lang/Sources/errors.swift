// how to qualify the throws type
func send(job: Int, toPrinter printerName: String) throws -> String {
  if printerName == "HP2211" {
    throw PrinterError.noToner(percent: 7)
  }
  return "Job sent"
}

func sendWithTypedError(job: Int, toPrinter printerName: String) throws(PrinterError) -> String {
  if printerName == "HP2212" {
    throw .onFire
  }
  return "Job sent"
}

func sendWithThrowsNever(job: Int, toPrinter printerName: String) throws(Never) {
  print("sendWithNever")
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

  do {
    let _ = try sendWithTypedError(job: 101, toPrinter: "HP2212")
  } catch {
    print("\(error)")
  }

  sendWithThrowsNever(job: 101, toPrinter: "HP2210")
}
