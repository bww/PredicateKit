all: parser lexer

parser: lemon PKGrammar.c

PKGrammar.c: PKGrammar.y
	./lemon -s PKGrammar.y

lemon: lemon.c

lemon.c:
	cc -o lemon lemon.c

lexer: PKLexer.c

PKLexer.c: PKLexer.l
	flex -o PKLexer.c PKLexer.l

clean:
	rm -f PKLexer.c PKGrammar.c PKGrammar.h

cleanall: clean
	rm -f lemon
