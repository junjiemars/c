#
# ./configure --has-swift
# make clean test
#


swift: swift_hi

swift_test: swift_hi_test


# env
swift_prefix := swift
SWIFTC := $(has_swiftc)
SWIFT := $(has_swift)

swift_build_opt :=

# hi
swift_hi_package := $(swift_root)/hi/Package.swift
swift_hi_binout := $(swift_root)/hi/debug/hi

swift_hi: $(swift_hi_binout)
swift_hi_test: swift_hi
	$(SWIFT) run --package-path=$(swift_root)/hi

$(swift_hi_package):
	$(SWIFT) package --package-path=$(swift_root)/hi  \
		init --type=executable --name=$(swift_hi_name)

$(swift_hi_binout): $(swift_hi_package)                 \
                    $(swift_root)/hi/Sources/main.swift
	$(SWIFT) build --package-path=$(swift_root)/hi




# eof
