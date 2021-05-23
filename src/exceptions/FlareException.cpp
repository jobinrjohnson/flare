//
// Created by jobinrjohnson on 23/05/21.
//

#include "FlareException.h"

std::string flare::exceptions::FlareException::getMessage() {
    return this->exception;
}

flare::exceptions::FlareException::FlareException(std::string message) {
    this->exception = message;
}
