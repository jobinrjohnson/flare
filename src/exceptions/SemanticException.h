//
// Created by jobinrjohnson on 23/05/21.
//

#ifndef FLARE_SEMANTICEXCEPTION_H
#define FLARE_SEMANTICEXCEPTION_H


#include "FlareException.h"

namespace flare::exceptions {
    class SemanticException : public FlareException {

    protected:

        int lineNumber;

    public:
        SemanticException(std::string error, int lineNumber);

        std::string getMessage() override;

    };
}


#endif //FLARE_SEMANTICEXCEPTION_H
