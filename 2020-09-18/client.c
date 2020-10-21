#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char **argv)
{
    int sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    
    char message[30];
    char rev_message[30] = "";
    char *ip_addr;
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

    printf("insert String : ");
    scanf("%[^\n]", message);

    write(sock, message, sizeof(message));

    str_len = read(sock, rev_message, sizeof(rev_message) - 1);

    if (str_len == -1)
        error_handling("read() error!");

    printf("Message from server : '%s' ", rev_message);
    ip_addr = inet_ntoa(serv_addr.sin_addr);
    printf("server ip addr : '%s'\n", ip_addr);

    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

