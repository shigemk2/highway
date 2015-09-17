#include <stdio.h>
#include <string.h>
#include "queue.h"

file_queue *create_file_queue()
{
    file_queue *queue = (file_queue *)malloc(sizeof(file_queue));
    queue->first = NULL;
    queue->last  = NULL;
    queue->total = 0;
    return queue;
}

file_queue_node *enqueue_file(file_queue *queue, char *filename)
{
    file_queue_node *node = (file_queue_node *)malloc(sizeof(file_queue_node));
    node->id   = queue->total++;
    node->next = NULL;
    strcpy(node->filename, filename);

    if (queue->first) {
        queue->last->next = node;
        queue->last = node;
    } else {
        queue->first = node;
        queue->last  = node;
    }

    return node;
}

file_queue_node *dequeue_file(file_queue *queue)
{
    if (queue->first) {
        file_queue_node *first = queue->first;
        queue->first = first->next;
        return first;
    } else {
        return NULL;
    }
}

/* file_queue *create_file_queue() */
/* { */
/*     file_queue *queue = (file_queue *)malloc(sizeof(file_queue)); */
/*     queue->first = NULL; */
/*     queue->last  = NULL; */
/*     return queue; */
/* } */
/*  */
/* file_queue_node *enqueue_file(file_queue *queue, char *filename) */
/* { */
/*     file_queue_node *node = (file_queue_node *)malloc(sizeof(file_queue_node)); */
/*     node->next = NULL; */
/*     strcpy(node->filename, filename); */
/*  */
/*     if (queue->first) { */
/*         queue->last->next = node; */
/*         queue->last = node; */
/*     } else { */
/*         queue->first = node; */
/*         queue->last  = node; */
/*     } */
/*  */
/*     return node; */
/* } */
/*  */
/* file_queue_node *dequeue_file(file_queue *queue) */
/* { */
/*     if (queue->first) { */
/*         file_queue_node *first = queue->first; */
/*         queue->first = first->next; */
/*         return first; */
/*     } else { */
/*         return NULL; */
/*     } */
/* } */
