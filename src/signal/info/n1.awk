BEGIN {
    FS = ","

    print "#include <signal.h>"
    print

    print "char *strsig(int);"
    print
    print "char *strsig(int signo)"
    print "{"
    print "  static char *ss[] = { \"\", "
}

{
    printf("    \"%s\",\n", $1);
}

END {
    print "  };"
    print "  return ss[signo];"
    print "}"
}
