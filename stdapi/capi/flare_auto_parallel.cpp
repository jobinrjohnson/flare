//
// Created by jobinrjohnson on 07/10/21.
//
#include <cstdio>
#include <pthread.h>
#include <cstdint>
#include <unistd.h>

extern "C" {

struct fTask {
    pthread_t *threads;
};

struct temp {
    int64_t a;
    void *pVars;
};

void createTask(void *(*f)(void *), void *pVars) {
    printf("\n---------------\n");

    auto *x = new temp;
    x->a = 0;
    x->pVars = pVars;

    fflush(stdout);
    pthread_t tid;
    pthread_create(&tid, NULL, f, (void *) (x));
    pthread_join(tid, NULL);
}

void runThread(void *(*f)(void *), void *pVars) {
    auto *x = (temp *) pVars;
    if (x->a == 0) {
        pthread_t tid;
        pthread_create(&tid, NULL, f, (void *) (x));
        pthread_join(tid, NULL);
    }
}

long getNumProc() {
    return sysconf(_SC_NPROCESSORS_ONLN);;
}

}