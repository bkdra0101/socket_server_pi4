#include <sys/types.h>   /* cho cac ham lien quan den socket*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h> /*cho prinf */
#include <unistd.h> /*cho cac ham lien quan toi he thong */
#include <string.h> /*cho memset() */
#include <stdlib.h>

const int g_portNumer=54321;
//tao socket
//gan dia chi(bind)
// listen connection tu client
//Accept connection va tao socket de giao tiep giua clien va server
//send va receive data su dung socket vua tao

int main (int argc, char ** argv)
{
	int serverSocketFd,newsocket;
	struct sockaddr_in serverSocketAddr;
	int addLen= sizeof(serverSocketAddr);
	char buff[1024]={0};
	char * serverMesssage = "Hello from server";
	
	//Tao socket
	serverSocketFd =socket(AF_INET,SOCK_STREAM,0);
	if(serverSocketFd <0)
	{
		perror("socket failed"); //ham log loi
		exit(EXIT_FAILURE); // thoat chuong trinh kem theo loi
	}
	//bind gan dia chi( tao cau truc dia chi)
	serverSocketAddr.sin_family = AF_INET;
	serverSocketAddr.sin_addr.s_addr = INADDR_ANY;
	serverSocketAddr.sin_port = htons(g_portNumer); //htons chuyen ve dang port tu so int
	if (bind(serverSocketFd,(struct sockaddr *)&serverSocketAddr,addLen)<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	//listen connection tu client
	if (listen(serverSocketFd,100)) //doi 100yeu cau ket noi 
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	
	//accept va tao socket moi
	newsocket =accept(serverSocketFd,(struct sockaddr *)&serverSocketAddr,(socklen_t*)&addLen); // tra ve socket moi
	if (newsocket <0)
	{
		perror("accept new socket failed");
		exit(EXIT_FAILURE);
	}
	// Send and receiver data
	//Recerice data from client
	read(newsocket,buff,1024); // note khoi can ep kieu char * vi da san roi
	printf("%s \n",buff);

	//gui data
	send(newsocket,serverMesssage,strlen(serverMesssage),0);
	
	

	
	return 0;
}
