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

    void Driver::setAstRoot(flare::ast::Node *node) {
        this->astRoot = node;
    }

    flare::ast::Node *Driver::getAstRoot() {
        return this->astRoot;
    }

    void Driver::setInputStream(std::istream &stream) {
        this->sourceStream = &stream;
    }

    flare::ast::Node *Driver::parse() {

        if (this->sourceStream->bad()) {
            throw "Some error occurred while opening the stream.";
        }

        this->scanner->switch_streams(this->sourceStream, &std::cerr);
#ifdef FLARE_DEBUG
//        this->scanner->setDebug(true);
#endif

        // TODO use proper init
        cursor->lines();

        this->parser->parse();

        return this->getAstRoot();
    }

} // namespace lang
