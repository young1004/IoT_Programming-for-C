#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(void)
{
	struct sockaddr_in addr1,addr2;
	char *str;
    // char ip_str[30];
    // char route_str[30];

	addr1.sin_addr.s_addr=htonl(0xa300a8c0);//a300a8c0
	addr2.sin_addr.s_addr=htonl(0x100a8c0);//100a8c0

	str=inet_ntoa(addr1.sin_addr);
	printf("Dotted-Decimal notation : %s\n",str);

	inet_ntoa(addr2.sin_addr);
	printf("Dotted-Decimal notation : %s \n\n",str);
	return 0;
}
