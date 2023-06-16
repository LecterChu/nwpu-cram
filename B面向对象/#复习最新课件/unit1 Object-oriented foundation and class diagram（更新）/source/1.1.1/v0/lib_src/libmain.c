/* libmain - flex run-time support library "main" function */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/lib_src/libmain.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */

extern int yylex();

int main( argc, argv )
int argc;
char *argv[];
	{
	return yylex();
	}
