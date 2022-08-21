#
# ./configure --has-rust
# make clean test
#


rust: rust_hi                                   \
      rust_libc                                 \
      rust_game                                 \
      rust_owner
rust_test: rust_hi_test                         \
           rust_libc_test                       \
           rust_game_test                       \
           rust_owner_test


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
