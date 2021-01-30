??=include <_lang_.h>
??=include <stdio.h>

/*  
 * trigraphs(three-character groups) are parsed before comments and
 * string literals.
*/

int
main(int argc, char **argv)
??<
  _unused_(argc);
  _unused_(argv);
  
if (argc > 1 && argv??(1??) != 0)
  {
    printf("Hello, %s\n", argv??(1??));
  }

  return 0;
??>
