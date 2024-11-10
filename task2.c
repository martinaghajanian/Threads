#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 10

int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int sum1 = 0, sum2 = 0;

void* sum_half(void* arg) {
    int start = *((int*)arg);
    int end = start + ARRAY_SIZE / 2;
    int* sum = (start == 0) ? &sum1 : &sum2;
    for (int i = start; i < end; i++) {
        *sum += array[i];
    }
    printf("Partial sum by thread %ld: %d\n", pthread_self(), *sum);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int start1 = 0, start2 = ARRAY_SIZE / 2;

    pthread_create(&thread1, NULL, sum_half, &start1);
    pthread_create(&thread2, NULL, sum_half, &start2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
