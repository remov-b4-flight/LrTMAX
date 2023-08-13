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
	q->tail = 0;
	for (uint8_t i = 0; i < QUEUE_DEPTH; i++) {
		q->data[i] = 0;
	}
}
/**
 * @brief push value to queue
 * @param *q pointer to queue structure
 * @param value value to push
 */
bool queue_enqueue(QUEUE *q, uint16_t value) {
	if (q->tail >= QUEUE_DEPTH) {
		return false;
	} else {
		q->data[ q->tail ] = value;
		q->tail++;
	}
	return true;
}
/**
 * @brief 	pull value from queue
 * @param 	*q pointer to queue structure
 * @retval	 pulled value from queue
 */
uint16_t queue_dequeue(QUEUE *q) {
	if (q->head == q->tail) {
		return	QUEUE_EMPTY;
	} else {
		uint16_t temp = q->data[ q->head ];
		q->head++;
		return temp;
	}
}

/**
 * @brief	Empty check for queue
 * @param	*q pointer to queue structure
 * @retval	true if queue is empty
 */
bool queue_isempty(QUEUE *q) {
	return (q->head == q->tail)?	true:false;
}
