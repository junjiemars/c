// The Swift Programming Language
// https://docs.swift.org/swift-book

#if os(macOS)
  #if arch(arm64)
    print("macos/arm64")
  #elseif arch(x86_64)
    print("macos/x86_64")
  #else
    print("macos/unknown")
  #endif
#endif


list("/Applications")
foundations()
processes()
unsafeCases()
