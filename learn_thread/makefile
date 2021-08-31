SRC=-I${HOME}/Documents/TEST/thread_t
COMPILE=g++

.SUFFIXES: .cpp .o
.cpp.o:
	@${COMPILE} ${SRC}/*.cpp -c $<

all:test_thread

CFLAGS = -Wall

#compile c++
# $@:代表当前的目标 
test_thread:test_thread.o
	@${COMPILE} -o $@ $? -lpthread
	@rm -f test_thread.o

	@echo "#####################"

clean:
	rm -rf thread_t