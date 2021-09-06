#ifndef WRAP_H_
#define WRAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h> //socket

#define false 0
#define true  1


//print error message
void perr_exit(const char* s);

int Socket(int family, int type, int protocol);

int Bind(int lisfd, const struct sockaddr* s_addr, socklen_t addrlen);

int Listen(int fd, int backlog);

//return the socket of client
int Accept(int lisfd, struct sockaddr* cliaddr, socklen_t cliaddrLen);

int Connect(int clifd, const struct sockaddr* cliaddr, socklen_t cliaddrLen);

#endif