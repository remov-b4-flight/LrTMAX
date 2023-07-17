/**
* @file queue.c
* @brief basic queue
*/
#include "queue.h"

void queue_init(QUEUE *q) {
	q->head = 0;
	q->tail = 0;
	for (uint8_t i = 0; i < QUEUE_DEPTH; i++) {
		q->data[i] = 0;
	}
}

bool queue_enqueue(QUEUE *q, uint16_t value) {
	if (q->tail >= QUEUE_DEPTH) {
		return false;
	} else {
		q->data[ q->tail ] = value;
		q->tail++;
	}
	return true;
}

uint16_t queue_dequeue(QUEUE *q) {
	if (q->head == q->tail) {
		return	QUEUE_EMPTY;
	} else {
		uint16_t temp = q->data[ q->head ];
		q->head++;
		return temp;
	}
}

bool queue_isempty(QUEUE *q) {
	return (q->head == q->tail)?	true:false;
}
