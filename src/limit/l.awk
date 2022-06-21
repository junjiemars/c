BEGIN {
    FS = ","
    print "#include <stdio.h>"
    print "#include <unistd.h>"
    print "#include <limits.h>"
    print "\n"
    
    print "#define STR(s)   #s"
    print "#define ULL(u)   (unsigned long long) (u)"
    print "#define SLL(s)   (long long) (s)"
    print "#define INT(i)   (int) (i)"
    print ""
    print "#define FMT_ULL  \"%-35s%-24llu\\n\""
    print "#define FMT_SLL  \"%-35s%-24lld\\n\""
    print "#define FMT_INT  \"%-35s%-24d\\n\""
    print "#define FMT_SYM  \"%-35s(no symbol)\\n\""
    print "\n"
    print "int main(void) \n{\n"
}
{
    printf("#if defined(%s)\n", $1)
    
    if ($3 == null) $3 = $1

    switch ($2) {
    case "ULL":
        printf("  printf(FMT_ULL, STR(%s), ULL(%s));\n", $1, $3)
        break
    case "SLL":
        printf("  printf(FMT_ULL, STR(%s), SLL(%s));\n", $1, $3)
        break
    case "INT":
        printf("  printf(FMT_INT, STR(%s), INT(%s));\n", $1, $3)
        break
    }

    printf("#else\n")
    printf("  printf(FMT_SYM, STR(%s));\n", $1)
    print "#endif\n"
};

END {
    print "\n  return 0;\n}"
}
