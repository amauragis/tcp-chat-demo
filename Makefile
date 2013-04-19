CC = gcc
EXEC = tcpchatserver tcpchatclient
CCFLAGS = -Wall -g -pedantic
OBJS = tcpchatserver.o tcpchatclient.o

all: ${EXEC}

#${EXEC}: ${OBJS}
#	${CC} ${CCFLAGS} -lm -o ${EXEC} ${OBJS}

tcpchatclient: tcpchatclient.o
	${CC} ${CCFLAGS} -lm -o tcpchatclient tcpchatclient.o
tcpchatserver: tcpchatserver.o
	${CC} ${CCFLAGS} -lm -o tcpchatserver tcpchatserver.o

clean:
	rm -f ${EXEC} ${OBJS}
