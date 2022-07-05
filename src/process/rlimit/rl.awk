BEGIN {
    FS = ","

    print "#include <stdio.h>"
    print "#include <sys/resource.h>"
    print "\n"

    print "#define STR(s)   #s"
    print "#define FMT_SYM  \"%-18s (no symbol)\\n\""
    print "\n"
    print "int main(void)"
    print "{"
    print "  struct rlimit r;\n"
}

(/^[ \t]*$/) {

    print ""
}

(/^[ \t]*#.*$/) {

    # match($0, /^\s*#\s*(.*?)\s*$/, ms)
    # if (ms[1] ~ /^\s*$/)
    #     print ""
    # else
    #     printf("/* %s */\n", ms[1])

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
    print "{"

    printf("  getrlimit(%s, &r);\n", $1)

    print  "  printf(\"%-18s cur: 0x%016lx, max: 0x%016lx\\n\", "
    printf("         STR(%s),\n", $1)
    print  "         (size_t) r.rlim_cur,"
    print  "         (size_t) r.rlim_max);"

    print  "}"

    printf("#else\n")
    printf("  printf(FMT_SYM, STR(%s));\n", $1)
    print "#endif\n"
};

END {
    print "  return 0;"
    print "}"
}
