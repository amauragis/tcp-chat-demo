#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

main(int argc, char **argv) {
	int listener, conn, length; char ch;
	struct sockaddr_in s1, s2;
	
	listener = socket( AF_INET, SOCK_STREAM, 0 );
	
	bzero((char *) &s1, sizeof(s1));
	s1.sin_family = (short) AF_INET;
	s1.sin_addr.s_addr = htonl(INADDR_ANY); //accept any IP
	s1.sin_port = htons(atoi(argv[1])); //Bind to given port
	bind(listener, (struct sockaddr *)&s1, sizeof(s1));
	length = sizeof(s1);
	getsockname(listener, (struct sockaddr *)&s1, &length);
	printf("RSTREAM:: assigned port number %d\n",
           ntohs(s1.sin_port));
    
	listen(listener,1);
	length = sizeof(s2);
	conn=accept(listener, (struct sockaddr *)&s2, &length);
	printf("Connection accepted\n");
	//printf("\n\nRSTREAM:: data from stream:\n");
    
    //if(fork() == 0)
    //{
    while ( read(conn, &ch, 1) == 1) {putchar(ch);}
        putchar('\n');
    //}
}