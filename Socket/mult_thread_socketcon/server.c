#include "wrap.h"
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>

#define MAXLINE 80
#define SERV_PORT 9000

struct s_info {
    struct sockaddr_in cliaddr;
    int connfd;
};


void* do_work (void *arg) {
    int n,i;
    struct s_info *ts = (struct s_info*)arg;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN]; //16

    while(true) {

        n = read(ts->connfd, buf, MAXLINE);// 读客户端
        printf("do_work : n = %d \n", n);
        if (0 == n) {
            printf("the client %d closed... \n", ts->connfd);
            break;
        }
        
        //receive message
        printf("received from %s at port %d \n",    \
             inet_ntop(AF_INET, &(ts->cliaddr.sin_addr), str, sizeof(str)),     \
            ntohs(ts->cliaddr.sin_port));
        
        for(i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]); //小写变为大写
        }
        write(STDOUT_FILENO, buf, n);//写出至屏幕
        write(ts->connfd, buf, n);// 回写给客户端
    }

    close(ts->connfd);

    return (void*)0;
}

int main (int argc, char* argv[]) {

    struct sockaddr_in servaddr, cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));
    socklen_t cliaddrLen = sizeof(cliaddr);

    int listen_socket, client_socket;
    struct s_info ts[256];
    int i = 0;
    pthread_t tid;

    listen_socket = Socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    printf("listen_socket = %d \n", listen_socket);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//指定本地任意IP地址
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listen_socket, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Listen(listen_socket, MAXLINE);

    printf("Accepting client connect ...... \n");

    while(true) {
        client_socket = Accept(listen_socket, (struct sockaddr*)&cliaddr, cliaddrLen);
        printf("accept client_socket = %d \n", client_socket);
        ts[i].cliaddr = cliaddr,
        ts[i].connfd = client_socket;

        pthread_create(&tid, NULL, (void*)do_work, (void*)&ts[i]);
        pthread_detach(tid);

        sleep(3);
        i++;
    }

    return 0;
}