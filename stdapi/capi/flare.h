//
// Created by jobinrjohnson on 06/08/21.
//

#ifndef FLARE_FLARE_H
#define FLARE_FLARE_H

extern "C" {

struct FLARE_string_base {
    int8_t *str;
};

struct FLARE_array_t {
    int8_t *arr;
};

typedef struct FLARE_string_base *FLARE_string_t;

}

#endif //FLARE_FLARE_H
