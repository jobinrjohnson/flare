//
// Created by jobinrjohnson on 24/07/21.
//

#include <string>
#include "flare.h"

using namespace std;

extern "C" {


void printString(struct FLARE_string_t *s) {
    if (s != nullptr && s->str != nullptr)
        printf("%s\n", ((std::string *) (*s).str)->c_str());
    else
        printf("\n");
}

void FLARE_str_init(FLARE_string_t **s, int8_t *charSeq) {
    *s = new FLARE_string_t;
    auto *str = new std::string();
    str->assign((const char *) charSeq);
    (*s)->str = (int8_t *) str;
}

void FLARE_str_concat(struct FLARE_string_t *s1, struct FLARE_string_t *s2, struct FLARE_string_t **res) {
    FLARE_str_init(res, (int8_t *) "");
    if (s1 != nullptr && s1->str != nullptr)
        ((string *) (*res)->str)->append(*(string *) s1->str);
    if (s2 != nullptr && s2->str != nullptr)
        ((string *) (*res)->str)->append(*(string *) s2->str);
}

void FLARE_str_assign(struct FLARE_string_t *s1, struct FLARE_string_t *s2) {

    if (s1 == nullptr) {
        FLARE_str_init(&s1, (int8_t *) ((std::string *) s2->str)->c_str());
        return;
    }
    ((std::string *) s1->str)->clear();
    ((std::string *) s1->str)->append(*((std::string *) s2->str));
}

bool FLARE_str_is_equal(struct FLARE_string_t *s1, struct FLARE_string_t *s2) {
    return *((string *) s1->str) == *(string *) s2->str;
}

}