/**
* @file queue.h
* @brief basic queue
*/

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

#define	QUEUE_DEPTH	250
#define QUEUE_EMPTY	(uint16_t)0xffff

typedef struct queue_t {
	uint16_t	data[QUEUE_DEPTH];
	uint8_t		head;
	uint8_t		tail;
} QUEUE;

void queue_init(QUEUE *q);
bool queue_enqueue(QUEUE *q, uint16_t value);
uint16_t queue_dequeue(QUEUE *q);

#endif /* INC_QUEUE_H_ */
