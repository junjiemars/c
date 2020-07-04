#include <stdlib.h>
#include <string.h>

typedef struct queue_s {
  size_t n;
  size_t size;
  void *head;
  void *tail;
  void *data;
} queue_s;


static inline void*
queue_node_new(queue_s *const queue) {
  return queue->data = realloc(queue->data, queue->n * queue->size);
}

static inline void
queue_node_free(queue_s *const queue) {
  free(queue->data);
}

queue_s*
queue_new(queue_s *queue, size_t n, size_t size) {
  queue = calloc(1, sizeof(queue_s));
  if (queue) {
    queue->size = size;
    queue->n = n;
    queue_node_new(queue);
    queue->head = queue->tail = queue->data;
  }
  return queue;
}

void
queue_free(queue_s *const queue) {
  queue_node_free(queue);
  free(queue);  
}

int
queue_empty(queue_s *const queue) {
  return queue->head == queue->tail;
}

int
queue_full(queue_s *const queue) {
  size_t len = (char*)queue->tail - (char*)queue->data;
  return queue->size * queue->n == len;
}

void*
queue_enq(queue_s *queue, void *val) {
  if (queue_full(queue)) {
    size_t offset = (char*)queue->head - (char*)queue->data;
    size_t len = (char*)queue->tail - (char*)queue->head;
    if (offset > 0) {
      if (len > 0) {
        memmove(queue->data, queue->head, len);
      }
    } else {
      queue->n = queue->n*2;
      void *new_one = queue_node_new(queue);
      if (0 == new_one) {
        return 0;
      }
    }
    queue->head = queue->data;
    queue->tail = (char*)queue->head + len;
  }
  memcpy(queue->tail, val, queue->size);
  return queue->tail = (char*)queue->tail + queue->size;
}

void*
queue_deq(queue_s *const queue, void *val) {
  if (queue_empty(queue)) {
    queue->head = queue->tail = queue->data;
    return 0;
  }
  memcpy(val, queue->head, queue->size);
  return queue->head = (char*)queue->head + queue->size;
}

void*
queue_peek(queue_s *const queue, void *val) {
  if (queue_empty(queue)) {
    return 0;
  }
  memcpy(val, queue->head, queue->size);
  return queue->head;
}
