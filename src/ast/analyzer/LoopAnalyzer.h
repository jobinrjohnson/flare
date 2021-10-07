//
// Created by jobinrjohnson on 07/10/21.
//

#ifndef FLARE_LOOPANALYZER_H
#define FLARE_LOOPANALYZER_H

#include <vector>

namespace flare::ast {
    class Node;

    class LoopAnalyzer {
        Node *statementList;

    public:
        explicit LoopAnalyzer(Node *smtL) {
            this->statementList = smtL;
        }

        bool isParallizable() {
            return false;
        }

        std::vector<Node *> getPrivatizationVars() {
            std::vector<Node *> pVars;
            return pVars;
        }

    };
}


#endif //FLARE_LOOPANALYZER_H
