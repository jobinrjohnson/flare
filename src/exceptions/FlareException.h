//
// Created by jobinrjohnson on 23/05/21.
//

#ifndef FLARE_FLAREEXCEPTION_H
#define FLARE_FLAREEXCEPTION_H

#include "string"

namespace flare::exceptions {

    class FlareException {

    protected:

        std::string exception;

    public:

        explicit FlareException(std::string);

        virtual std::string getMessage();

    };
}


#endif //FLARE_FLAREEXCEPTION_H
