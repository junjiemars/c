BEGIN {
    FS = ","

    print "#include <stdio.h>"
    print "#include <stdlib.h>"
    print "#include <sys/resource.h>"
    print "\n"

    print "#define STR(s)   #s"
    print "#define FMT_SYM  \"%-18s (no symbol)\\n\""
    print "\n"

    print "static void print_rlimit(const char *, int, const char *);"
    print "\n"

    print "int"
    print "main(void)"
    print "{"
}

{
    printf("#if defined(%s)\n", $1)
    printf("  print_rlimit(STR(%s), %s, %s);\n", $1, $1, $2)
    printf("#else\n")
    printf("  printf(FMT_SYM, STR(%s));\n", $1)
    printf("#endif\n\n")
};

END {
    # main
    print "  return 0;"
    print "}\n"

    # print_rlimit
    print "void"
    print "print_rlimit(const char *name, int res, const char *des)"
    print "{"
    print "  struct rlimit r;"
    print ""
    print "  if (getrlimit(res, &r) < 0)"
    print "    {"
    print "      exit(EXIT_FAILURE);"
    print "    }"
    print ""
    print "  printf(\"%-14s  \", name);"
    print "  if (r.rlim_cur == RLIM_INFINITY)"
    print "    {"
    print "      printf(\"(infinite) \");"
    print "    }"
    print "  else"
    print "    {"
    print "      printf(\"%10lld \", (long long) r.rlim_cur);"
    print "    }"
    print ""
    print "  if (r.rlim_max == RLIM_INFINITY)"
    print "    {"
    print "      printf(\"(infinite)  \");"
    print "    }"
    print "  else"
    print "    {"
    print "      printf(\"%10lld  \", (long long) r.rlim_max);"
    print "    }"
    print "  printf(\"#%s\\n\", des);"
    print "}"
}
