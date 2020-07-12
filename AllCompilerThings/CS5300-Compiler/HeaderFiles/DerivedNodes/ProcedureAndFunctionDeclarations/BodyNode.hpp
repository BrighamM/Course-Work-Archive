#ifndef BODY_NODE_HPP
#define BODY_NODE_HPP

#include "../../AbstractNode.hpp"
#include "../ConstantDeclarations/ConstantDeclNode.hpp"
#include "../TypeDeclarations/TypeDeclNode.hpp"
#include "../VariableDeclarations/VarDeclNode.hpp"
#include "BlockNode.hpp"

// Body : ConstantDeclsList TypeDeclsList VarDeclsList Block {$$ = new
// ASTNamespace::BodyNode($1,$2,$3,$4);};

namespace ASTNamespace
{
class BodyNode : public AbstractNode
{
    std::vector<ConstantDeclNode*>* constsList;
    std::vector<TypeDeclNode*>* typesList;
    std::vector<VarDeclNode*>* varsList;
    BlockNode* blockNode;

  public:
    BodyNode(std::vector<ConstantDeclNode*>* inputConstList,
             std::vector<TypeDeclNode*>* inputTypeList, std::vector<VarDeclNode*>* inputVarList,
             BlockNode* inputBlock)
        : constsList(inputConstList), typesList(inputTypeList), varsList(inputVarList),
          blockNode(inputBlock)
    {
    }
    virtual void emit() const
    {
        if (constsList)
        {
            std::vector<ConstantDeclNode*> inlineConstsList = *constsList;
            for (int i = 0; i < inlineConstsList.size(); i++)
            {
                inlineConstsList[i]->emit();
            }
        }
        if (typesList)
        {
            std::vector<TypeDeclNode*> inlineTypesList = *typesList;
            for (int i = 0; i < inlineTypesList.size(); i++)
            {
                inlineTypesList[i]->emit();
            }
        }
        if (varsList)
        {
            std::vector<VarDeclNode*> inlineVarsList = *varsList;
            for (int i = 0; i < inlineVarsList.size(); i++)
            {
                inlineVarsList[i]->emit();
            }
        }
        blockNode->emit();
    }
    virtual void emitSource() const
    {
        if (constsList != NULL)
        {
            std::cout << "CONST" << std::endl;
            std::vector<ConstantDeclNode*> inlineConstsList = *constsList;
            for (int i = 0; i < inlineConstsList.size(); i++)
            {
                inlineConstsList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        if (typesList != NULL)
        {
            std::cout << "TYPE" << std::endl;
            std::vector<TypeDeclNode*> inlineTypesList = *typesList;
            for (int i = 0; i < inlineTypesList.size(); i++)
            {
                inlineTypesList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        if (varsList != NULL)
        {
            std::cout << "VAR" << std::endl;
            std::vector<VarDeclNode*> inlineVarsList = *varsList;
            for (int i = 0; i < inlineVarsList.size(); i++)
            {
                inlineVarsList[i]->emitSource();
            }
            std::cout << std::endl;
        }

        blockNode->emitSource();
    }
    ~BodyNode()
    {
        delete constsList;
        constsList = 0;
        delete typesList;
        typesList = 0;
        delete varsList;
        varsList = 0;
        delete blockNode;
        blockNode = 0;
    }
};
} // namespace ASTNamespace

#endif