# -*- mode:makefile-gmake -*-
#
# ./configure --has-swift
# make clean test
# https://developer.apple.com/library/archive/documentation/Porting/Conceptual/PortingUnix/intro/intro.html
#


swift: swift_hi                                 \
       swift_lang                               \
       swift_foundation                         \
       swift_os

swift_test: swift_hi_test                       \
            swift_lang_test                     \
            swift_foundation_test               \
            swift_os_test

# env
swift_prefix := swift
SWIFTC := $(has_swiftc)
SWIFT := $(has_swift)

swift_build_opt := debug
ifeq ($(NM_BUILD),YES)
swift_build_opt := release
endif


# hi
swift_hi_package := $(swift_root)/hi/Package.swift
swift_hi_binout := $(swift_root)/hi/$(swift_build_opt)/hi

swift_hi: $(swift_hi_binout)
swift_hi_test: swift_hi
	$(SWIFT) run --package-path=$(swift_root)/hi
swift_hi_clean:
	$(SWIFT) run --package-path=$(swift_root)/hi

$(swift_hi_package):
	$(SWIFT) package --package-path=$(swift_root)/hi  \
		init --type=executable --name=hi

$(swift_hi_binout): $(swift_hi_package)                 \
                    $(swift_root)/hi/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/hi -c $(swift_build_opt)



# lang
swift_lang_package := $(swift_root)/lang/Package.swift
swift_lang_binout := $(swift_root)/lang/debug/lang

swift_lang: $(swift_lang_binout)
swift_lang_test: swift_lang
	$(SWIFT) run --package-path=$(swift_root)/lang
swift_lang_clean:
	$(SWIFT) run --package-path=$(swift_root)/lang

$(swift_lang_package):
	$(SWIFT) package --package-path=$(swift_root)/lang  \
		init --type=executable --name=lang

$(swift_lang_binout): $(swift_lang_package)                 \
                      $(swift_root)/lang/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/lang $(swift_build_opt)



# foundation
swift_foundation_package := $(swift_root)/foundation/Package.swift
swift_foundation_binout := $(swift_root)/foundation/debug/foundation

swift_foundation: $(swift_foundation_binout)
swift_foundation_test: swift_foundation
	$(SWIFT) run --package-path=$(swift_root)/foundation
swift_foundation_clean:
	$(SWIFT) run --package-path=$(swift_root)/foundation

$(swift_foundation_package):
	$(SWIFT) package --package-path=$(swift_root)/foundation  \
		init --type=executable --name=foundation

$(swift_foundation_binout): $(swift_foundation_package)                 \
                      $(swift_root)/foundation/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/foundation $(swift_build_opt)



# os
swift_os_package := $(swift_root)/os/Package.swift
swift_os_binout := $(swift_root)/os/debug/os

swift_os: $(swift_os_binout)
swift_os_test: swift_os
	$(SWIFT) run --package-path=$(swift_root)/os

$(swift_os_package):
	$(SWIFT) package --package-path=$(swift_root)/os  \
		init --type=executable --name=os

$(swift_os_binout): $(swift_os_package)                 \
                    $(swift_root)/os/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/os




# eof
