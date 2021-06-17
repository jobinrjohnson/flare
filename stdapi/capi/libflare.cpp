//
// Created by jobinrjohnson on 17/06/21.
//
#include <cstdio>
using namespace std;

extern "C" {

void print() {
    printf("Hello World");
}

long int read_int() {
    long int i;
    int status = scanf("%ld", &i);
    if (status == 2) {
        return -1;
    }
    return i;
}

char* getLine(){
    char *buffer = NULL;
    size_t len;
    int line = getline(&buffer, &len, stdin);
    if(line == -1){
        return buffer;
    }
    return buffer;
}



}