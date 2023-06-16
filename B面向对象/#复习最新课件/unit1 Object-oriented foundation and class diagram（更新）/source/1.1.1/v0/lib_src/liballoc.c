/* liballoc - flex run-time memory allocation */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/lib_src/liballoc.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */

#ifdef STDC_HEADERS

#include <stdlib.h>

#else /* not STDC_HEADERS */

void *malloc();
void *realloc();
void free();

#endif /* not STDC_HEADERS */


void *yy_flex_alloc( size )
int size;
	{
	return (void *) malloc( (unsigned) size );
	}

void *yy_flex_realloc( ptr, size )
void *ptr;
int size;
	{
	return (void *) realloc( ptr, (unsigned) size );
	}

void yy_flex_free( ptr )
void *ptr;
	{
	free( ptr );
	}
