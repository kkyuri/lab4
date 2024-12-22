#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_get(int client_socket);
void handle_post(int client_socket, const char *request);
void handle_cgi(int client_socket);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // 바인딩
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 리슨
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0) {
            perror("Receive failed");
            close(client_socket);
            continue;
        }
        buffer[bytes_received] = '\0';

        // 요청 로그 출력
        printf("Received request:\n%s\n", buffer);

        if (strstr(buffer, "GET /cgi-bin/hello.cgi") != NULL) {
            handle_cgi(client_socket);
        } else if (strstr(buffer, "GET") != NULL) {
            handle_get(client_socket);
        } else if (strstr(buffer, "POST") != NULL) {
            handle_post(client_socket, buffer);
        } else {
            const char *response_header = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n";
            send(client_socket, response_header, strlen(response_header), 0);
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}

void handle_get(int client_socket) {
    const char *response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *response_body = "Hello, World! This is a simple web server.\n";
    send(client_socket, response_header, strlen(response_header), 0);
    send(client_socket, response_body, strlen(response_body), 0);
    printf("%s\n\n", response_body);
}

void handle_post(int client_socket, const char *request) {
    const char *response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *response_body = "POST request received.\n";
    send(client_socket, response_header, strlen(response_header), 0);
    send(client_socket, response_body, strlen(response_body), 0);
    printf("%s\n\n", response_body);
}

void handle_cgi(int client_socket) {
    // HTTP 응답 헤더 전송
    const char *response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    send(client_socket, response_header, strlen(response_header), 0);

    pid_t pid = fork();
    if (pid == 0) {
        // 자식 프로세스
        dup2(client_socket, STDOUT_FILENO);  // 클라이언트 소켓을 표준 출력으로 리디렉션
        dup2(client_socket, STDERR_FILENO);   // 표준 에러를 클라이언트 소켓으로 리디렉션
        execl("/usr/lib/cgi-bin/hello.cgi", "hello.cgi", NULL);
        perror("execl failed"); // execl이 실패한 경우
        exit(1);
    } else if (pid > 0) {
        // 부모 프로세스
        wait(NULL); // 자식 프로세스가 종료될 때까지 기다림
    } else {
        perror("Fork failed");
    }
}

