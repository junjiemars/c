BEGIN {
    FS = ","

    print "#ifndef _SYS_SIGNAME_H_"
    print "#define _SYS_SIGNAME_H_"
    print ""

    print "#include <signal.h>"
    print ""

    print "#if !defined(_str_)"
    print "#define _str_(x)  #x"
    print "#endif"
    print ""

    print "typedef struct signo_s"
    print "{"
    print "  unsigned int   signo;"
    print "  char          *name;"
    print "} signo_s;"
    print ""

    print "static signo_s sys_signame1[] = "
    print "  {"
    print "    {.signo = 0, .name = \"Null\"},"
}

{
    printf "    {.signo = %s, .name = _str_(%s)},\n", $1, $1
}

END {
    print "  };"
    print ""
    print "#endif"
}
