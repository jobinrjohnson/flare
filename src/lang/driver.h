//
// Created by Jobin Johnson on 31/05/20.
//

#ifndef FLARE_DRIVER_H
#define FLARE_DRIVER_H

//namespace flare::ast{
//    class Node;
//}

#include <ast/Node.h>

#include <fstream>
#include <iostream>
#include <string>

namespace lang {

    class Parser;

    class Scanner;

    class location;

    class Driver {

    public:
        Driver();

        ~Driver();

        void setInputStream(std::istream &stream);

        flare::ast::Node *parse();

        void stepCursor();

        location *getCursor();

        int getError();

        void setError(int);

        void setAstRoot(flare::ast::Node *);

        flare::ast::Node *getAstRoot();

    private:
        Scanner *scanner;
        Parser *parser;
        location *cursor;

        flare::ast::Node *astRoot;

        std::istream *sourceStream;

        int error_;

        friend class Parser;

        friend class Scanner;
    };

} // namespace lang

#endif // FLARE_DRIVER_H
