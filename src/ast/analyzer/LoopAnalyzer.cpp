//
// Created by jobinrjohnson on 07/10/21.
//

#include "LoopAnalyzer.h"
#include <ast/StatementListNode.h>
#include <ast/ExprNode.h>
#include <ast/AssignmentNode.h>
#include <ast/LoopNode.h>

namespace flare::ast {

    Context *globalContext;
    LoopNode *mLoopNode;
    std::vector<Node *> lopStatementLists;


    bool isVarInside(StatementListNode *list, std::string name) {
        VarDeclNode *variable = nullptr;
        auto i = lopStatementLists.end();
        while (i != lopStatementLists.begin()) {
            auto *node = dynamic_cast<StatementListNode *>(*(--i));
            variable = node->findLocal(name);
            if (variable != nullptr) {
                return true;
            }
        }
        return false;
    }

    void LoopAnalyzer::analyze() {

        LoopAnalyzer *analysis = nullptr;

        if (this->node->getNodeType() == NodeType::STATEMENT_LIST_NODE) {
            auto mNode = dynamic_cast<StatementListNode *>(this->node);
            for (auto x: mNode->statements) {
                analysis = new LoopAnalyzer(x);
                if (!analysis->isParallizable()) {
                    break;
                }
            }
        } else if (this->node->getNodeType() == NodeType::ASSIGNMENT_NODE) {
            this->analyzeAssignment();
            return;
        } else if (this->node->getNodeType() == NodeType::EXPR_NODE) {
            this->analyzeExprNode();
            return;
        } else if (this->node->getNodeType() == NodeType::VAR_DEREF_NODE) {
            this->analyzeVarDerefNode();
            return;
        }

        if (analysis == nullptr) {
            std::cerr << "Analysis Skipped";
            return;
        }

        if (!analysis->isParallizable()) {
            this->_isParallizable = false;
        }

    }

    void LoopAnalyzer::analyzeAssignment() {
        this->_isParallizable = false;
        auto mNode = dynamic_cast<AssignmentNode *>(this->node);
        if (mNode->index != nullptr) {
            // array assignment
        } else {
            if (isVarInside(dynamic_cast<StatementListNode *>(mLoopNode->statementList), mNode->varName)) {
                this->_isParallizable = true;
                return;
            }
        }
    }

    void LoopAnalyzer::analyzeExprNode() {

        auto mNode = dynamic_cast<ExprNode *>(this->node);
        if (mNode->opr == OperatorType::GROUPED) {
            this->node = mNode->operands[0];
            this->analyze();
        }
    }

    void LoopAnalyzer::analyzeVarDerefNode() {

    }

}