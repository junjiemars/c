#
# ./configure --has-rust
# make clean test
#


rust: rust_hi                                   \
      rust_libc                                 \
      rust_game                                 \
      rust_owner                                \
      rust_generic                              \
      rust_error                                \
      rust_grep                                 \
      rust_io                                   \
      rust_iter                                 \
      rust_lib                                  \
      rust_macro                                \
      rust_module                               \
      rust_unsafe
rust_test: rust_hi_test                         \
           rust_libc_test                       \
           rust_game_test                       \
           rust_owner_test                      \
           rust_generic_test                    \
           rust_error_test                      \
           rust_grep_test                       \
           rust_io_test                         \
           rust_iter_test                       \
           rust_lib_test                        \
           rust_macro_test                      \
           rust_module_test                     \
           rust_unsafe_test


# env
rust_prefix := rust
RUSTC := $(has_rustc)
CARGO := $(has_cargo)
cargo_target_dir := $(CURDIR)/$(tmp_path)


# hi
rust_hi_cargo := $(rust_root)/hi/Cargo.toml
rust_hi_binout := $(bin_path)/$(rust_prefix)_hi$(bin_ext)


rust_hi: $(rust_hi_binout)
rust_hi_test: rust_hi
	size $(rust_hi_binout)
	$(rust_hi_binout)

$(rust_hi_cargo): $(RUSTC)
	$(CARGO) new --bin $(rust_prefix)_hi $(rust_root)/hi

$(rust_hi_binout): $(rust_hi_cargo)             \
                   $(rust_root)/hi/src/main.rs
	$(CARGO) build                                \
		--manifest-path $<                          \
		-Z unstable-options                         \
    --out-dir $(bin_path)

# libc
rust_libc_cargo := $(rust_root)/libc/Cargo.toml
rust_libc_binout := $(bin_path)/$(rust_prefix)_libc$(bin_ext)

rust_libc: $(rust_libc_binout)
rust_libc_doc: $(rust_libc_cargo)
	-$(CARGO) doc --open --manifest-path $<

rust_libc_test: rust_libc
	$(rust_libc_binout)

$(rust_libc_binout): $(rust_libc_cargo)             \
                     $(rust_root)/libc/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --out-dir $(bin_path)                       \
    --verbose


# game
rust_game_cargo := $(rust_root)/game/Cargo.toml
rust_game_binout := $(bin_path)/$(rust_prefix)_game$(bin_ext)

rust_game: $(rust_game_binout)
rust_game_doc: $(rust_game_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_game_test: rust_game
	echo "Q" | $(rust_game_binout)

$(rust_game_binout): $(rust_game_cargo)             \
                     $(rust_root)/game/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --out-dir $(bin_path)

# owner
rust_owner_cargo := $(rust_root)/owner/Cargo.toml
rust_owner_binout := $(bin_path)/$(rust_prefix)_owner$(bin_ext)

rust_owner: $(rust_owner_binout)
rust_owner_doc: $(rust_owner_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_owner_test: rust_owner
	$(rust_owner_binout)

$(rust_owner_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_owner $(rust_root)/owner

$(rust_owner_binout): $(rust_owner_cargo)             \
                      $(rust_root)/owner/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)


# generic
rust_generic_cargo := $(rust_root)/generic/Cargo.toml
rust_generic_binout := $(bin_path)/$(rust_prefix)_generic$(bin_ext)

rust_generic: $(rust_generic_binout)
rust_generic_doc: $(rust_generic_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_generic_test: rust_generic
	$(rust_generic_binout)

$(rust_generic_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_generic $(rust_root)/generic

$(rust_generic_binout): $(rust_generic_cargo)             \
                        $(rust_root)/generic/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)

# error
rust_error_cargo := $(rust_root)/error/Cargo.toml
rust_error_binout := $(bin_path)/$(rust_prefix)_error$(bin_ext)

rust_error: $(rust_error_binout)
rust_error_doc: $(rust_error_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_error_test: rust_error
	-$(shell RUST_BACKTRACE=1 $(rust_error_binout))

$(rust_error_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_error $(rust_root)/error

$(rust_error_binout): $(rust_error_cargo)             \
                        $(rust_root)/error/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)

# grep
rust_grep_cargo := $(rust_root)/grep/Cargo.toml
rust_grep_binout := $(bin_path)/$(rust_prefix)_grep$(bin_ext)

rust_grep: $(rust_grep_binout)
rust_grep_doc: $(rust_grep_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_grep_test: $(rust_grep_cargo)              \
                rust_grep
	$(CARGO) test --manifest-path $<
rust_grep_run: rust_grep
	-$(rust_grep_binout)
	$(rust_grep_binout) use $(rust_root)/grep/src/main.rs

$(rust_grep_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_grep $(rust_root)/grep

$(rust_grep_binout): $(rust_grep_cargo)             \
                     $(rust_root)/grep/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)


# io
rust_io_cargo := $(rust_root)/io/Cargo.toml
rust_io_binout := $(bin_path)/$(rust_prefix)_io$(bin_ext)

rust_io: $(rust_io_binout)
rust_io_doc: $(rust_io_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_io_test: rust_io
	$(rust_io_binout)

$(rust_io_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_io $(rust_root)/io

$(rust_io_binout): $(rust_io_cargo)             \
                   $(rust_root)/io/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)

# iter
rust_iter_cargo := $(rust_root)/iter/Cargo.toml
rust_iter_binout := $(bin_path)/$(rust_prefix)_iter$(bin_ext)

rust_iter: $(rust_iter_binout)
rust_iter_doc: $(rust_iter_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_iter_test: rust_iter
	$(rust_iter_binout)

$(rust_iter_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_iter $(rust_root)/iter

$(rust_iter_binout): $(rust_iter_cargo)             \
                     $(rust_root)/iter/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)


# lib
rust_lib_cargo := $(rust_root)/lib/Cargo.toml
rust_lib_rlib := lib$(rust_prefix)_lib.rlib
rust_lib_binout := $(lib_path)/$(rust_lib_rlib)

rust_lib: $(rust_lib_binout)
rust_lib_doc: $(rust_lib_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_lib_test: rust_lib
	size $(rust_lib_binout)

$(rust_lib_cargo): $(CARGO)
	$(CARGO) new --lib --name $(rust_prefix)_lib $(rust_root)/lib

$(rust_lib_binout): $(rust_lib_cargo)             \
                    $(rust_root)/lib/src/lib.rs
	$(CARGO) build --lib                          \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)
	@cp $(cargo_target_dir)/debug/$(rust_lib_rlib) $@


# macro
rust_macro_cargo := $(rust_root)/macro/Cargo.toml
rust_macro_binout := $(bin_path)/$(rust_prefix)_macro$(bin_ext)

rust_macro: $(rust_macro_binout)
rust_macro_doc: $(rust_macro_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_macro_test: rust_macro
	$(rust_macro_binout)

$(rust_macro_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_macro $(rust_root)/macro

$(rust_macro_binout): $(rust_macro_cargo)             \
                      $(rust_root)/macro/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)



# module
rust_module_cargo := $(rust_root)/module/Cargo.toml
rust_module_binout := $(bin_path)/$(rust_prefix)_module$(bin_ext)

rust_module: $(rust_module_binout)
rust_module_doc: $(rust_module_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_module_test: rust_module
	$(rust_module_binout)

$(rust_module_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_module $(rust_root)/module

$(rust_module_binout): $(rust_module_cargo)             \
                       $(rust_root)/module/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)


# unsafe
rust_unsafe_cargo := $(rust_root)/unsafe/Cargo.toml
rust_unsafe_binout := $(bin_path)/$(rust_prefix)_unsafe$(bin_ext)

rust_unsafe: $(rust_unsafe_binout)
rust_unsafe_doc: $(rust_unsafe_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_unsafe_test: rust_unsafe
	$(rust_unsafe_binout)

$(rust_unsafe_cargo): $(CARGO)
	$(CARGO) new --bin --name $(rust_prefix)_unsafe $(rust_root)/unsafe

$(rust_unsafe_binout): $(rust_unsafe_cargo)             \
                       $(rust_root)/unsafe/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)
