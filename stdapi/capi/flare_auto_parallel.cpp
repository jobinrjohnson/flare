//
// Created by jobinrjohnson on 07/10/21.
//
#include <cstdio>
#include <pthread.h>

extern "C" {

struct fTask {
    pthread_t *threads;
};

void createThread(void *(*f)(void *)) {
    printf("---------------");
    fflush(stdout);
    pthread_t tid;
    pthread_create(&tid, NULL, f, NULL);
    pthread_join(tid, NULL);
}

void runThread() {

}

}