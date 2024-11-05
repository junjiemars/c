import Foundation

func list(_ root: String) {
  print("XXX")
}

func processes() {
  let processName = ProcessInfo.processInfo.processName
  assert(processName == "os")
  let environment = ProcessInfo.processInfo.environment
  assert(environment.count > 0)
  let hostName = ProcessInfo.processInfo.hostName
  assert(hostName.count > 0)
}

func foundations() {
  let u1 = URLComponents(string: "https://swift.org")!
  assert(u1.host == "swift.org")
}

func unsafeCases() {
  unsafePointers()
}
