//Simples project de sockets em windows. Solicita uma página na internet e lê seu conteúdo.
#include<winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PORT 80
#define MAX 4096


int main(int argc , char **argv)
{
	int n;
	int sendbytes;
    char send[MAX];
	char recv[MAX];

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)   //Iniciar a winsock dll, versão 2.
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");


	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) //Cria o socket(s), usando o protocplo TCP(0).
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");


	server.sin_family = AF_INET; //Internet socket
	server.sin_port = htons(PORT); //Espicificar a porta. htons -> Converte a ordem dos bytes do host para a ordem de bytes do TCP/IP.


    if(inet_pton(AF_INET,argv[1],&server.sin_addr) <= 0)  // inet_pton = Converter o texto do argumento na representação binária
         printf("Error\n");

	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}

	sprintf(send,"GET / HTTP/1.1\r\n\r\n"); //"Pedir" uma pagina . (Root)
	sendbytes = strlen(send);

	if(write(s,send,sendbytes) != sendbytes){ //Escevve essa pagina no socket.
         printf("Error");
	}

	memset(recv,0,MAX);

	while((n = read(s,recv,MAX-1)) > 0){ //Ler o conteúdo dessa pagina (Resposta do sevidor)


        printf("%s", recv);
	}
	if(n < 0)
        printf("Read error");


	exit(0);
}
