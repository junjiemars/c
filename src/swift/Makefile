#
# ./configure --has-swift
# make clean test
#


swift: swift_hi                                 \
       swift_os

swift_test: swift_hi_test                       \
            swift_os_test

# env
swift_prefix := swift
SWIFTC := $(has_swiftc)
SWIFT := $(has_swift)

swift_build_opt :=
ifeq ($(NM_BUILD),YES)
swift_build_opt := -c release
endif


# hi
swift_hi_package := $(swift_root)/hi/Package.swift
swift_hi_binout := $(swift_root)/hi/debug/hi

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
	$(SWIFT) build --package-path=$(swift_root)/hi $(swift_build_opt)



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
