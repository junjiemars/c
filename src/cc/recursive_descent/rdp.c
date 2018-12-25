#include <_cc_.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {ident, number, lparen, rparen, times, slash, plus,
							minus, eql, neq, lss, leq, gtr, geq, callsym, beginsym, semicolon,
							endsym, ifsym, whilesym, becomes, thensym, dosym, constsym, comma,
							varsym, procsym, period, oddsym} Symbol;


static Symbol sym;
void nextsym(void);
void expression(void);

static char *tape;
static char *p_tape;

void error(int status, const char *format, ...) {
	va_list args;
	va_start(args, format);
	fprintf(stdout, format, args);
	va_end(args);
	exit(status);
}

void nextsym(void) {
	if (0 == p_tape) {
		return;
	}
}

int accept(Symbol s) {
	if (sym == s) {
		nextsym();
		return 1;
	}
	return 0;
}

int expect(Symbol s) {
	if (accept(s))
		return 1;
	error(1, "expect: unexpected symbol");
	return 0;
}

void factor(void) {
	if (accept(ident)) {
		;
	} else if (accept(number)) {
		;
	} else if (accept(lparen)) {
		expression();
		expect(rparen);
	} else {
		error(1, "factor: syntax error");
		nextsym();
	}
}

void term(void) {
	factor();
	while (sym == times || sym == slash) {
		nextsym();
		factor();
	}
}

void expression(void) {
	if (sym == plus || sym == minus)
		nextsym();
	term();
	while (sym == plus || sym == minus) {
		nextsym();
		term();
	}
}

void condition(void) {
	if (accept(oddsym)) {
		expression();
	} else {
		expression();
		if (sym == eql || sym == neq || sym == lss || sym == leq || sym == gtr || sym == geq) {
			nextsym();
			expression();
		} else {
			error(1, "condition: invalid operator");
			nextsym();
		}
	}
}

void statement(void) {
	if (accept(ident)) {
		expect(becomes);
		expression();
	} else if (accept(callsym)) {
		expect(ident);
	} else if (accept(beginsym)) {
		do {
			statement();
		} while (accept(semicolon));
		expect(endsym);
	} else if (accept(ifsym)) {
		condition();
		expect(thensym);
		statement();
	} else if (accept(whilesym)) {
		condition();
		expect(dosym);
		statement();
	} else {
		error(1, "statement: syntax error");
		nextsym();
	}
}

void block(void) {
	if (accept(constsym)) {
		do {
			expect(ident);
			expect(eql);
			expect(number);
		} while (accept(comma));
		expect(semicolon);
	}
	if (accept(varsym)) {
		do {
			expect(ident);
		} while (accept(comma));
		expect(semicolon);
	}
	while (accept(procsym)) {
		expect(ident);
		expect(semicolon);
		block();
		expect(semicolon);
	}
	statement();
}


int main(int argc, char **argv) {
	_unused_(argv);

	if (argc > 1) {
		tape = argv[1];
		p_tape = tape;
		
		nextsym();
		block();
		expect(period);
	}
	
	return 0;
}
