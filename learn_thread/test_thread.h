#ifndef TEST_THREAD_H_
#define TEST_THREAD_H_

#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define Trace_print(str) \
    cout << str << endl

pthread_attr_t m_attr;
pthread_t m_thread_t;
pthread_mutex_t m_mutex;


#endif //TEST_THREAD_H_