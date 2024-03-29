#include "unp.h"
#include <time.h>

int main(int argc, char **argv) {

	int 				listenfd, connfd;
	socklen_t			len;
	struct sockaddr_in 	servaddr, cliaddr;
	char 				buff[MAXLINE];
	time_t 				ticks;

	if(argc != 2)
		err_quit("usuage: <Program Name> <Port No.>");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for( ; ; ) {

		len = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &len);

		printf("\r\nClient Addr %lu \r\n", &cliaddr.sin_addr);
		printf("Client Port %hu \r\n", cliaddr.sin_port);

		printf("connection from %s, port %d\n",
			Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
			ntohs(cliaddr.sin_port) );

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buff ,strlen(buff));

		Close(connfd);
	}
}
