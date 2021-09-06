#include "wrap.h"
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>

#define MAXLINE 80
#define SERV_PORT 9000

int main (int argc ,char*argv[]) {

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    char buf[MAXLINE];
    int sockfd, n;

    sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);//指定本地任意IP地址
    addr.sin_port = htons(SERV_PORT);
    
    Connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        write(sockfd, buf, strlen(buf));

        n = read(sockfd, buf, MAXLINE);
        if (0 >n ) {
            printf("the other side has been closed \n");
            break;
        }
        else {
            write(STDOUT_FILENO, buf, n);
        }
    }

    close(sockfd);

    return 0;
}