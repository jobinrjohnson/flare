//
// Created by jobinrjohnson on 24/07/21.
//

#include <string>
#include <iostream>

extern "C" {

struct FLARE_string_t {
    int8_t *str;
    int64_t length;
};

void printString(struct FLARE_string_t *s) {
    printf("%s", ((std::string *) s->str)->c_str());
}

void FLARE_str_init(FLARE_string_t **s, int8_t *charSeq) {
    *s = new FLARE_string_t;
    auto *str = new std::string();
    str->assign((const char *) charSeq);
    (*s)->str = (int8_t *) str;
    (*s)->length = str->length();
}


}