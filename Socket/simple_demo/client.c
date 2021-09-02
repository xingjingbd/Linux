#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR   -1
#define NO_ERROR 0
#define PORT    9000

static  int cli_socket = 0;

int Connect_Server() {

    //创建socket
    cli_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ERROR == cli_socket) {
        printf("socket failed \n");
        return ERROR;
    }

    //请求建立连接
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = connect(cli_socket, (struct sockaddr*)&addr, sizeof(addr));
    if (ERROR == ret) {
        printf("connect failed \n");
        return ERROR;
    }

    return 0;
}

int main() {

    while(1) {
        Connect_Server();
        sleep(5);
    }

    close(cli_socket);

    return 0;
}