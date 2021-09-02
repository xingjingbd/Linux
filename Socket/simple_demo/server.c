/*
* 服务器端
*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR   -1
#define NO_ERROR 0

#define MAX_SOCKET_NUM  5
#define PORT    9000

//初始化socket
int Init_Socket() {

    int lis_socket = socket(AF_INET/*IPv4协议*/, SOCK_STREAM, IPPROTO_TCP);
    printf("Init_Socket : lis_socket = %d \n", lis_socket);
    if (ERROR == lis_socket) {
        printf("init socket failed \n");
        return ERROR;
    }

    //绑定port和addr
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);//接收任意IP地址

    int ret = bind(lis_socket, (struct sockaddr*)&addr, sizeof(addr));
    if(ERROR == ret) {
        printf("bind failed \n");
        return ERROR;
    }

    //listen 监听socket,只负责监听，不负责连接
    ret = listen(lis_socket, MAX_SOCKET_NUM);
    if(ERROR == ret) {
        printf("listen failed \n");
        return ERROR;
    }

    printf("wait for client connecting ...... \n");

    return lis_socket;
}

int Start_Accept(int lis_socket) {

    struct sockaddr_in  client_addr;
    unsigned int len = sizeof(client_addr);

    int recv_socket = accept(lis_socket, (struct sockaddr*)&client_addr, &len);
    if(ERROR == recv_socket) {
        printf("accept failed \n");
        return ERROR;
    }

    printf("receive a client , addr = %s \n", inet_ntoa(client_addr.sin_addr));

    //返回接收到的socket
    return recv_socket;
}

int main(int argc, char*argv[]) {

    int listen_socket = Init_Socket();

    while(1) {

        int new_socket = Start_Accept(listen_socket);

        sleep(3);
    }

    close(listen_socket);

    return 0;
}