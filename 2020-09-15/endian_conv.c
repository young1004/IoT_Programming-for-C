#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h> 

int main(int argc, char **argv)
{
	short host_port_order = 0x1234;
	short net_port_order;

	long host_add_order = 0x12345678;
	long net_add_order;

	net_port_order = htons(host_port_order);
	net_add_order = htonl(host_add_order);

	printf("Host ordered port : %x\n", host_port_order);
	printf("Network orderd port : %x\n\n", net_port_order);

	printf("Host ordered Address : %x\n", host_add_order);
	printf("Network ordered Address : %x \n\n", net_add_order);

    if (host_port_order == net_port_order)
        printf("My System : Big-Endian Policy\n");
    else
        printf("My System : Little-Endian Policy\n");



	return 0;
}