/**
* @file			queue.h
* @brief		Basic queue functions
* @author		remov-b4-flight
* @copyright	3-Clause BSD License
*/

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

#define	QUEUE_DEPTH	128	// 2^n is recommended
#define QUEUE_EMPTY	(uint16_t)0xffff

//! Structure for queue
typedef struct queue_t {
	uint16_t	data[QUEUE_DEPTH + 1];
	uint8_t		head;
	uint8_t		tail;
} QUEUE;

void queue_init(QUEUE *q);
bool queue_enqueue(QUEUE *q, uint16_t value);
uint16_t queue_dequeue(QUEUE *q);
bool queue_isempty(QUEUE *q);

#endif /* INC_QUEUE_H_ */
