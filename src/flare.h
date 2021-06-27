//
// Created by jobinrjohnson on 27/05/21.
//

#ifndef FLARE_FLARE_H
#define FLARE_FLARE_H

#include <lang/driver.h>
#include <ast/Node.h>

namespace flare {

    class Flare {

        // Lex driver
        lang::Driver driver;

        // The AST root node
        ast::Node *ast;

        // The program exit code
        int exitCode = 0;

        std::string streamName = "";

    public:

        // Set input stream
        void setInputStream(std::istream &stream, std::string stream_name);

        // Set file
        void setFileStream(std::string &fileName);

        // Perform parsing using the driver
        void parseStream();

        // Starts generating LLVM IR Trew
        void codeGenAst();

        //  Returns the Program exit code after executing it
        int getExitCode();

        // Executes the program using LLJIT
        void executeJit();

        // Prints the LLVM IR
        void printLLVMIR();

        // Reads, Parses, IR Generates, Executes the stream
        void executeStream(std::istream &stream, std::string stream_name);

    };

}


#endif //FLARE_FLARE_H
