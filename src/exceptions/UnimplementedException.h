//
// Created by jobinrjohnson on 23/05/21.
//

#ifndef FLARE_UNIMPLEMENTEDEXCEPTION_H
#define FLARE_UNIMPLEMENTEDEXCEPTION_H


#include <exceptions/FlareException.h>

namespace flare::exceptions {
    class UnimplementedException : public FlareException {

    public:
        explicit UnimplementedException(std::string message);

    };
}


#endif //FLARE_UNIMPLEMENTEDEXCEPTION_H
