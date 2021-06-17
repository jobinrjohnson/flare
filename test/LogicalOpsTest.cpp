//
// Created by jobinrjohnson on 16/06/21.
//

#include <string>
#include <iostream>
#include <sstream>
#include <flare.h>

int EXPECTED_EXIT_CODE = 3;

std::string CODE = R"(

function main(): int {
    let totalTrueConds: int = 0;

    let x: int = 0;
    if (x == 0 && x != 0) {
        totalTrueConds = totalTrueConds + 1;
    } else if (x == 0 || x != 0) {
        totalTrueConds = totalTrueConds + 1;
    }

    let j = 0;
    let k = 10;

    if (((j + k) == 10 && ((j == 10 && k == 0) || (k == 10 && j == 0))) || ((j * k) == 0 && (k == 0 || j == 0))) {
        totalTrueConds = totalTrueConds + 1;
    }

    if (j == k - 10 && k == j - 10) {
        totalTrueConds = totalTrueConds + 1;
    }

    if (j == k - 10 || k == j - 10) {
        totalTrueConds = totalTrueConds + 1;
    }

    if (!((j + k) == 10 && ((j == 10 && k == 0) || (k == 10 && j == 0))) || !((j * k) == 0 && (k == 0 || j == 0))) {
        totalTrueConds = totalTrueConds + 1;
    }

    return totalTrueConds;
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
