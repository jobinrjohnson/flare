//
// Created by jobinrjohnson on 06/08/21.
//


#include <vector>
#include "../../src/ast/constants/AstConstants.h"
#include "flare.h"

using namespace std;

extern "C" {


void FLARE_arr_init(FLARE_array_t **s, flare::ast::VariableType variableType) {
    *s = new FLARE_array_t;
    switch (variableType) {

        case flare::ast::VariableType::VARTYPE_BOOLEAN:
            (*s)->arr = (int8_t *) new std::vector<bool>();
            break;
        case flare::ast::VariableType::VARTYPE_INT_32:
            (*s)->arr = (int8_t *) new std::vector<int32_t>();
            break;
        case flare::ast::VariableType::VARTYPE_INT_64:
        case flare::ast::VariableType::VARTYPE_INT:
            (*s)->arr = (int8_t *) new std::vector<int64_t>();
            break;
        case flare::ast::VariableType::VARTYPE_FLOAT:
            (*s)->arr = (int8_t *) new std::vector<float>();
            break;
        case flare::ast::VariableType::VARTYPE_DOUBLE:
        case flare::ast::VariableType::VARTYPE_NUMBER:
            (*s)->arr = (int8_t *) new std::vector<double>();
            break;
        case flare::ast::VariableType::VARTYPE_ARRAY:
            break;
        case flare::ast::VariableType::VARTYPE_STRING:
            (*s)->arr = (int8_t *) new std::vector<FLARE_string_t *>();
            break;
        case flare::ast::VariableType::VARTYPE_VOID:
            break;
        case flare::ast::VariableType::OTHER:
            break;
    }

    if ((*s)->arr == nullptr) {
        throw "Not defined";
    }

}

#define FLARE_arr_index_assign(T, N)  \
void FLARE_arr_index_assign_##N(FLARE_array_t *s, int64_t index, T value) {     \
    if(((vector<T> *) s->arr)->size() <= (unsigned long)(index+1) ){            \
        ((vector<T> *) s->arr)->resize(index+1);                               \
    }                                                                           \
    ((vector<T> *) s->arr)->at(index) = value;                                   \
}

FLARE_arr_index_assign(int64_t, int64_t)
FLARE_arr_index_assign(double, double)
FLARE_arr_index_assign(bool, bool)
FLARE_arr_index_assign(FLARE_string_t, FLARE_string_t)

//void FLARE_arr_index_assign_int64_t(FLARE_array_t *s, int64_t index, int64_t value) {
//    if(((vector<int64_t> *) s->arr)->size() <= (unsigned long)(index) ){
//        ((vector<int64_t> *) s->arr)->resize(index+1);
//    }
//    ((vector<int64_t> *) s->arr)->at(index) = value;
//}

// TODO add size check.
#define FLARE_arr_index_deref(T, N) \
T FLARE_arr_index_deref_##N(FLARE_array_t *s, int64_t index) { \
    return ((vector<T> *) s->arr)->at(index); \
}

FLARE_arr_index_deref(int64_t, int64_t)
FLARE_arr_index_deref(double, double)
FLARE_arr_index_deref(bool, bool)
FLARE_arr_index_deref(FLARE_string_t, FLARE_string_t)

//int64_t FLARE_arr_index_deref_int(FLARE_array_t *s, int64_t index) {
//    return ((vector<int64_t> *) s->arr)->at(index);
//}


}
