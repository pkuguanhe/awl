#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "csapp.h"


int transferData(int localFd, int serverFd, char *buf)
{
    while(1)
    {
        recv(serverFd, buf, MAXBUF, MSG_DONTWAIT);
        send(localFd, buf, MAXBUF, MSG_DONTWAIT);
        recv(localFd, buf, MAXBUF, MSG_DONTWAIT);
        send(serverFd, buf, MAXBUF, MSG_DONTWAIT);
    }
}

int main(int argc, char const *argv[])
{
    int serverFd, localFd;
    char buf[MAXBUF];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if(argc!=3)
    {
        fprintf(stderr, "usage : %s <port>\n", argv[0]);
        exit(1);
    }

    printf("listening...\n");
    serverFd = Open_clientfd(argv[1], argv[2]);
    printf("connected...\n");

    while(1)
    {
        socklen_t userlen;
        struct sockaddr_storage useraddr;
        localFd = Open_clientfd("127.0.0.1", "22");
        transferData(localFd, serverFd, buf);
    }
}
