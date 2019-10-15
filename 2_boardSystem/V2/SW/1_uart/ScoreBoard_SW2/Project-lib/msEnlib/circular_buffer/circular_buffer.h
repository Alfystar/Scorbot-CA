/*
 * circular_buffer.h
 *
 *  Created on: 25 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_
#define PROJECT_LIB_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

// The definition of our circular buffer structure is hidden from the user
struct circular_buf_t_ {
    uint16_t *buffer;
    size_t head;
    size_t tail;
    size_t max; //of the buffer
    bool full;
};

/// Opaque circular buffer structure
typedef struct circular_buf_t_ circular_buf_t;

/// Handle type, the way users interact with the API
typedef circular_buf_t_ *cbuf_handle_t;

/// Pass in a storage buffer and size, returns a circular buffer handle
/// Requires: buffer is not NULL, size > 0
/// Ensures: cbuf has been created and is returned in an empty state
cbuf_handle_t circular_buf_init(uint16_t *buffer, size_t size);

/// Free a circular buffer structure
/// Requires: cbuf is valid and created by circular_buf_init
/// Does not free data buffer; owner is responsible for that
void circular_buf_free(cbuf_handle_t cbuf);

/// Reset the circular buffer to empty, head == tail. Data not cleared
/// Requires: cbuf is valid and created by circular_buf_init
void circular_buf_reset(cbuf_handle_t cbuf);

/// Put version 1 continues to add data if the buffer is full
/// Old data is overwritten
/// Requires: cbuf is valid and created by circular_buf_init
void circular_buf_put(cbuf_handle_t cbuf, uint16_t data);

/// Put Version 2 rejects new data if the buffer is full
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns 0 on success, -1 if buffer is full
int circular_buf_put2(cbuf_handle_t cbuf, uint16_t data);

/// Retrieve a value from the buffer
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns 0 on success, -1 if the buffer is empty
int circular_buf_get(cbuf_handle_t cbuf, uint16_t *data);

/// Retrieve a value from the buffer before the last, and not forward the head
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns 0 on success, -1 if the buffer is empty
int circular_buf_getLastOne(cbuf_handle_t cbuf, uint16_t *data);

/// CHecks if the buffer is empty
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns true if the buffer is empty
bool circular_buf_empty(cbuf_handle_t cbuf);

/// Checks if the buffer is full
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns true if the buffer is full
bool circular_buf_full(cbuf_handle_t cbuf);

/// Check the capacity of the buffer
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns the maximum capacity of the buffer
size_t circular_buf_capacity(cbuf_handle_t cbuf);

/// Check the number of elements stored in the buffer
/// Requires: cbuf is valid and created by circular_buf_init
/// Returns the current number of elements in the buffer
size_t circular_buf_size(cbuf_handle_t cbuf);
#ifndef __IN_ECLIPSE__

#include "circular_buffer.cpp"

#endif
#endif /* PROJECT_LIB_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_ */
