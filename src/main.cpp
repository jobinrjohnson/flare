#include "lang/driver.h"
#include "ast/Node.h"
#include "jit/FlareJit.h"

using namespace llvm;

int main(int argc, char **argv) {
    lang::Driver driver;
    std::string fileName = "../../samples/1.ts";

    if (argc > 1) {
        fileName = argv[1];
    } else {
        std::clog << "No file name supplied. Since it is a debug build a default test program will be executed.\n";
    }

    try {
        driver.parseFile(fileName);
    } catch (char const *e) {
        std::cerr << "Error occurred while parsing : " << e;
        return 1;
    }

    // Execute JIT
    flare::jit::FlareJit jit(module);
    jit.initialize();
    jit.execute();

    return jit.getExitCode();
}
