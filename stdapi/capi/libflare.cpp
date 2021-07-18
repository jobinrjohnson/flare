//
// Created by jobinrjohnson on 17/06/21.
//
#include <cstdio>
#include <cstdint>
#include <unwind.h>
#include <malloc.h>
#include <cstring>

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


_Unwind_Reason_Code __gxx_personality_v0
        (int, _Unwind_Action, _Unwind_Exception_Class,
         struct _Unwind_Exception *, struct _Unwind_Context *);

_Unwind_Reason_Code __FLARE_personality_function(int version, _Unwind_Action actions,
                                                 _Unwind_Exception_Class exceptionClass,
                                                 struct _Unwind_Exception *exceptionObject,
                                                 struct _Unwind_Context *context) {

    return __gxx_personality_v0(version, actions,
                                exceptionClass,
                                exceptionObject,
                                context);

}

struct OurExceptionType_t {
    int type;
};

struct OurBaseException_t {
    struct OurExceptionType_t type;
    struct _Unwind_Exception unwindException;
};

_Unwind_Exception *__FLARE_createUnWindException() {
    size_t size = sizeof(OurBaseException_t);
    OurBaseException_t *ret = (OurBaseException_t *) memset(malloc(size), 0, size);
    (ret->type).type = 0;
    (ret->unwindException).exception_class = 0;
    (ret->unwindException).exception_cleanup = nullptr;
    return (&(ret->unwindException));
}

void __FLARE_raiseException(struct _Unwind_Exception *ex) {
    printf("unwinding........................");
    _Unwind_Reason_Code reason = _Unwind_RaiseException(ex);
    printf("\n\n\n\nthis failed because %d\n\n\n\n", reason);
    fflush(stdout);
}


}