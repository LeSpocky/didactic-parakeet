/*
 * SPDX-FileCopyrightText: 2026 Alexander Dahl <post@lespocky.de>
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	int myerrno;
	char *x;
	char *y;

#ifndef NDEBUG
	if ( argc > 0 )
	{
		printf( "%s debug\n", argv[0] );
	}
#endif

	x = malloc( 10 * sizeof(char) );
	if ( x == NULL )
	{
		myerrno = errno;
		fprintf( stderr, "Error (%d) allocating memory: %s\n",
				 myerrno, strerror(myerrno) );
		return EXIT_FAILURE;
	}
	snprintf( x, 10 * sizeof(char), "XXX" );
	printf( "%s\n", x );

	y = malloc( 10 * sizeof(char) );
	if ( y == NULL )
	{
		myerrno = errno;
		fprintf( stderr, "Error (%d) allocating memory: %s\n",
				 myerrno, strerror(myerrno) );
		return EXIT_FAILURE;
	}
	snprintf( y, 10 * sizeof(char), "YYY" );
	printf( "%s\n", y );

	free( x );

	// printf( "x[5]: %c\n", x[5] );

	return EXIT_SUCCESS;
}
