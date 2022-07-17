BEGIN {
    FS = ","

    print "#include <signal.h>"
    print

    print "char *strsigno(int);"
    print
    print "char *strsigno(int signo)"
    print "{"
    print "  static char *ss[] = "
    print "    { \"\", "
}

{
    printf("    \"%s\",\n", $1);
}

END {
    print "  };"
    print "  if (signo < (int)(sizeof(ss)/sizeof(*ss)))"
    print "    {"
    print "      return ss[signo];"
    print "    }"
    print "  return 0;"
    print "}"
}
