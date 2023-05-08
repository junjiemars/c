#
# ./configure --has-rust
# make clean test
#


rust: rust_attr                                 \
      rust_box                                  \
      rust_enum                                 \
      rust_error                                \
      rust_game                                 \
      rust_generic                              \
      rust_grep                                 \
      rust_hi                                   \
      rust_gtk                                  \
      rust_iced                                 \
      rust_io                                   \
      rust_iter                                 \
      rust_lang                                 \
      rust_lib                                  \
      rust_libc                                 \
      rust_macro                                \
      rust_mem                                  \
      rust_min                                  \
      rust_module                               \
      rust_owner                                \
      rust_rest                                 \
      rust_unsafe                               \
      rust_websrv                               \
      rust_ws

rust_test: rust_attr_test                       \
           rust_box_test                        \
           rust_enum_test                       \
           rust_error_test                      \
           rust_game_test                       \
           rust_generic_test                    \
           rust_grep_test                       \
           rust_hi_test                         \
           rust_gtk_test                        \
           rust_iced_test                       \
           rust_io_test                         \
           rust_iter_test                       \
           rust_lang_test                       \
           rust_lib_test                        \
           rust_libc_test                       \
           rust_macro_test                      \
           rust_mem_test                        \
           rust_min_test                        \
           rust_module_test                     \
           rust_owner_test                      \
           rust_rest_test                       \
           rust_unsafe_test                     \
           rust_websrv_test                     \
           rust_ws_test


# env
rust_prefix := rust
RUSTC := $(has_rustc)
CARGO := $(has_cargo)
RUSTFMT := $(has_rustfmt)


rust_tags_opt := $(has_rust_ctags)
rust_tags_file := $(CURDIR)/.rust.tags
rust_tags_sub_file := $(rust_root)/.rust.sub.tags
rust_src_dir := $(has_rust_src)
rust_fmt_file := $(rust_root)/rustfmt.toml
cargo_target_dir := $(CURDIR)/$(tmp_path)
analyzer_project_json := $(CURDIR)/rust-project.json

rust_build_opt :=
cargo_out_dir := "$(cargo_target_dir)/debug"
ifeq ($(NM_BUILD),YES)
rust_build_opt := --release --profile=release
cargo_out_dir := "$(cargo_target_dir)/release"
endif

rust_dbg_dummy_dir :=
ifneq ($(has_rust_hash),)
rust_dbg_dummy_dir := "/build/$(has_rust_hash)"
endif

rust_tags: $(rust_tags_file)
rust_sub_tags: $(rust_tags_sub_file)
rust_fmt: $(rust_fmt_file)

$(rust_tags_file): $(rust_tags_opt) $(rust_src_dir)
	ctags -R -e -a -o $@ --options="$<" $(rust_src_dir)

$(rust_tags_sub_file): $(rust_tags_opt)
	ctags -R -e -a -o $@ --options="$<" $(CURDIR)/$(rust_root)

$(rust_fmt_file): $(RUSTFMT)
	$(RUSTFMT) --print-config default \
    | sed -e 's#max_width = .*#max_width = 79#g' > $@

rust_lldb_source_map: $(rust_src_dir)
	echo "settings set target.source-map $(rust_dbg_dummy_dir) $(rust_src_dir)"
rust_gdb_source_map:
	echo "set substitute-path $(rust_dbg_dummy_dir) $(rust_src_dir)"




# attr
rust_attr_cargo := $(rust_root)/attr/Cargo.toml
rust_attr_name := $(rust_prefix)_attr$(bin_ext)
rust_attr_binout := $(bin_path)/$(rust_attr_name)

rust_attr: $(rust_attr_binout)
rust_attr_test: rust_attr
	size $(rust_attr_binout)
	$(rust_attr_binout)

$(rust_attr_cargo):
	$(CARGO) new --bin --vcs=none --name=$(rust_attr_name) $(rust_root)/attr

$(rust_attr_binout): $(rust_attr_cargo)             \
                     $(rust_root)/attr/src/main.rs
	$(CARGO) build $(rust_build_opt)                      \
		--manifest-path $<                                  \
    --target-dir $(cargo_target_dir)                    \
	&& cp $(cargo_out_dir)/$(rust_attr_name) $(bin_path)



# hi
rust_hi_cargo := $(rust_root)/hi/Cargo.toml
rust_hi_name := $(rust_prefix)_hi$(bin_ext)
rust_hi_binout := $(bin_path)/$(rust_hi_name)

rust_hi: $(rust_hi_binout)
rust_hi_test: rust_hi
	size $(rust_hi_binout)
	$(rust_hi_binout)

$(rust_hi_cargo):
	$(CARGO) new --bin --vcs=none --name=$(rust_hi_name) $(rust_root)/hi

$(rust_hi_binout): $(rust_hi_cargo)             \
                   $(rust_root)/hi/src/main.rs
	$(CARGO) build $(rust_build_opt)                    \
		--manifest-path $<                                \
    --target-dir $(cargo_target_dir)                  \
	&& cp $(cargo_out_dir)/$(rust_hi_name) $(bin_path)

# enum
rust_enum_cargo := $(rust_root)/enum/Cargo.toml
rust_enum_binout := $(bin_path)/$(rust_prefix)_enum$(bin_ext)

rust_enum: $(rust_enum_binout)
rust_enum_test: rust_enum
	echo "Q" | $(rust_enum_binout)

$(rust_enum_cargo):
	$(CARGO) new --bin --vcs=none --name=$(rust_prefix)_enum $(rust_root)/enum

$(rust_enum_binout): $(rust_enum_cargo)             \
                     $(rust_root)/enum/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    --target-dir $(cargo_target_dir)            \
    -Z unstable-options                         \
    --out-dir $(bin_path)




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
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)

# owner
rust_owner_cargo := $(rust_root)/owner/Cargo.toml
rust_owner_binout := $(bin_path)/$(rust_prefix)_owner$(bin_ext)

rust_owner: $(rust_owner_binout)
rust_owner_doc: $(rust_owner_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_owner_test: rust_owner
	$(rust_owner_binout)

$(rust_owner_cargo):
	$(CARGO) new --bin --name $(rust_prefix)_owner $(rust_root)/owner

$(rust_owner_binout): $(rust_owner_cargo)             \
                      $(rust_root)/owner/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)



# rest
rust_rest_name := $(rust_prefix)_rest
rust_rest_cargo := $(rust_root)/rest/Cargo.toml
rust_rest_binout := $(bin_path)/$(rust_rest_name)$(bin_ext)
# https://github.com/seanmonstar/warp/tree/master/examples

rust_rest: $(rust_rest_binout)
rust_rest_test: rust_rest
	$(rust_rest_binout)

$(rust_rest_cargo):
	$(CARGO) new --bin --vcs=none --name $(rust_prefix)_rest $(rust_root)/rest
	$(CARGO) add --manifest-path=$@ serde serde_json tokio warp uuid

$(rust_rest_binout): $(rust_rest_cargo)
	$(CARGO) build                                          \
		--manifest-path $<                                    \
    --target-dir $(cargo_target_dir)                      \
    && cp $(cargo_out_dir)/$(rust_rest_name)$(bin_ext) $@



# generic
rust_generic_cargo := $(rust_root)/generic/Cargo.toml
rust_generic_binout := $(bin_path)/$(rust_prefix)_generic$(bin_ext)

rust_generic: $(rust_generic_binout)
rust_generic_doc: $(rust_generic_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_generic_test: rust_generic
	$(rust_generic_binout)

$(rust_generic_cargo):
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

$(rust_error_cargo):
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
rust_grep_test: rust_grep_run

rust_grep_unit_test: $(rust_grep_cargo)         \
                     rust_grep
	$(CARGO) test                                 \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)

rust_grep_run: $(rust_grep_binout)
	-$<
	$< USE $(rust_root)/grep/src/main.rs
	IGNORE_CASE= $< USE $(rust_root)/grep/src/main.rs

$(rust_grep_cargo):
	$(CARGO) new --bin --name=$(rust_prefix)_grep $(rust_root)/grep

$(rust_grep_binout): $(rust_grep_cargo)             \
                     $(rust_root)/grep/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)


# gtk
rust_gtk_name := $(rust_prefix)_gtk
rust_gtk_cargo := $(rust_root)/gtk/Cargo.toml
rust_gtk_binout := $(bin_path)/$(rust_gtk_name)$(bin_ext)

ifneq ($(has_gtk_ver),)
rust_gtk: $(rust_gtk_binout)
rust_gtk_test: rust_gtk
	$(rust_gtk_binout)
else
rust_gtk:
	echo "#skip ..."
rust_gtk_test: rust_gtk
	echo "#skip ..."
endif

$(rust_gtk_cargo):
	$(CARGO) new --bin --name $(rust_prefix)_gtk $(rust_root)/gtk
	$(CARGO) tree --manifest-path $@ --prune gtk4                                 \
    $(CARGO) add gtk4 --manifest-path $@ --rename gtk --features $(has_gtk_ver)


$(rust_gtk_binout): $(rust_gtk_cargo)             \
                    $(rust_root)/gtk/src/main.rs
	$(CARGO) build                                          \
    --manifest-path $<                                    \
    --target-dir $(cargo_target_dir)                      \
    && cp $(cargo_out_dir)/$(rust_gtk_name)$(bin_ext) $@

# iced
rust_iced_name := $(rust_prefix)_iced
rust_iced_cargo := $(rust_root)/iced/Cargo.toml
rust_iced_binout := $(bin_path)/$(rust_iced_name)$(bin_ext)
# https://github.com/iced-rs/iced

rust_iced: $(rust_iced_binout)
rust_iced_test: rust_iced
	$(rust_iced_binout)

$(rust_iced_cargo):
	$(CARGO) new --bin --vcs=none --name $(rust_iced_name) $(rust_root)/iced
	$(CARGO) add --manifest-path=$@ iced

$(rust_iced_binout): $(rust_iced_cargo)
	$(CARGO) build $(rust_build_opt)                        \
    --manifest-path $<                                    \
    --target-dir $(cargo_target_dir)                      \
    && cp $(cargo_out_dir)/$(rust_iced_name)$(bin_ext) $@



# io
rust_io_cargo := $(rust_root)/io/Cargo.toml
rust_io_binout := $(bin_path)/$(rust_prefix)_io$(bin_ext)

rust_io: $(rust_io_binout)
rust_io_doc: $(rust_io_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_io_test: rust_io
	$(rust_io_binout)

$(rust_io_cargo):
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

$(rust_iter_cargo):
	$(CARGO) new --bin --name=$(rust_prefix)_iter $(rust_root)/iter

$(rust_iter_binout): $(rust_iter_cargo)             \
                     $(rust_root)/iter/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)




# lang
rust_lang_cargo := $(rust_root)/lang/Cargo.toml
rust_lang_binout := $(bin_path)/$(rust_prefix)_lang$(bin_ext)

rust_lang: $(rust_lang_binout)
rust_lang_doc: $(rust_lang_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_lang_test: rust_lang
	$(rust_lang_binout)

$(rust_lang_cargo):
	$(CARGO) new --bin --name=$(rust_prefix)_lang $(rust_root)/lang

$(rust_lang_binout): $(rust_lang_cargo)             \
                     $(rust_root)/lang/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    --target-dir $(cargo_target_dir)            \
    -Z unstable-options                         \
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
$(rust_lib_cargo):
	$(CARGO) new --lib --name $(rust_prefix)_lib $(rust_root)/lib

$(rust_lib_binout): $(rust_lib_cargo)             \
                    $(rust_root)/lib/src/lib.rs
	$(CARGO) build --lib                          \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)
	@cp $(cargo_target_dir)/debug/$(rust_lib_rlib) $@



# libc
rust_libc_cargo := $(rust_root)/libc/Cargo.toml
rust_libc_binout := $(bin_path)/$(rust_prefix)_libc$(bin_ext)

rust_libc: $(rust_libc_binout)
rust_libc_doc: $(rust_libc_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_libc_tree: $(rust_libc_cargo)
	$(CARGO) tree --manifest-path $<

rust_libc_test: rust_libc
	$(rust_libc_binout)

$(rust_libc_binout): $(rust_libc_cargo)             \
                     $(rust_root)/libc/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    --target-dir $(cargo_target_dir)            \
    -Z unstable-options                         \
    --out-dir $(bin_path)                       \



# macro
rust_macro_cargo := $(rust_root)/macro/Cargo.toml
rust_macro_binout := $(bin_path)/$(rust_prefix)_macro$(bin_ext)

rust_macro: $(rust_macro_binout)
rust_macro_doc: $(rust_macro_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_macro_test: rust_macro
	$(rust_macro_binout)

$(rust_macro_cargo):
	$(CARGO) new --bin --name=$(rust_prefix)_macro $(rust_root)/macro

$(rust_macro_binout): $(rust_macro_cargo)             \
                      $(rust_root)/macro/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    --target-dir $(cargo_target_dir)            \
    -Z unstable-options                         \
    --out-dir $(bin_path)



# mem
rust_mem_cargo := $(rust_root)/mem/Cargo.toml
rust_mem_binout := $(bin_path)/$(rust_prefix)_mem$(bin_ext)

rust_mem: $(rust_mem_binout)
rust_mem_doc: $(rust_mem_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_mem_test: rust_mem
	$(rust_mem_binout)

$(rust_mem_cargo):
	$(CARGO) new --bin --name=$(rust_prefix)_mem $(rust_root)/mem

$(rust_mem_binout): $(rust_mem_cargo)             \
                      $(rust_root)/mem/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    --target-dir $(cargo_target_dir)            \
    -Z unstable-options                         \
    --out-dir $(bin_path)



# min
rust_min_cargo := $(rust_root)/min/Cargo.toml
rust_min_binout := $(bin_path)/$(rust_prefix)_min$(bin_ext)
rust_min_profile ?= min

rust_min: $(rust_min_binout)
rust_min_test: rust_min
	size $(rust_min_binout)
	$(rust_min_binout)

$(rust_min_cargo):
	$(CARGO) new $(rust_root)/min

$(rust_min_binout): $(rust_min_cargo)             \
                    $(rust_root)/min/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    --profile $(rust_min_profile)               \
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

$(rust_module_cargo):
	$(CARGO) new --bin --name=$(rust_prefix)_module $(rust_root)/module

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

$(rust_unsafe_cargo):
	$(CARGO) new --bin --name $(rust_prefix)_unsafe $(rust_root)/unsafe

$(rust_unsafe_binout): $(rust_unsafe_cargo)             \
                       $(rust_root)/unsafe/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)


# box
rust_box_cargo := $(rust_root)/box/Cargo.toml
rust_box_binout := $(bin_path)/$(rust_prefix)_box$(bin_ext)

rust_box: $(rust_box_binout)
rust_box_doc: $(rust_box_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_box_test: rust_box
	$(rust_box_binout)

$(rust_box_cargo):
	$(CARGO) new --bin --name $(rust_prefix)_box $(rust_root)/box

$(rust_box_binout): $(rust_box_cargo)             \
                    $(rust_root)/box/src/main.rs
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)

# websrv
rust_websrv_cargo := $(rust_root)/websrv/Cargo.toml
rust_websrv_binout := $(bin_path)/$(rust_prefix)_websrv$(bin_ext)
rust_websrv_html := $(rust_root)/websrv/h.html

rust_websrv: $(rust_websrv_binout)
rust_websrv_doc: $(rust_websrv_cargo)
	-$(CARGO) doc --open --manifest-path $<
rust_websrv_test: rust_websrv
	size $(rust_websrv_binout)
	# RUST_BACKTRACE=1 $(rust_websrv_binout)

$(rust_websrv_cargo):
	$(CARGO) new --bin --name $(rust_prefix)_websrv $(rust_root)/websrv

$(rust_websrv_binout): $(rust_websrv_cargo)             \
                       $(rust_root)/websrv/src/main.rs  \
                       $(rust_websrv_html)
	$(CARGO) build                                \
    --manifest-path $<                          \
    -Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)
	@cp $(rust_websrv_html) $(bin_path)/


# ws : workspace
rust_ws_cargo := $(rust_root)/ws/Cargo.toml
rust_ws_binout := $(bin_path)/adder


rust_ws: $(rust_ws_binout)
rust_ws_test: rust_ws
	$(rust_ws_binout)

rust_ws_unit_test: $(rust_ws_cargo)             \
                   rust_ws
	$(CARGO) test                                 \
		--manifest-path $<                          \
		-Z unstable-options                         \
    --target-dir $(cargo_target_dir)


$(rust_ws_binout): $(rust_ws_cargo)
	$(CARGO) build $(rust_build_opt)              \
		--manifest-path $<                          \
		-Z unstable-options                         \
    --target-dir $(cargo_target_dir)            \
    --out-dir $(bin_path)



# eof
