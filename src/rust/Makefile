#
# ./configure --has-rust
# make clean test
#


rust: rust_hi                                   \
      rust_libc
rust_test: rust_hi_test                         \
           rust_libc_test


# env
rust_prefix := rust
RUSTC := $(shell which rustc)
CARGO := $(shell which cargo)


# hi
rust_hi_cargo := $(rust_root)/hi/Cargo.toml
rust_hi_binout := $(bin_path)/$(rust_prefix)_hi$(bin_ext)


rust_hi: $(rust_hi_binout)
rust_hi_test: rust_hi
	$(rust_hi_binout)

$(rust_hi_cargo): $(RUSTC)
	$(CARGO) new $(rust_root)/hi

$(rust_hi_binout): $(rust_hi_cargo)             \
                   $(rust_root)/hi/src/main.rs
	$(CARGO) build                                \
		--manifest-path $<                          \
		-Z unstable-options                         \
    --out-dir $(bin_path)

# libc
rust_libc_binout := $(bin_path)/$(rust_prefix)_libc$(bin_ext)

rust_libc: $(rust_libc_binout)
rust_libc_test: rust_libc
	$(rust_libc_binout)

$(rust_libc_binout): $(rust_root)/libc/Cargo.toml   \
                     $(rust_root)/libc/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --out-dir $(bin_path)


