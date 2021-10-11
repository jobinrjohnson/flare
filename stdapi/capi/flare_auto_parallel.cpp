//
// Created by jobinrjohnson on 07/10/21.
//
#include <cstdio>
#include <pthread.h>
#include <cstdint>

extern "C" {

struct fTask {
    pthread_t *threads;
};

struct temp {
    int64_t a;
    int64_t b;
};

void createThread(void *(*f)(void *), void *pVars) {
    printf("---------------");

//    struct temp *x = (struct temp *) pVars;
//
//    printf("====================[[[[[[[%ld,%ld]]]]]]]]]===========\n\n\n\n\n", x->a, x->b);

    fflush(stdout);
    pthread_t tid;
    pthread_create(&tid, NULL, f, pVars);
    pthread_join(tid, NULL);
}

void runThread() {

}

}