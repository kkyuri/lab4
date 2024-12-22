#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_LINE 511

// 메시지를 수신하는 스레드 함수
void *receive_messages(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buf[MAX_LINE + 1];

    while (1) {
        int n = recv(sock, buf, sizeof(buf) - 1, 0);
        if (n > 0) {
            buf[n] = 0; // 문자열 종료
            printf("%s\n", buf); // 서버로부터 받은 메시지 출력
            printf("You: "); // 입력 프롬프트 다시 출력
            fflush(stdout); // 출력 버퍼를 비워서 즉시 표시
        } else {
            break; // 연결이 끊어지면 종료
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    char buf[MAX_LINE + 1];

    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket fail");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect fail");
        exit(1);
    }

    printf("Connected to server.\n");

    // 사용자 ID 입력
    printf("Enter your username: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;  // 개행 문자를 제거
    send(sock, buf, strlen(buf), 0);

    // 메시지 수신 스레드 생성
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock);

    // 메시지 전송
    while (1) {
        printf("You: "); // 입력 프롬프트
        fflush(stdout); // 출력 버퍼를 비워서 즉시 표시
        fgets(buf, sizeof(buf), stdin);
        send(sock, buf, strlen(buf), 0);

        if (strstr(buf, "exit") != NULL) break;
    }

    close(sock);
    return 0;
}

