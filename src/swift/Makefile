# -*- mode:makefile-gmake -*-
#
# ./configure --has-swift
#
# make clean test
#
# https://developer.apple.com/library/archive/documentation/Porting/Conceptual/PortingUnix/intro/intro.html
#
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

swift_build := debug
ifeq ($(NM_BUILD),YES)
swift_build := release
endif




# hi
swift_hi_package := $(swift_root)/hi/Package.swift
swift_hi_binout := $(swift_root)/hi/.build/$(swift_build)/hi

swift_hi: $(swift_hi_binout)
swift_hi_test: swift_hi
	$(swift_hi_binout)
swift_hi_clean:
	$(SWIFT) package --package-path=$(swift_root)/hi clean

$(swift_hi_package):
	$(SWIFT) package --package-path=$(swift_root)/hi \
		init --type=executable --name=hi

$(swift_hi_binout): $(swift_hi_package) \
                    $(swift_root)/hi/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/hi -c $(swift_build)



# lang
swift_lang_package := $(swift_root)/lang/Package.swift
swift_lang_binout := $(swift_root)/lang/.build/$(swift_build)/lang

swift_lang: $(swift_lang_binout)
swift_lang_test: swift_lang
	$(swift_lang_binout)
swift_lang_clean:
	$(SWIFT) package --package-path=$(swift_root)/lang clean

$(swift_lang_package):
	$(SWIFT) package --package-path=$(swift_root)/lang \
		init --type=executable --name=lang

$(swift_lang_binout): $(swift_lang_package) \
                      $(swift_root)/lang/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/lang -c $(swift_build)



# foundation
swift_foundation_package := $(swift_root)/foundation/Package.swift
swift_foundation_binout := $(swift_root)/foundation/.build/$(swift_build)/foundation

swift_foundation: $(swift_foundation_binout)
swift_foundation_test: swift_foundation
	$(swift_foundation_binout)
swift_foundation_clean:
	$(SWIFT) package --package-path=$(swift_root)/foundation clean

$(swift_foundation_package):
	$(SWIFT) package --package-path=$(swift_root)/foundation \
		init --type=executable --name=foundation

$(swift_foundation_binout): $(swift_foundation_package) \
                      $(swift_root)/foundation/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/foundation -c $(swift_build)



# os
swift_os_package := $(swift_root)/os/Package.swift
swift_os_binout := $(swift_root)/os/.build/$(swift_build)/os

swift_os: $(swift_os_binout)
swift_os_test: swift_os
	$(swift_os_binout)
swift_os_clean:
	$(SWIFT) package --package-path=$(swift_root)/os clean

$(swift_os_package):
	$(SWIFT) package --package-path=$(swift_root)/os \
		init --type=executable --name=os

$(swift_os_binout): $(swift_os_package) \
                    $(swift_root)/os/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/os -c $(swift_build)




# eof
