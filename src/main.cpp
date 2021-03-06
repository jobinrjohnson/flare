#include <flare.h>

int main(int argc, char **argv) {
    std::string fileName;

    if (argc > 1) {
        fileName = argv[1];
    } else {
#ifdef FLARE_DEBUG
        fileName = "../../samples/1.ts";
        std::clog << "No file name supplied. Since it is a debug build a default test program will be executed.\n\n";
        std::clog.flush();
#else
        std::cerr << "No file name supplied\n";
        return 1;
#endif
    }

    std::ifstream file(fileName.c_str(), std::ifstream::in);

    if (!file.is_open()) {
        std::cerr << "Some error occurred while opening the file.";
        return 1;
    }

    flare::Flare f;

#ifndef FLARE_DEBUG
    f.executeStream(file, fileName);
    // Print LLVM IR if debug mode is on
    std::cout << "========================================\n";
    f.printLLVMIR();
    std::cout << "========================================\n\n";
#else
    f.setInputStream(file, fileName);
    f.parseStream();
    f.codeGenAst();
    std::cout << "========================================\n";
    f.printLLVMIR();
    std::cout << "========================================\n\n";
    f.executeJit();
#endif

    return f.getExitCode();

}
