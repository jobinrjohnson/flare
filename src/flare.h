//
// Created by jobinrjohnson on 27/05/21.
//

#ifndef FLARE_FLARE_H
#define FLARE_FLARE_H

#include <lang/driver.h>

namespace flare {

    class Flare {

        lang::Driver driver;

        bool hasParseError = false;

        int exitCode = 0;

    public:

        Flare();

        void setInputStream(std::istream &stream);

        int getExitCode();

        void printLLVMIR();

        void executeJit();

    };

}


#endif //FLARE_FLARE_H
