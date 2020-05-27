#include "norstd.h"
#include <stdio.h>

struct conf_s {
  int name;
  char *label;
};

static struct conf_s confs[] = {
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
#elif defined(LINUX)
    { _SC_ARG_MAX, _txt_(_SC_ARG_MAX) },
    { _SC_CHILD_MAX, _txt_(_SC_CHILD_MAX) },
    {  _SC_HOST_NAME_MAX, _txt_(_SC_HOST_NAME_MAX) },
    {  _SC_LOGIN_NAME_MAX, _txt_(_SC_LOGIN_NAME_MAX) },
    {  _SC_NGROUPS_MAX, _txt_(_SC_NGROUPS_MAX) },
    {  _SC_CLK_TCK,   _txt_(_SC_CLK_TCK) },
    {  _SC_OPEN_MAX, _txt_(_SC_OPEN_MAX) },
    {  _SC_PAGESIZE, _txt_(_SC_PAGESIZE) },
    {  _SC_RE_DUP_MAX, _txt_(_SC_RE_DUP_MAX) },
    {  _SC_STREAM_MAX, _txt_(_SC_STREAM_MAX) },
    {  _SC_SYMLOOP_MAX, _txt_(_SC_SYMLOOP_MAX) },
    {  _SC_TTY_NAME_MAX, _txt_(_SC_TTY_NAME_MAX) },
    {  _SC_TZNAME_MAX, _txt_(_SC_TZNAME_MAX) },
    {  _SC_BC_BASE_MAX, _txt_(_SC_BC_BASE_MAX) },
    {  _SC_BC_DIM_MAX, _txt_(_SC_BC_DIM_MAX) },
    {  _SC_BC_SCALE_MAX, _txt_(_SC_BC_SCALE_MAX) },
    {  _SC_BC_STRING_MAX, _txt_(_SC_BC_STRING_MAX) },
    {  _SC_COLL_WEIGHTS_MAX, _txt_(_SC_COLL_WEIGHTS_MAX) },
    {  _SC_EXPR_NEST_MAX, _txt_(_SC_EXPR_NEST_MAX) },
    {  _SC_LINE_MAX, _txt_(_SC_LINE_MAX) },
    {  _SC_RE_DUP_MAX, _txt_(_SC_RE_DUP_MAX) },
    {  _SC_2_VERSION, _txt_(_SC_2_VERSION) },
    {  _SC_2_C_DEV, _txt_(_SC_2_C_DEV) },
    {  _SC_2_FORT_DEV, _txt_(_SC_2_FORT_DEV) },
    {  _SC_2_FORT_RUN, _txt_(_SC_2_FORT_RUN) },
    {  _SC_2_LOCALEDEF, _txt_(_SC_2_LOCALEDEF) },
    {  _SC_2_SW_DEV, _txt_(_SC_2_SW_DEV) },
    {  _SC_PHYS_PAGES, _txt_(_SC_PHYS_PAGES) },
    {  _SC_AVPHYS_PAGES, _txt_(_SC_AVPHYS_PAGES) },
    {  _SC_NPROCESSORS_CONF, _txt_(_SC_NPROCESSORS_CONF) },
    {  _SC_NPROCESSORS_ONLN, _txt_(_SC_NPROCESSORS_ONLN) },
#else
    { -1, 0, }
#endif
};

void
test_sysconf(void) {
  if (-1 == confs[0].name) {
    fprintf(stdout, "<empty>\n");
    return;
  }
  for (size_t i = 0; i < sizeof(confs)/sizeof(struct conf_s); i++) {
    fprintf (stdout, "%s = #x%lX\n", confs[i].label, sysconf(confs[i].name));
  }
}

int
main(void) {
  test_sysconf();
  return 0;
}
