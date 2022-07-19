BEGIN {
    FS = ","

    ss = ""

    print "#include <signal.h>"
    print ""
    print "char *strsigno(int);"
    print ""
    print ""
}

{
    ss = ss sprintf("      \"%s\",\n", $1)
}

END {
    print "char *"
    print "strsigno(int signo)"
    print "{"
    print "  static char *ss[] = "
    print "    {"
    print ss
    print "    };"
    print ""
    print "  if (signo < (int) (sizeof(ss)/sizeof(*ss)))"
    print "    {"
    print "      return ss[signo];"
    print "    }"
    print "  return 0;"
    print "}"
}
