#
# ./configure --has-rust
# make clean test
#


rust: rust_hi
rust_test: rust_hi_test


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

# # c
# rust_c_binout := $(bin_path)/$(rust_prefix)_c$(bin_ext)
# rust_c_rust_binout := $(bin_path)/$(rust_prefix)_z0$(bin_ext)
# rust_c_rustout1 := $(bin_path)/$(rust_prefix)_z1$(bin_ext)
# rust_c_rustout2 := $(bin_path)/$(rust_prefix)_z2$(bin_ext)
# rust_c_rustout3 := $(bin_path)/$(rust_prefix)_z3$(bin_ext)
# rust_c_root := $(CURDIR)/$(rust_root)/c

# rust_c: $(rust_c_binout)                          \
#        $(rust_c_rust_binout)                      \
#        $(rust_c_rustout1)                         \
#        $(rust_c_rustout2)
# rust_c_test: rust_c_binout_test                   \
#             rust_c_rust_binout_test               \
#             rust_c_rustout1_test                  \
#             rust_c_rustout2_test                  \
#             rust_c_rustout3_test

# rust_c_binout_test: $(rust_c_binout)
# 	$<
# rust_c_rust_binout_test: $(rust_c_rust_binout)
# 	$<
# rust_c_rustout1_test: $(rust_c_rustout1)
# 	$<
# rust_c_rustout2_test: $(rust_c_rustout2)
# 	$<
# rust_c_rustout3_test: $(rust_c_rustout3)
# 	$<

# $(rust_c_binout): $(rust_root)/c/c.c              \
#                  $(rust_root)/c/m.c
# 	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# $(rust_c_rust_binout): $(rust_root)/c/c.c          \
#                      $(rust_root)/c/m.c
# 	$(RUST) cc $(CPPFLAGS) $(CFLAGS) $(INC) $^ -o $@


# $(rust_c_rustout1): $(rust_root)/c/build1.rust      \
#                   $(rust_root)/c/c.c             \
#                   $(rust_root)/c/m.c
# 	$(RUST) build                                  \
#     --build-file $(rust_c_root)/build1.rust       \
#     --cache-dir $(rust_cache_dir)                \
#     --prefix-exe-dir $(rust_prefix_exe_dir)

# $(rust_c_rustout2): $(rust_root)/c/build2.rust      \
#                   $(rust_root)/c/c.c             \
#                   $(rust_root)/c/m.rust
# 	$(RUST) build                                  \
#     --build-file $(rust_c_root)/build2.rust       \
#     --cache-dir $(rust_cache_dir)                \
#     --prefix-exe-dir $(rust_prefix_exe_dir)

# $(rust_c_rustout3): $(rust_root)/c/build3.rust      \
#                   $(rust_root)/c/c.rust           \
#                   $(rust_root)/c/m.c
# 	$(RUST) build                                  \
#     --build-file $(rust_c_root)/build3.rust       \
#     --cache-dir $(rust_cache_dir)                \
#     --prefix-exe-dir $(rust_prefix_exe_dir)


