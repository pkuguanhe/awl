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

int transferData(int clientfd, int userfd, char *buf)
{
    while(1)
    {
        recv(userfd, buf, MAXBUF, MSG_DONTWAIT);
        send(clientfd, buf, MAXBUF, MSG_DONTWAIT);
        recv(clientfd, buf, MAXBUF, MSG_DONTWAIT);
        send(userfd, buf, MAXBUF, MSG_DONTWAIT);
    }
}

int main(int argc, char const *argv[])
{
    int listenfd, clientFd;
    char buf[MAXBUF];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if(argc!=2)
    {
        fprintf(stderr, "usage : %s <port>\n", argv[0]);
        exit(1);
    }

    printf("listening...\n");
    listenfd = Open_listenfd(argv[1]);
    clientFd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
    printf("connected...\n");

    while(1)
    {
        socklen_t userlen;
        struct sockaddr_storage useraddr;
        int userFd = Accept(listenfd, (SA*)&useraddr, &userlen);
        transferData(clientFd, userFd, buf);
    }
}
