#include <iostream>
#include "test_thread.h"

using namespace std;

#if 0
pthread_t SAL_thread_t;
pthread_attr_t SAL_thread_attr;

pid_t gettid(void) {
    return syscall(SYS_gettid);
}

void* SAL_thread_func(void *para_1) {
    cout << "SAL_thread_func pid = " << gettid() << endl; //获取进程ID

    pthread_detach(pthread_self());

    while(true) {
        cout << "SAL_thread_func" << endl;
        sleep(3);
    }

    pthread_exit(0);
}

void* Func(void* para) {
    cout << pthread_self() << endl;
    
    cout << "Func pid = " << getpid() << endl;

    pthread_detach(pthread_self());

    pthread_attr_init(&SAL_thread_attr);
    int ret = pthread_create(&SAL_thread_t, &SAL_thread_attr, SAL_thread_func, NULL);

    while(true) {
        cout << "Func ..." << endl;
        sleep(2);
    }

    pthread_exit(0);
}

int main() {
    cout << "Hello World !" << endl;

    pthread_t m_thread;
    pthread_attr_t attr;

    pthread_attr_init (&attr);   
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);   

    int ret = pthread_create(&m_thread, &attr, Func, NULL);
    // pthread_detach(m_thread);

    cout <<  "ret = " << ret << endl;

    // pthread_join(m_thread, NULL);
    // pthread_exit(0);

    while(true) {
        sleep(2);
    }

    cout <<  "return 0" << endl;
    return 0;
}
#endif

int Init(void) {
    int ret = 0;
    ret = pthread_mutex_init(&m_mutex, NULL);
    if (0 != ret) {
        Trace_print("pthread_mutex_init failed");
        return false;
    }

    ret = pthread_attr_init(&m_attr);//初始化默认属性
    if (0 != ret) {
        Trace_print("pthread_attr_init failed");
        return false;
    }

    //PTHREAD_CREATE_JOINABLE：设置线程等待,不设置属性时，默认为JOINABLE
    //PTHREAD_CREATE_DETACHED：设置线程分离
    ret = pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_DETACHED);
    if (0 != ret) {
        Trace_print("pthread_attr_init failed");
        return false;
    }

    int detachstate;
    ret = pthread_attr_getdetachstate(&m_attr, &detachstate);//获取设置的线程属性
    // cout << "detachstate = " << detachstate << endl;

    size_t stackSize;
    pthread_attr_getstacksize(&m_attr, &stackSize);
    // cout << stackSize << endl;//系统默认的大小=8388608

    //重新设置线程使用堆栈大小
    ret = pthread_attr_setstacksize(&m_attr, 65535);
    if (0 != ret) {
        Trace_print("pthread_attr_setstacksize failed");
        return false;
    }
    pthread_attr_getstacksize(&m_attr, &stackSize);
    // cout << stackSize << endl;//65535

    /*
    * PTHREAD_EXPLICIT_SCHED：不继承父线程的调度策略才可以设置线程的调度策略
    * PTHREAD_INHERIT_SCHED：继承父线程的调度策略
    */
    ret = pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
     if (0 != ret) {
        Trace_print("pthread_attr_setinheritsched failed");
        cout << ret << endl;
        return false;
    }

    /*
    * SCHED_OTHER：其他普通调度策略，sched_priority仅能设置为0(前提:设置了不继承父线程调度策略PTHREAD_EXPLICIT_SCHED)
    * SCHED_RR：轮询调度策略，同一优先级中，各个线程平均分配资源，先后平均运行，线程优先级可设置为1-99
    * SCHED_FIFO：抢占式调度，设置该线程后会持续占用CPU，不会执行其他实时线程，线程优先级可设置为1-99
    */
    int policy = SCHED_OTHER;
    
    struct sched_param m_sched_param;
    m_sched_param.sched_priority = 0;

    ret = pthread_attr_setschedpolicy(&m_attr, policy);
    if (0 != ret) {
        Trace_print("pthread_attr_setschedpolicy failed");
        cout << ret << endl;
        return false;
    }

    // pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setschedparam(&m_attr, &m_sched_param);
    if (0 != ret) {
        Trace_print("pthread_attr_setschedparam failed");
        cout << ret << endl;
        return false;
    }

    return true;
}

void DeInit() {

    pthread_attr_destroy(&m_attr);//销毁线程属性，不影响创建的线程
    pthread_mutex_destroy(&m_mutex);

}

void LockMutex() {
    pthread_mutex_lock(&m_mutex);
}

void UnLockMutex() {
    pthread_mutex_unlock(&m_mutex);
}

void My_Create_Thread() {
    LockMutex();

    int ret = pthread_create(&m_thread_t, &m_attr, NULL, NULL);

    UnLockMutex();
}

int main (int argc, char* argv[]) {

    if (!Init()) {
        Trace_print("Init failed");
    }

    My_Create_Thread();

    return 0;
}