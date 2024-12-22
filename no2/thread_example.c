#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg; // 쓰레드 번호
    printf("Hello from thread %d!\n", thread_num);
    sleep(1); // 1초 대기
    printf("Thread %d finished execution.\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[5]; // 5개의 쓰레드
    int thread_args[5];

    // 쓰레드 생성
    for (int i = 0; i < 5; i++) {
        thread_args[i] = i + 1; // 쓰레드 번호 설정
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_args[i]);
    }

    // 모든 쓰레드가 끝날 때까지 대기
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished execution.\n");
    return 0;
}

