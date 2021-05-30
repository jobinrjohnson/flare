//
// Created by jobinrjohnson on 27/05/21.
//

#include <string>
#include <iostream>
#include <sstream>
#include <flare.h>

int EXPECTED_EXIT_CODE = 2;

std::string CODE = R"(

function main(): int {
    return 1 + 1;
}

)";

int main() {

    std::stringstream ss;
    ss.str(CODE);

    // Execute
    flare::Flare f;
    f.setInputStream(ss);
    f.parseStream();
    f.codeGenAst();

    f.printLLVMIR();

    f.executeJit();

    // Assert
    if (f.getExitCode() != EXPECTED_EXIT_CODE) {
        return 1;
    }

    return 0;

}
