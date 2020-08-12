#include "lang/driver.h"
#include "ast/Node.h"
#include "jit/FlareJit.h"

using namespace llvm;

int main() {
    lang::Driver driver;
    std::string fileName = "../../samples/1.program";
    driver.parseFile(fileName);

    // Execute JIT
    FlareJit jit(module);
    jit.initialize();
    jit.execute();

    return jit.getExitCode();
}
