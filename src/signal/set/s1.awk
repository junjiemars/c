BEGIN {
    FS = ","

    print "#include <unistd.h>"
    print "#include <signal.h>"
    print "#include <stdio.h>"
    print

    print "#define STR(s)   #s"
    print "#define YES(s)   (s) ? \"yes\" : \"no\""
    print ""
    print "#define FMT_SIG  \"%-16s %04i, %-4s\\n\""
    print "#define FMT_SYM  \"%-16s (no symbol)\\n\""
    print
    print
    print "int main(void)"
    print "{"
    print "  int       rc;"
    print "  sigset_t  oset;"
    print
    print "  sigprocmask(0, NULL, &oset);"
    print
}

(/^[ \t]*$/) {

    print ""
}

(/^[ \t]*#.*$/) {

    if ($1 ~ /^[ \t]*#[ \t]*?$/) {
        print ""
    } else {
        comment = $1
        sub(/^[ \t]*?#[ \t]*?/, null, comment)
        printf("/* %s */\n", comment)
    }
}

! (/^[ \t]*$/ || /^[ \t]*#.*$/) {

    printf("#if defined(%s)\n", $1)

    print  "  {"
    printf("     rc = sigismember(&oset, %s);\n", $1)
    printf("     printf(FMT_SIG, STR(%s), %s, YES(%s));\n", $1, $1, $1)
    print  "  }"

    printf("#else\n")
    printf("  printf(FMT_SYM, STR(%s));\n", $1)
    print "#endif\n"
};

END {
    print "\n  return 0;\n}"
}
