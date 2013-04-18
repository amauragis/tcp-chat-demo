#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <stdlib.h>

main(int argc, char **argv) {
	char *remhost; u_short remport;
	int sock, left, num, put;
	struct sockaddr_in remote;
	struct hostent *h;

	remhost = argv[1]; remport = atoi(argv[2]);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	// bzero((char *) &remote, sizeof(remote));
	remote.sin_family = (short) AF_INET;
	h = gethostbyname(remhost);
	bcopy((char *)h->h_addr, (char *)&remote.sin_addr, 
		  h->h_length);

	remote.sin_port = htons(remport);
	if (0 != connect(sock, (struct sockaddr *)&remote, sizeof(remote)))
	{
		perror("Connection error!");
		exit(1);
	}

	char* buf;
	buf = malloc(200);
	int bufSize = 200;
	int bufFill = 0;
	puts("read loop");
	while (read(STDIN_FILENO, buf + bufFill, 1) != 0)
	{
		puts("readchar");

		bufFill++;
		if (bufFill >= bufSize - 2)
		{
			buf = realloc(buf, bufSize*2);
			bufSize *= 2;
			puts("buffer increasing");
		}
	}

	buf[bufFill+1] = 0;
	bufFill++;
	printf("Buffer: %s", buf);
	left = bufFill; put = 0;
	while(left > 0) 
	{
		num = write(sock, buf+put, left);
		if( num < 0)
		{
			perror("inet_wstream: write");
			exit(1);
		}
		else {
			left -= num;
			put += num;
		}
		write(STDOUT_FILENO, buf+put, left);
	}
}