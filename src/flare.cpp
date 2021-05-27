//
// Created by jobinrjohnson on 27/05/21.
//

#include <exceptions/FlareException.h>
#include "flare.h"
#include "ast/Node.h"
#include "jit/FlareJit.h"

namespace flare {

    Flare::Flare() {

    }

    void Flare::setInputStream(std::istream &stream) {

        try {
            this->driver.parseInputStream(stream);
            return;
        } catch (char const *e) {
            std::cerr << "Error occurred while parsing : " << e;
        } catch (std::string e) {
            std::cerr << "Error occurred while parsing : " << e;
        } catch (exceptions::FlareException *e) {
            std::cerr << e->getMessage() << "\n\n";
        }

        this->hasParseError = true;
    }

    int Flare::getExitCode() {
        return this->hasParseError ? 1 : this->exitCode;
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

}
