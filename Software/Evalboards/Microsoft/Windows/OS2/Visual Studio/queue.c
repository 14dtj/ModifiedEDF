#include "ucos_ii.h"
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 8
#define LIST_SIZE 3

prioQueue* initQueue() {
	int i;
	prioQueue* result;
	for (i = 0; i < LIST_SIZE; i++) {
		result[i] = (prioQueue)malloc(sizeof(prioQueue));
	}
}
