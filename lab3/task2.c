#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival;
    int duration;
} Call;

typedef struct Node {
    Call data;
    struct Node *next;
} Node;

static Node *front = NULL;
static Node *rear  = NULL;

void queue_init(void) {
    front = rear = NULL;
}

int is_empty(void) {
    return front == NULL;
}

int is_full(void) {
    return 0;
}

int enqueue(Call c) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) return 0;
    n->data = c;
    n->next = NULL;
    if (rear == NULL) front = n;
    else rear->next = n;
    rear = n;
    return 1;
}

int dequeue(Call *out) {
    if (is_empty()) return 0;
    Node *n = front;
    *out = n->data;
    front = n->next;
    if (front == NULL) rear = NULL;
    free(n);
    return 1;
}

int peek_front(Call *out) {
    if (is_empty()) return 0;
    *out = front->data;
    return 1;
}

void queue_destroy(void) {
    Call tmp;
    while (dequeue(&tmp)) {}
}

#define CALLS_COUNT 12

int main(void) {
    Call calls[CALLS_COUNT] = {
        { 1,  0, 5}, { 2,  1, 4}, { 3,  2, 6}, { 4,  3, 3},
        { 5,  4, 5}, { 6, 10, 2}, { 7, 11, 4}, { 8, 12, 3},
        { 9, 30, 5}, {10, 31, 2}, {11, 32, 2}, {12, 33, 1}
    };

    int clock = 0;
    int next_call = 0;
    int processed = 0;
    int serving = 0;
    int busy_until = 0;
    int queue_len = 0;
    int max_len = 0;
    int last_finish = 0;
    Call current;

    queue_init();

    while (processed < CALLS_COUNT) {
        if (serving && clock >= busy_until) {
            serving = 0;
            processed++;
            last_finish = busy_until;
            printf("t=%3d: call #%d finished\n", clock, current.id);
        }

        while (next_call < CALLS_COUNT && calls[next_call].arrival <= clock) {
            if (!enqueue(calls[next_call])) {
                printf("Error: queue is full or out of memory\n");
                queue_destroy();
                return 1;
            }
            queue_len++;
            printf("t=%3d: call #%d added to the queue\n",
                   clock, calls[next_call].id);
            next_call++;
        }

        if (!serving && !is_empty()) {
            dequeue(&current);
            queue_len--;
            serving = 1;
            busy_until = clock + current.duration;
            printf("t=%3d: operator took call #%d (until t=%d)\n",
                   clock, current.id, busy_until);
        }

        if (queue_len > max_len) max_len = queue_len;

        clock++;
    }

    queue_destroy();

    printf("\nMaximum queue length: %d\n", max_len);
    printf("Last call finish time: %d s\n", last_finish);
    return 0;
}
