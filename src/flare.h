//
// Created by jobinrjohnson on 27/05/21.
//

#ifndef FLARE_FLARE_H
#define FLARE_FLARE_H

#include <lang/driver.h>
#include <ast/Node.h>

namespace flare {

    class Flare {

        lang::Driver driver;

        ast::Node *ast;

        int exitCode = 0;

    public:

        Flare();

        void setInputStream(std::istream &stream);

        void setFileStream(std::string &fileName);

        void parseStream();

        void codeGenAst();

        int getExitCode();

        void printLLVMIR();

        void executeJit();

    };

}


#endif //FLARE_FLARE_H
