#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);
void rev_str(char* message, char* rev_message);

int main(int argc, char **argv)
{
    int sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    
    char message[30];
    char rev_message[30];
    int str_len;
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connet() error");

    str_len = read(sock, message, sizeof(message) - 1);

    if (str_len == -1)
        error_handling("read() error!");

    message[str_len] = 0;
    printf("Message from server : %s \n", message);

    rev_str(message, rev_message);
    // strcpy(rev_message, rev_str(message));
    // rev_message = rev_str(message);
    // printf("뒤집은 문자열: %s\n", rev_message);
    // printf("문자열 길이: %ld\n", sizeof(rev_message)); 여기가 문제!
    write(sock, rev_message, sizeof(rev_message));
    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void rev_str(char* message, char* rev_message)
{
    int len = strlen(message);

    for (int i = len-1; i>=0; i--){
        rev_message[len-i-1] = message[i];
    }
}