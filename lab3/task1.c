#include <stdio.h>

typedef struct {
    int id;
    int arrival;
    int duration;
} Call;

#define QUEUE_CAPACITY 100

static Call data[QUEUE_CAPACITY];
static int head  = 0;
static int tail  = 0;
static int count = 0;

void queue_init(void) {
    head = tail = count = 0;
}

void queue_destroy(void) {
    head = tail = count = 0;
}

int is_empty(void) {
    return count == 0;
}

int is_full(void) {
    return count == QUEUE_CAPACITY;
}

int enqueue(Call c) {
    if (is_full()) return 0;
    data[tail] = c;
    tail = (tail + 1) % QUEUE_CAPACITY;
    count++;
    return 1;
}

int dequeue(Call *out) {
    if (is_empty()) {
        printf("Queue is empty: dequeue skipped\n");
        return 0;
    } else {
        *out = data[head];
        head = (head + 1) % QUEUE_CAPACITY;
        count--;
        return 1;
    }
}

int peek_front(Call *out) {
    if (is_empty()) return 0;
    *out = data[head];
    return 1;
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
    dequeue(&current);

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
