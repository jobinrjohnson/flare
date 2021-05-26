//
// Created by Jobin Johnson on 31/05/20.
//

#include "driver.h"
#include "parser.hh"
#include "scanner.h"

namespace lang {

    Driver::Driver()
            : scanner(new Scanner()), parser(new Parser(*this)),
              cursor(new location()) {}

    int Driver::parseFile(std::string &path) {

        std::ifstream file(path.c_str(), std::ifstream::in);

        if (!file.is_open()) {
            throw "Some error occurred while opening the file.";
        }

        this->scanner->switch_streams(&file, &std::cerr);

        // TODO use proper init
        cursor->lines();

        this->parser->parse();

        this->scanner->setDebug(true);

        file.close();
        return 0;
    }

    Driver::~Driver() {
        delete parser;
        delete scanner;
        delete cursor;
    }

    void Driver::stepCursor() {
        this->cursor->step();
    }

    location *Driver::getCursor() {
        return this->cursor;
    }

    int Driver::getError() {
        return this->error_;
    }

    void Driver::setError(int err) {
        this->error_ = err;
    }

} // namespace lang
