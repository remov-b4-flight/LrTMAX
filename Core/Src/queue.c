/**
* @file 		queue.c
* @brief 		basic queue
* @author		remov-b4-flight
* @copyright	3-Clause BSD License
*
*/
#include "queue.h"
/**
 * @brief Initialize queue structure
 * @param *q pointer to queue structure.
 */
void queue_init(QUEUE *q) {
	q->head = 0;
	q->tail = -1;
	for (uint8_t i = 0; i < QUEUE_DEPTH; i++) {
		q->data[i] = 0;
	}
}
/**
 * @brief push value to queue
 * @param *q pointer to queue structure
 * @param value value to push
 * @retval true when queue is full
 */
bool queue_enqueue(QUEUE *q, uint16_t value) {
	if ((q->tail + 2) % QUEUE_DEPTH == q->head) {
		return false;
	} else {
		q->data[ (q->tail + 1) % QUEUE_DEPTH ] = value;
		q->tail = (q->tail + 1) % QUEUE_DEPTH;
	}
	return true;
}
/**
 * @brief 	pull value from queue
 * @param 	*q pointer to queue structure
 * @retval	 pulled value from queue
 */
uint16_t queue_dequeue(QUEUE *q) {
	if ( queue_isempty(q) ) {
		return	QUEUE_EMPTY;
	} else {
		uint16_t temp = q->data[ q->head ];
		q->head = (q->head + 1) % QUEUE_DEPTH;
		return temp;
	}
}

/**
 * @brief	Empty check for queue
 * @param	*q pointer to queue structure
 * @retval	true if queue is empty
 */
bool queue_isempty(QUEUE *q) {
	return ((q->tail + 1) % QUEUE_DEPTH == q->head)?	true:false;
}
