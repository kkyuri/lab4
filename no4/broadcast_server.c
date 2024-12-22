#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLIENTS 100
#define MAX_NAME_LEN 50
#define MAX_MESSAGE_LEN 256

// 클라이언트 구조체 정의
typedef struct {
    char name[MAX_NAME_LEN];
    int is_registered;
} Client;

// 서버 구조체 정의
typedef struct {
    Client clients[MAX_CLIENTS];
    int client_count;
} Server;

// 서버 초기화 함수
void init_server(Server *server) {
    server->client_count = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].is_registered = 0;
    }
}

// 클라이언트 등록 함수
void add_client(Server *server, const char *name) {
    // 중복 확인
    for (int i = 0; i < server->client_count; i++) {
        if (strcmp(server->clients[i].name, name) == 0) {
            printf("클라이언트 '%s'는 이미 등록되어 있습니다.\n", name);
            return;
        }
    }

    if (server->client_count >= MAX_CLIENTS) {
        printf("최대 클라이언트 수를 초과했습니다. 등록할 수 없습니다.\n");
        return;
    }

    // 새 클라이언트 등록
    strcpy(server->clients[server->client_count].name, name);
    server->clients[server->client_count].is_registered = 1;
    server->client_count++;
    printf("클라이언트 '%s'가 서버에 등록되었습니다.\n", name);
}

// 메시지 브로드캐스트 함수
void broadcast(Server *server, const char *message) {
    if (server->client_count == 0) {
        printf("등록된 클라이언트가 없습니다. 메시지를 보낼 수 없습니다.\n");
        return;
    }

    printf("브로드캐스트: '%s'\n", message);
    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i].is_registered) {
            printf("[클라이언트 %s] 메시지를 수신했습니다: %s\n", server->clients[i].name, message);
        }
    }
}

// 메인 함수
int main() {
    Server server;
    char message[MAX_MESSAGE_LEN];
    char command[MAX_MESSAGE_LEN];
    char client_name[MAX_NAME_LEN];

    // 서버 초기화
    init_server(&server);

    printf("===== 서버가 시작되었습니다 =====\n");
    printf("명령어:\n");
    printf("- add [클라이언트 이름]: 클라이언트를 등록합니다.\n");
    printf("- send [메시지]: 모든 클라이언트에게 메시지를 브로드캐스트합니다.\n");
    printf("- exit: 프로그램을 종료합니다.\n");

    while (1) {
        printf("\n명령을 입력하세요: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // 개행 문자 제거

        if (strncmp(command, "add ", 4) == 0) {
            // 클라이언트 등록
            strncpy(client_name, command + 4, MAX_NAME_LEN - 1);
            client_name[MAX_NAME_LEN - 1] = '\0'; // null-terminate
            add_client(&server, client_name);
        } else if (strncmp(command, "send ", 5) == 0) {
            // 메시지 브로드캐스트
            strncpy(message, command + 5, MAX_MESSAGE_LEN - 1);
            message[MAX_MESSAGE_LEN - 1] = '\0'; // null-terminate
            broadcast(&server, message);
        } else if (strcmp(command, "exit") == 0) {
            // 프로그램 종료
            printf("서버를 종료합니다.\n");
            break;
        } else {
            printf("알 수 없는 명령입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}

