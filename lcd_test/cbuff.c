/*
 * File:	circular_buf.c
 * Author:	James Letendre
 *
 * Implementation of a circular buffer
 */
#include "cbuff.h"

/*
 * c_buffer_init
 * 	buffer:			The buffer to store data in
 * 	buffer_size:	The size of the data buffer
 *
 * 	return:	buffer struct
 */
c_buffer_t c_buffer_init( char *buffer, size_t buffer_size )
{
	c_buffer_t buf_struct;

	buf_struct.buffer = buffer;
	buf_struct.buf_size = buffer_size;
	buf_struct.head = 0;
	buf_struct.tail = 0;
	buf_struct.size = 0;

	return buf_struct;
}

/*
 * c_buffer_write
 * 	buffer:			The buffer struct
 * 	c:				The character to add to the buffer
 *
 * return:
 *	0:				The character was written to the buffer
 *	other:			The buffer is full
 */
int c_buffer_write( c_buffer_t *buf, char c )
{
	if( buf->size == buf->buf_size )
	{
		return -1;
	}
	else
	{
		buf->buffer[buf->tail++] = c;
		
		buf->tail = buf->tail % buf->buf_size;
		buf->size++;

	}
	return 0;
}

/*
 * c_buffer_read
 * 	buffer:			The buffer struct
 * 	c:				The pointer to store the character in
 *
 * return:
 *	0:				The character was read from the buffer
 *	other:			The buffer is empty
 */
int c_buffer_read( c_buffer_t *buf, char *c )
{
	if( buf->size == 0 )
	{
		return -1;
	}
	else
	{
		*c = buf->buffer[buf->head++];

		buf->head = buf->head % buf->buf_size;
		buf->size--;
	}
	return 0;
}

