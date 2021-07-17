//
// Created by jobinrjohnson on 17/06/21.
//
#include <cstdio>
#include <cstdint>

using namespace std;

extern "C" {

void print(char *string) {
    printf("%s", string);
    fflush(stdout);
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

int32_t __FLARE_personality_function(int32_t i321, int32_t i322, int64_t i64, int8_t *i81, int8_t *i82) {

    printf("@__FLARE_personality_function\n");

    return 0;
}


}