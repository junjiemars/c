#include "norstd.h"
#include <stdio.h>

struct conf_s {
  int name;
  char *label;
} conf_s;

void
test_sysconf(void) {
  struct conf_s conf[] = {
#if defined (DARWIN)
    { _SC_ARG_MAX, _txt_(_SC_ARG_MAX) },
    { _SC_CHILD_MAX, _txt_(_SC_CHILD_MAX) },
    { _SC_CLK_TCK, _txt_(_SC_CLK_TCK) },
    { _SC_IOV_MAX, _txt_(_SC_IOV_MAX) },
    { _SC_NGROUPS_MAX, _txt_(_SC_NGROUPS_MAX) },
    { _SC_NPROCESSORS_CONF, _txt_(_SC_NPROCESSORS_CONF) },
    { _SC_NPROCESSORS_ONLN, _txt_(_SC_NPROCESSORS_ONLN) },
    { _SC_OPEN_MAX, _txt_(_SC_OPEN_MAX) },
    { _SC_PAGESIZE, _txt_(_SC_PAGESIZE) },
    { _SC_STREAM_MAX, _txt_(_SC_STREAM_MAX) },
    { _SC_TZNAME_MAX, _txt_(_SC_TZNAME_MAX) },
    { _SC_JOB_CONTROL, _txt_(_SC_JOB_CONTROL) },
    { _SC_SAVED_IDS, _txt_(_SC_SAVED_IDS) },
    { _SC_VERSION, _txt_(_SC_VERSION) },
    { _SC_BC_BASE_MAX, _txt_(_SC_BC_BASE_MAX) },
    { _SC_BC_DIM_MAX, _txt_(_SC_BC_DIM_MAX) },
    { _SC_BC_SCALE_MAX, _txt_(_SC_BC_SCALE_MAX) },
    { _SC_BC_STRING_MAX, _txt_(_SC_BC_STRING_MAX) },
    { _SC_COLL_WEIGHTS_MAX, _txt_(_SC_COLL_WEIGHTS_MAX) },
    { _SC_EXPR_NEST_MAX, _txt_(_SC_EXPR_NEST_MAX) },
    { _SC_LINE_MAX, _txt_(_SC_LINE_MAX) },
    { _SC_RE_DUP_MAX, _txt_(_SC_RE_DUP_MAX) },
    { _SC_2_VERSION, _txt_(_SC_2_VERSION) },
    { _SC_2_C_BIND, _txt_(_SC_2_C_BIND) },
    { _SC_2_C_DEV, _txt_(_SC_2_C_DEV) },
    { _SC_2_CHAR_TERM, _txt_(_SC_2_CHAR_TERM) },
    { _SC_2_FORT_DEV, _txt_(_SC_2_FORT_DEV) },
    { _SC_2_FORT_RUN, _txt_(_SC_2_FORT_RUN) },
    { _SC_2_LOCALEDEF, _txt_(_SC_2_LOCALEDEF) },
    { _SC_2_SW_DEV, _txt_(_SC_2_SW_DEV) },
    { _SC_2_UPE, _txt_(_SC_2_UPE) },
    { _SC_PHYS_PAGES, _txt_(_SC_PHYS_PAGES) },
#endif
  };
  for (size_t i = 0; i < sizeof(conf)/sizeof(struct conf_s); i++) {
    fprintf (stdout, "%s = 0x%lX\n", conf[i].label, sysconf(conf[i].name));
  }
}

int
main(void) {
  test_sysconf();
  return 0;
}
