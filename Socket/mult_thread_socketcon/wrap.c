#include "wrap.h"

void perr_exit(const char* s) {
    perror(s);
    exit(-1);//exit(0)
}

int Socket(int family, int type, int protocol) {

    int ret = socket(family, type, protocol);
    if (0 > ret) {
        perr_exit("socket error");
    }

    return ret;
}

int Bind(int lisfd, const struct sockaddr* s_addr, socklen_t addrLen) {
    int ret = bind(lisfd, s_addr, addrLen);
    printf("Bind : ret = %d \n", ret);

    if (0 > ret) {
        perr_exit("bind error");
    }

    return true;
}

int Listen(int fd, int backlog) {

    if (0 > listen(fd, backlog)) {
        perr_exit("listen error");
    }

    return true;
}

int Accept(int lisfd, struct sockaddr* cliaddr, socklen_t cliaddrLen) {

    int client_socket;
again:
    client_socket = accept(lisfd, cliaddr, &cliaddrLen);

    if ((errno == ECONNABORTED) || (errno == EINTR)){
        goto again;
    }
    else {
        printf("accept : ");
    }

    return client_socket;
}

int Connect(int clifd, const struct sockaddr* cliaddr, socklen_t cliaddrLen) {

    if (0 > connect(clifd, cliaddr, cliaddrLen)) {
        perr_exit("connect error");
    }

    return true;
}


