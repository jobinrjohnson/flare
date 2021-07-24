//
// Created by jobinrjohnson on 24/07/21.
//

#include <string>

extern "C" {

void FLARE_str_init(std::string *s, int8_t *charSeq) {
    s = new std::string();
    s->assign((const char *) charSeq);
}


}