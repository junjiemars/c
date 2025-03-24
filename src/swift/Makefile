# -*- mode:makefile-gmake -*-
#
# ./configure --has-swift
#
# make clean test
#
# https://www.swift.org
# https://docs.swift.org/swift-book
# https://swiftpackageindex.com
# https://developer.apple.com/library/archive/documentation/Porting/Conceptual/PortingUnix/intro/intro.html
#


swift: swift_hi                                 \
       swift_cli                                \
       swift_lang                               \
       swift_lib                                \
       swift_foundation                         \
       swift_os

swift_test: swift_hi_test                       \
            swift_cli_test                      \
            swift_lang_test                     \
            swift_lib_test                      \
            swift_foundation_test               \
            swift_os_test

# env
swift_prefix := swift
SWIFT := $(has_swift)

swift_build := debug
ifeq ($(NM_BUILD),YES)
swift_build := release
endif

ifeq ($(NM_VERBOSE),YES)
swift_build += --verbose
endif

swiftc_v5 := -Xswiftc -swift-version -Xswiftc 5
swiftc_v6 := -Xswiftc -swift-version -Xswiftc 6

swift_package_root := --package-path=$(swift_root)




# hi
swift_hi_package := $(swift_root)/hi/Package.swift
swift_hi_binout := $(swift_root)/hi/.build/$(swift_build)/hi

swift_hi: $(swift_hi_binout)
swift_hi_test: swift_hi
	$(SWIFT) run $(swift_package_root)/hi
swift_hi_clean:
	$(SWIFT) package $(swift_package_root)/hi clean

$(swift_hi_package):
	$(SWIFT) package $(swift_package_root)/hi \
		init --type=executable --name=Hi

$(swift_hi_binout): $(swift_hi_package) \
                    $(swift_root)/hi/Sources/hi/main.swift
	$(SWIFT) build $(swift_package_root)/hi -c $(swift_build) $(swiftc_v5)



# lang
swift_lang_package := $(swift_root)/lang/Package.swift
swift_lang_binout := $(swift_root)/lang/.build/$(swift_build)/lang

swift_lang: $(swift_lang_binout)
swift_lang_test: swift_lang
	$(swift_lang_binout)
swift_lang_clean:
	$(SWIFT) package $(swift_package_root)/lang clean

$(swift_lang_package):
	$(SWIFT) package $(swift_package_root)/lang \
		init --type=executable --name=lang

$(swift_lang_binout): $(swift_lang_package) \
                      $(swift_root)/lang/Sources/main.swift \
                      $(swift_root)/lang/Sources/lang.swift \
                      $(swift_root)/lang/Sources/values.swift \
                      $(swift_root)/lang/Sources/controls.swift \
                      $(swift_root)/lang/Sources/functions.swift \
                      $(swift_root)/lang/Sources/objects.swift \
                      $(swift_root)/lang/Sources/enumerations.swift \
                      $(swift_root)/lang/Sources/concurrency.swift \
                      $(swift_root)/lang/Sources/protocols.swift \
                      $(swift_root)/lang/Sources/errors.swift \
                      $(swift_root)/lang/Sources/protocols.swift
	$(SWIFT) build $(swift_package_root)/lang -c $(swift_build)



# lib
swift_lib_package := $(swift_root)/lib/Package.swift
swift_lib_binout := $(swift_root)/lib/.build/$(swift_build)/lib

swift_lib: $(swift_lib_binout)
swift_lib_test: swift_lib
	$(SWIFT) test $(swift_package_root)/lib
swift_lib_clean:
	$(SWIFT) package $(swift_package_root)/lib clean

$(swift_lib_package):
	$(SWIFT) package $(swift_package_root)/lib \
		init --type=executable --name=Lib

$(swift_lib_binout): $(swift_lib_package) \
                     $(swift_root)/lib/Sources/lib/Lib.swift
	$(SWIFT) build $(swift_package_root)/lib -c $(swift_build) $(swiftc_v5)



# cli
swift_cli_package := $(swift_root)/cli/Package.swift
swift_cli_binout := $(swift_root)/cli/.build/$(swift_build)/cli

swift_cli: $(swift_cli_binout)
swift_cli_test: swift_cli
	$(swift_cli_binout) --input $@
swift_cli_clean:
	$(SWIFT) package $(swift_package_root)/cli clean

$(swift_cli_binout): $(swift_cli_package) \
                     $(swift_root)/cli/Sources/cli.swift
	$(SWIFT) build $(swift_package_root)/cli -c $(swift_build)



# foundation
swift_foundation_package := $(swift_root)/foundation/Package.swift
swift_foundation_binout := $(swift_root)/foundation/.build/$(swift_build)/foundation

swift_foundation: $(swift_foundation_binout)
swift_foundation_test: swift_foundation
	$(swift_foundation_binout)
swift_foundation_clean:
	$(SWIFT) package $(swift_package_root)/foundation clean

$(swift_foundation_package):
	$(SWIFT) package $(swift_package_root)/foundation \
		init --type=executable --name=foundation

$(swift_foundation_binout): $(swift_foundation_package) \
                      $(swift_root)/foundation/Sources/main.swift
	$(SWIFT) build $(swift_package_root)/foundation -c $(swift_build)



# os
swift_os_package := $(swift_root)/os/Package.swift
swift_os_binout := $(swift_root)/os/.build/$(swift_build)/os

swift_os: $(swift_os_binout)
swift_os_test: swift_os
	$(swift_os_binout)
swift_os_clean:
	$(SWIFT) package $(swift_package_root)/os clean

$(swift_os_package):
	$(SWIFT) package $(swift_package_root)/os \
		init --type=executable --name=os

$(swift_os_binout): $(swift_os_package) \
                    $(swift_root)/os/Sources/main.swift \
                    $(swift_root)/os/Sources/c.swift \
                    $(swift_root)/os/Sources/lib.swift
	$(SWIFT) build $(swift_package_root)/os -c $(swift_build)



.PHONY: swift_hi swift_hi_test swift_hi_clean                         \
        swift_cli swift_cli_test swift_cli_clean                      \
        swift_lang swift_lang_test swift_lang_clean                   \
        swift_foundation swift_foundation_test swift_foundation_clean \
        swift_os swift_os_test swift_os_clean

# eof
