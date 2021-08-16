//
// Created by jobinrjohnson on 27/05/21.
//

#include <exceptions/FlareException.h>

#include <utility>
#include "flare.h"
#include "ast/Node.h"
#include "jit/FlareJit.h"

namespace flare {

    void Flare::setInputStream(std::istream &stream, std::string streamIdentifier) {
        this->streamName.assign(streamIdentifier);
        this->driver.setInputStream(stream);
    }

    int Flare::getExitCode() {
        return this->exitCode;
    }

    void Flare::printLLVMIR() {
        module->print(llvm::outs(), nullptr);
    }

    void Flare::executeJit() {
        // Execute JIT
        jit::FlareJit jit(module);
        jit.initialize();
        jit.execute();

        this->exitCode = jit.getExitCode();

    }

    void Flare::setFileStream(std::string &fileName) {

        std::ifstream file(fileName.c_str(), std::ifstream::in);

        if (!file.is_open()) {
            std::cerr << "Some error occurred while opening the file.";
            return;
        }

        this->setInputStream(file, fileName);
    }

    void Flare::parseStream() {
        try {
            this->ast = this->driver.parse();
        } catch (char const *e) {
            std::cerr << "Error occurred while parsing : " << e;
        }
    }

    void Flare::codeGenAst() {
        try {
            this->ast->startCodeGen();
            delete (this->ast);
        } catch (exceptions::FlareException *e) {
            std::cerr << e->getMessage() << "\n\n";
        }
#ifndef FLARE_DEBUG
        catch (char const *e) {
            std::cerr << "Error occurred while parsing : " << e;
        } catch (std::string e) {
            std::cerr << "Error occurred while parsing : " << e;
        }
#endif

    }

    void Flare::executeStream(std::istream &stream, std::string streamIdentifier) {
        this->setInputStream(stream, streamIdentifier);
//        try {
        this->parseStream();
        this->codeGenAst();
//        } catch (exceptions::FlareException *e) {
//            std::cerr << e->getMessage() << "\n\n";
//            exit(1);
//        }
        this->executeJit();
    }


}
