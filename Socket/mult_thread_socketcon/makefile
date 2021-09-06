SRC=-I${HOME}/Documents/TEST/Linux/Socket/mult_thread_socketcon
COMPILE=gcc

# .SUFFIXES: .c .o
# .c.o:
# 	@${COMPILE} ${SRC}/*.c -c $<

all:server client

CFLAGS = -Wall

#compile cc
# $@:代表当前的目标 
server:server.o wrap.o
	@${COMPILE} server.o wrap.o -o server -lpthread
#@rm -f server.o wrap.o
client:client.o wrap.o
	@${COMPILE} client.o wrap.o -o client -lpthread
#@rm -f client.o wrap.o

%.o%.c:
	@${COMPILE} -c $< -Wall

clean:
	rm -rf server client *.o