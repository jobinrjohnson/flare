#include "lang/driver.h"


int main() {
    lang::Driver driver;
    // driver.parse();
    std::string fileName = "../../samples/1.program";
    driver.parseFile(fileName);

    return 0;
}
