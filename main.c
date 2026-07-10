/*
 * SPDX-FileCopyrightText: 2026 Alexander Dahl <post@lespocky.de>
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int myerrno;
	char *x;
	char *y;

	x = malloc( 10 * sizeof(char) );
	if ( x == NULL )
	{
		myerrno = errno;
		fprintf( stderr, "Error (%d) allocating memory: %s\n",
				 myerrno, strerror(myerrno) );
		return EXIT_FAILURE;
	}

	y = malloc( 10 * sizeof(char) );
	if ( y == NULL )
	{
		myerrno = errno;
		fprintf( stderr, "Error (%d) allocating memory: %s\n",
				 myerrno, strerror(myerrno) );
		return EXIT_FAILURE;
	}

	free( x );

	// printf( "x[5]: %c\n", x[5] );

	return EXIT_SUCCESS;
}
