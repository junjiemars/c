#include <stdlib.h>
#include <string.h>

typedef struct queue_s {
  size_t n;
  size_t size;
  void *head;
  void *tail;
  void *data;
} queue_s;

queue_s *queue_new(queue_s *q, size_t n, size_t size);
void queue_free(queue_s *const q);
int queue_empty(queue_s *q);
int queue_full(queue_s *q);
void *queue_enq(queue_s *const q, void *val);
void *queue_deq(queue_s *const q, void *val);
void *queue_peek(queue_s *const q, void *val);


static inline void*
queue_node_new(queue_s *const q) {
  return q->data = realloc(q->data, q->n * q->size);
}

static inline void
queue_node_free(queue_s *const q) {
  free(q->data);
}

queue_s*
queue_new(queue_s *q, size_t n, size_t size) {
  q = calloc(1, sizeof(queue_s));
  if (q) {
    q->size = size;
    q->n = n;
    queue_node_new(q);
    q->head = q->tail = q->data;
  }
  return q;
}

void
queue_free(queue_s *const q) {
  queue_node_free(q);
  free(q);  
}

int
queue_empty(queue_s *const q) {
  return q->head == q->tail;
}

int
queue_full(queue_s *const q) {
  size_t len = (char*)q->tail - (char*)q->data;
  return q->size * q->n == len;
}

void*
queue_enq(queue_s *const q, void *val) {
  if (queue_full(q)) {
    size_t offset = (char*)q->head - (char*)q->data;
    size_t len = (char*)q->tail - (char*)q->head;
    if (offset > 0) {
      if (len > 0) {
        memmove(q->data, q->head, len);
      }
    } else {
      q->n = q->n*2;
      void *new_one = queue_node_new(q);
      if (0 == new_one) {
        return 0;
      }
    }
    q->head = q->data;
    q->tail = (char*)q->head + len;
  }
  memcpy(q->tail, val, q->size);
  return q->tail = (char*)q->tail + q->size;
}

void*
queue_deq(queue_s *const q, void *val) {
  if (queue_empty(q)) {
    q->head = q->tail = q->data;
    return 0;
  }
  memcpy(val, q->head, q->size);
  return q->head = (char*)q->head + q->size;
}

void*
queue_peek(queue_s *const q, void *val) {
  if (queue_empty(q)) {
    return 0;
  }
  memcpy(val, q->head, q->size);
  return q->head;
}
