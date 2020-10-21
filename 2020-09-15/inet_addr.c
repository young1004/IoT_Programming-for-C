#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{

	char addr1[30];// = argv[1];//"192.168.0.163";
	char addr2[30];// = argv[2];//"192.168.0.1";

    printf("%s", "Your IP: ");
    scanf("%s", addr1);
    printf("%s", "Your Router IP: ");
    scanf("%s", addr2);

	unsigned long conv_addr;
	conv_addr = inet_addr(addr1);
	if (conv_addr == INADDR_NONE)
		printf("Error Occur : %d \n", conv_addr);
	else
		printf("Unsigned long addr(network ordered):%x\n", conv_addr);
	conv_addr = inet_addr(addr2);
	if (conv_addr == INADDR_NONE)
		printf("Error Occured %d \n\n", conv_addr);
	else
		printf("unsigned long addr(nerwork ordered):%x\n\n", conv_addr);
	return 0;
}