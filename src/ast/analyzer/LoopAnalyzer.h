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

        std::vector<Node *> privatizeList;

        bool analysisComplete = false;

        bool _isParallizable = true;

    private:

        void analyze();

        void analyzeAssignment();

        void analyzeExprNode();

        void analyzeVarDerefNode();

        void analyzeFunCallNode();

    public:
        explicit LoopAnalyzer(Node *smtL) {
            this->node = smtL;
        }

        bool isParallizable();

        std::vector<Node *> getPrivatizationVars() {
            if (!this->analysisComplete) {
                this->analyze();
                this->analysisComplete = true;
            }
            return privatizeList;
        }

    };
}


#endif //FLARE_LOOPANALYZER_H
