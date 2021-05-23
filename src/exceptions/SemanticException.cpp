//
// Created by jobinrjohnson on 23/05/21.
//

#include "SemanticException.h"
#include "FlareException.h"

flare::exceptions::SemanticException::SemanticException(std::string error, int lineNumber)
        : flare::exceptions::FlareException(error) {
    this->lineNumber = lineNumber;
}

std::string flare::exceptions::SemanticException::getMessage() {
    return "Error at line " + std::to_string(this->lineNumber) + "\n" + FlareException::getMessage();
}
