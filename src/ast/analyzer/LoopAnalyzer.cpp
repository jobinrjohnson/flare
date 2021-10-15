//
// Created by jobinrjohnson on 07/10/21.
//

#include "LoopAnalyzer.h"
#include <ast/StatementListNode.h>
#include <ast/ExprNode.h>
#include <ast/AssignmentNode.h>
#include <ast/LoopNode.h>
#include <ast/VariableDerefNode.h>
#include <ast/FunctionNode.h>
#include <ast/FunctionCallNode.h>
#include <ast/EmptyNode.h>

#define ENABLE_AUTO_PARALLIZATION true

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
                    this->privatizeList.clear();
                    break;
                } else {
                    this->privatizeList.insert(privatizeList.end(), analysis->privatizeList.begin(),
                                               analysis->privatizeList.end());
                }
//
//                for (auto i: this->privatizeList) {
//                    auto x2 = dynamic_cast<VariableDerefNode *>(i);
//                    std::cout << x2->variableName << "==\n\n";
//                    std::cout.flush();
//                }

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
        } else if (this->node->getNodeType() == NodeType::FUNCTION_CALL_NODE) {
            this->analyzeFunCallNode();
            return;
        } else if (this->node->getNodeType() == NodeType::VAR_DECL_NODE) {
            this->analyzeVarDeclNode();
            return;
        }

        if (analysis == nullptr) {
            std::cerr << "Analysis Skipped for : " << node->getNodeType() << "\n";
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
//            this->_isParallizable = true;
//            this->privatizeList.push_back(mNode->base.c_str());
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
        } else if (mNode->opr == VAR_DE_REF || mNode->opr == FUNCTION_CALL) {
            this->node = mNode->operands[0];
            this->analyze();
        } else {
            for (auto x: mNode->operands) {
                auto nanalysis = new LoopAnalyzer(x);
                if (!nanalysis->isParallizable()) {
                    this->privatizeList.clear();
                    this->_isParallizable = false;
                    break;
                } else {
                    this->privatizeList.insert(privatizeList.end(), nanalysis->privatizeList.begin(),
                                               nanalysis->privatizeList.end());
                }
            }

        }
    }

    void LoopAnalyzer::analyzeVarDerefNode() {

        std::cout.flush();
        auto mNode = dynamic_cast<VariableDerefNode *>(this->node);
        if (mNode->isArrayDeReference) {

            auto an = new LoopAnalyzer(mNode->arrayIndex);
            if (!an->isParallizable()) {
                this->_isParallizable = false;
                return;
            } else {
                this->privatizeList.insert(privatizeList.end(), an->privatizeList.begin(),
                                           an->privatizeList.end());
            }

        }

        if (!isVarInside(dynamic_cast<StatementListNode *>(mLoopNode->statementList), mNode->variableName)) {
            this->privatizeList.push_back(mNode->variableName);
        }

    }

    void LoopAnalyzer::analyzeFunCallNode() {
        auto mNode = dynamic_cast<FunctionCallNode *>(this->node);
        for (auto n: *mNode->argumentList) {

            auto analysis = new LoopAnalyzer(n);
            if (!analysis->isParallizable()) {
                this->privatizeList.clear();
                break;
            } else {
                this->privatizeList.insert(privatizeList.end(), analysis->privatizeList.begin(),
                                           analysis->privatizeList.end());
            }

        }

    }

    void LoopAnalyzer::analyzeVarDeclNode() {
        auto mNode = dynamic_cast<VarDeclNode *>(this->node);
        if (mNode->hasInitializer()) {
            this->node = mNode->getInitializer();
            this->analyze();
        }
    }

    bool LoopAnalyzer::isParallizable() {

        if (!ENABLE_AUTO_PARALLIZATION) {
            return false;
        }

        if (!this->analysisComplete) {
            this->analyze();
            this->analysisComplete = true;
        }
//            return false;
        return this->_isParallizable;
    }

}