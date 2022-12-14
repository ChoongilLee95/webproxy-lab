#include "csapp.h"

void echo(int connfd){
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("server received %d byte\n", (int)n);
        Rio_writen(connfd, buf, n);
    }
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; // 연결 되었을때 연결 사실을 서버측에서 알 수 있는 수단?
    // argv[1] = 서버에서 열 포트 번호
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc !=2){
        fprintf(stderr, "usage: %s <port> \n",argv[0]); // stderr 찾아보기
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1){
        clientlen = sizeof(struct sockaddr_storage); // 
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA*)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname,client_port);
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}
