BEGIN {
    FS = ","

    print "#include \"sig2str.h\""
    print "#include <signal.h>"
    print "#include <string.h>"
    print "#include <errno.h>"
    print ""

    print "#if !defined(_str_)"
    print "#define _str_(x)  #x"
    print "#endif"
    print ""

    print "#if !defined(_nof_)"
    print "#define _nof_(x)  sizeof(x)/sizeof(*(x))"
    print "#endif"
    print ""

    print "typedef struct signo_s"
    print "{"
    print "  unsigned int   signo;"
    print "  char          *name;"
    print "} signo_s;"
    print ""

    print "static signo_s ss[] = "
    print "  {"
    print "    {.signo = 0, .name = \"Null\"},"
}

{
    printf "    {.signo = SIG%s, .name = _str_(%s)},\n", $1, $1
}

END {
    print "  };"
    print ""

    print "int sig2str(int signo, char *str)"
    print "{"
    print "  if (0 <= signo && (size_t) signo < _nof_(ss))"
    print "    {"
    print "      strncpy(str, ss[signo].name, SIG2STR_MAX);"
    print "      return 0;"
    print "    }"
    print ""
    print "  errno = EINVAL;"
    print "  return -1;"
    print "}"
    print ""

    print "int str2sig(const char *str, int *signo)"
    print "{"
    print "  if (str != NULL)"
    print "    {"
    print "      for (size_t i = 0; i < _nof_(ss); i++)"
    print "        {"
    print "          if (strncmp(ss[i].name, str, SIG2STR_MAX) == 0)"
    print "            {"
    print "              *signo = ss[i].signo;"
    print "              return 0;"
    print "            }"
    print "        }"
    print "    }"
    print ""
    print "  errno = EINVAL;"
    print "  return -1;"
    print "}"
    print ""

}
