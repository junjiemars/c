// The Swift Programming Language
// https://docs.swift.org/swift-book

import ArgumentParser
import Figlet

@main
struct NoreSwift: ParsableCommand {
  @Option(help: "specify the input")
  public var input: String

  // static func main() {
  //   print("Hello, Nore!")
  // }

  public func run() throws {
    Figlet.say(self.input)
  }
}
