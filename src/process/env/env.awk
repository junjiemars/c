BEGIN {
    FS = ","

    print "#include <stdio.h>"
    print "#include <stdlib.h>"
    print "\n"

    print "int main(void)"
    print "{"
}


{
    print "  printf(\"" $1 "=%s  #%s (" $2 ")\\n\", " "getenv(\"" $1 "\"),"
    print "         " $3 ");"
}


END {
    print ""
    print "  return 0;"
    print "}"
}
