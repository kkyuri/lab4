#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd, max_sd, sd, activity, i;
    int client_sockets[MAX_CLIENTS];
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    char client_names[MAX_CLIENTS][50]; // 클라이언트 이름 저장

    // 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 주소 구조체 설정
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 바인딩
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 리슨
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // 클라이언트 소켓 초기화
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
        strcpy(client_names[i], ""); // 이름 초기화
    }

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);

        // 서버 소켓을 읽기 집합에 추가
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        // 클라이언트 소켓을 읽기 집합에 추가
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }
            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // select 호출
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("Select error");
        }

        // 새로운 클라이언트 연결 처리
        if (FD_ISSET(server_fd, &readfds)) {
            socklen_t addrlen = sizeof(address);
            if ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
                perror("Accept error");
                exit(EXIT_FAILURE);
            }

            printf("New connection, socket fd: %d\n", client_fd);

            // 클라이언트 소켓 배열에 추가
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = client_fd;
                    // 클라이언트 이름 요청
                    send(client_fd, "Enter your name: ", 17, 0);
                    break;
                }
            }
        }

        // 클라이언트 소켓에서 수신된 데이터 처리
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (FD_ISSET(sd, &readfds)) {
                int valread = read(sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // 클라이언트가 연결을 종료한 경우
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t*)&address);
                    printf("Client disconnected, ip: %s, port: %d\n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    client_sockets[i] = 0;
                } else {
                    // 수신된 메시지가 클라이언트 이름일 경우
                    if (strlen(client_names[i]) == 0) {
                        buffer[valread] = '\0';
                        strcpy(client_names[i], buffer); // 이름 저장
                        printf("Client %d set name: %s\n", sd, client_names[i]);
                    } else {
                        // 수신된 메시지를 모든 클라이언트에게 방송
                        buffer[valread] = '\0';
                        printf("Message from %s: %s\n", client_names[i], buffer);

                        // 메시지 포맷팅: 버퍼 크기를 고려하여 처리
                        char message[BUFFER_SIZE];
                        int msg_length = snprintf(message, sizeof(message), "%s: %s", client_names[i], buffer);

                        // 메시지가 버퍼 크기를 초과하지 않도록 처리
                        if (msg_length >= sizeof(message)) {
                            message[sizeof(message) - 1] = '\0'; // 마지막에 NULL 추가
                        }

                        for (int j = 0; j < MAX_CLIENTS; j++) {
                            if (client_sockets[j] != 0 && client_sockets[j] != sd) {
                                send(client_sockets[j], message, strlen(message), 0);
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

