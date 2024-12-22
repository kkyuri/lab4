#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int sock;
char buffer[BUFFER_SIZE];

void *receive_messages(void *arg) {
    while (1) {
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("\nServer: %s", buffer);
            printf("You: ");  // 사용자가 다시 입력할 수 있도록 프롬프트 표시
            fflush(stdout);
        } else {
            printf("Disconnected from server\n");
            break;
        }
    }
    return NULL;
}

int main() {
    struct sockaddr_in serv_addr;
    char name[50]; // 클라이언트 이름 저장

    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 서버 주소 변환
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // 서버에 연결
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connected to server. Type your messages below:\n");

    // 클라이언트 이름 입력
    recv(sock, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    fgets(name, sizeof(name), stdin);
    send(sock, name, strlen(name), 0);

    // 수신 스레드 생성
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    while (1) {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    return 0;
}

