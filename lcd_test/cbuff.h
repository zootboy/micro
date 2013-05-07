/*
 * File:	circular_buf.h
 * Author:	James Letendre
 *
 * Implementation of a circular buffer
 */
#ifndef _CIRCULAR_BUF_H_
#define _CIRCULAR_BUF_H_

#include <stdlib.h>

typedef struct {
	char *buffer;				// the data buffer
	size_t buf_size;			// the size of the data buffer
	size_t head;				// the next element to read from
	size_t tail;				// the next element to write to
	size_t size;				// the current size of the data buffer
} c_buffer_t;

/*
 * c_buffer_init
 * 	buffer:			The buffer to store data in
 * 	buffer_size:	The size of the data buffer
 *
 * 	return:	buffer struct
 */
c_buffer_t c_buffer_init( char *buffer, size_t buffer_size );

/*
 * c_buffer_write
 * 	buffer:			The buffer struct
 * 	c:				The character to add to the buffer
 *
 * return:
 *	0:				The character was written to the buffer
 *	other:			The buffer is full
 */
int c_buffer_write( c_buffer_t *buf, char c );

/*
 * c_buffer_read
 * 	buffer:			The buffer struct
 * 	c:				The pointer to store the character in
 *
 * return:
 *	0:				The character was read from the buffer
 *	other:			The buffer is empty
 */
int c_buffer_read( c_buffer_t *buf, char *c );

#endif
