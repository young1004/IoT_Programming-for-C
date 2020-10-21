#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);
void rev_str(char *message, char *rev_message);

int main(int argc, char **argv)
{
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    char rev_massage[30] = "";
    int clnt_addr_size;
    char message[30] = "";
    char *ip_addr;

    time_t conn_time;
    time_t disconn_time;
    struct tm *t;

    FILE *log_file;

    log_file = fopen("conn_log.log", "a");

    if (log_file == NULL)
        printf("파일열기 실패\n");

    if (argc != 2)
    {
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

    if (clnt_sock == -1)
        error_handling("accept() error");

    time(&conn_time);
    t = (struct tm *)localtime(&conn_time);
    printf("연결 시간: %d년 %d월 %d일 %d시 %d분 %d초\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    read(clnt_sock, message, sizeof(message) - 1);
    printf("Message from client : '%s' ", message);

    ip_addr = inet_ntoa(clnt_addr.sin_addr);
    printf("client ip addr : '%s'\n", ip_addr);
    fprintf(log_file, "client ip addr : %s\n", ip_addr);
    fprintf(log_file, "연결 시간: %d년 %d월 %d일 %d시 %d분 %d초\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    rev_str(message, rev_massage);
    write(clnt_sock, rev_massage, sizeof(rev_massage));
    close(clnt_sock);

    time(&disconn_time);
    t = (struct tm *)localtime(&disconn_time);
    printf("종료 시간: %d년 %d월 %d일 %d시 %d분 %d초\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    fprintf(log_file, "종료 시간: %d년 %d월 %d일 %d시 %d분 %d초\n\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    fclose(log_file);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void rev_str(char *message, char *rev_message)
{
    int len = strlen(message);

    for (int i = len - 1; i >= 0; i--)
    {
        rev_message[len - i - 1] = message[i];
    }
}