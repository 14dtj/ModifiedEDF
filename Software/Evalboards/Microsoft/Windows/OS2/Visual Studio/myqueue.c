#include "ucos_ii.h"
#include <stdio.h>
#include <stdlib.h>
#define null '\0'
#define QUEUE_CAPACITY 8
void initQueue() {
	int i;
	for (i = 0; i < QUEUE_LEVEL; i++) {
		Queue* queue = (Queue*)malloc(sizeof(Queue));
		if (queue == null) {
			exit(1);
		}
		queue->size = 0;
		queue->capacity = QUEUE_CAPACITY;

		queue->elements = (Queue_Data*)malloc(sizeof(Queue_Data)*(QUEUE_CAPACITY + 1));
		if (queue->elements == null) {
			exit(1);
		}
		taskQueue[i] = *queue;
	}
}

void enqueue(Queue_Data* data) {
	int index = data->importance;
	if (taskQueue == null) {
		exit(1);
	}
	else {
		Queue_Data* head = taskQueue[index].elements;
		int i;
		/*  Deep copy*/
		for (i = 0; i < taskQueue[index].size; i++) {
			if (data->deadline < head[i].deadline) {
				int j;
				for (j = taskQueue[index].size-1; j >= i; j--) {
					head[j + 1].deadline = head[j].deadline;
					head[j + 1].importance = head[j].importance;
					head[j + 1].prio = head[j].prio;
					head[j + 1].id = head[j].id;
				}
				head[i].deadline = data->deadline;
				head[i].importance = data->importance;
				head[i].prio = data->prio;
				head[i].id = data->id;
				break;
			}
		}
		if (i == 0) {
			taskQueue[index].elements->deadline = data->deadline;
			taskQueue[index].elements->importance = data->importance;
			taskQueue[index].elements->prio = data->prio;
			taskQueue[index].elements->id = data->id;
		}
		taskQueue[index].size++;
	}
}
/* Because the schedule always run the first task, so just need to update the first task's location */
void update(INT32U level) {
	Queue queue = taskQueue[level];
	Queue_Data* head = queue.elements;
	Queue_Data first = head[0];
	int i;
	for (i = 0; i < queue.size; i++) {
		if (first.deadline < head[i].deadline) {
			int j;
			for (j = queue.size - 1; j >= i; j--) {
				head[j + 1] = head[j];
			}
			head[i] = first;
			break;
		}
	}
}