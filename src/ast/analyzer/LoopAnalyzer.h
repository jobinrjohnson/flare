//
// Created by jobinrjohnson on 07/10/21.
//

#ifndef FLARE_LOOPANALYZER_H
#define FLARE_LOOPANALYZER_H

#include <vector>
#include <ast/helpers/Context.h>

namespace flare::ast {
    class Node;

    class LoopAnalyzer {
        Node *node;

        bool analysisComplete = false;

        bool _isParallizable = true;

    private:

        void analyze();

        void analyzeAssignment();

        void analyzeExprNode();

        void analyzeVarDerefNode();

    public:
        explicit LoopAnalyzer(Node *smtL) {
            this->node = smtL;
        }

        bool isParallizable() {
            if (!this->analysisComplete) {
                this->analyze();
            }
            return this->_isParallizable;
        }

        std::vector<Node *> getPrivatizationVars() {
            std::vector<Node *> pVars;
            return pVars;
        }

    };
}


#endif //FLARE_LOOPANALYZER_H
