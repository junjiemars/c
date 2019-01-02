/*
https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm

<declarator> ::= {<pointer>}? <direct-declarator>
<pointer> ::= * {<type-qualifier>}* {<pointer>}?
<type-qualifier> ::= const | volatile
<direct-declarator> ::= <identifier>
                      | ( <declarator> )
                      | <direct-declarator> ( <parameter-type-list> )
                      | <direct-declarator> ( {identifier}* )
<parameter-type-list> ::= <parameter-list>
                        | <parameter-list> , ...
<parameter-list> ::= <parameter-declaration>
                   | <parameter-list> , <parameter-declaration>
<parameter-declaration> ::= {<declaration-specifier>}+ <declarator>
                          | {<declaration-specifier>}+ <abstract-declarator>
                          | {<declaration-specifier>}+
<direct-abstract-declarator> ::= ( <abstract-declarator> )
                               | {<direct-abstract-declarator>}? [ {<parameter-type-list>}? ]
<abstract-declarator> ::= <pointer>
                        | <pointer> <direct-abstract-declarator>
                        | <direct-abstract-declarator>
 
 */
