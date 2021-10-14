//
// Created by jobinrjohnson on 17/06/21.
//
#include <cstdio>
#include <cstring>
#include <unistd.h>

using namespace std;

extern "C" {

void print(char *string) {
    printf("%s", string);
    fflush(stdout);
}

void printI(int value) {
    printf("%d\n", value);
    fflush(stdout);
}

void initSpdl() {
    usleep(200);
}

long int read_int() {
    long int i;
    int status = scanf("%ld", &i);
    if (status == 2) {
        return -1;
    }
    return i;
}

char *get_line() {
    char *buffer = NULL;
    size_t len;
    int line = getline(&buffer, &len, stdin);
    if (line == -1) {
        return buffer;
    }
    return buffer;
}


int __FLARE_throwException() {
    throw 1;
}

}