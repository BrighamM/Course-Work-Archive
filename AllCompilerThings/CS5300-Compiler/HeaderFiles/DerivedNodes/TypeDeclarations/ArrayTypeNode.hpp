#ifndef ARRAY_TYPE_NODE_HPP
#define ARRAY_TYPE_NODE_HPP

#include "../ExpressionNodes/ExpressionNode.hpp"
#include "../TypeNode.hpp"

// ArrayType : ARRAY_TOKEN LEFT_BRACKET_TOKEN Expression COLON_TOKEN Expression RIGHT_BRACKET_TOKEN
// OF_TOKEN Type {$$ = new ASTNamespace::ArrayTypeNode($3,$5,$8);};

namespace ASTNamespace
{
class ArrayTypeNode : public TypeNode
{
    ExpressionNode* leftExpression;
    ExpressionNode* rightExpression;
    TypeNode* type;

  public:
    ArrayTypeNode(ExpressionNode* inputLhs, ExpressionNode* inputRhs, TypeNode* incomingType)
        : leftExpression(inputLhs), rightExpression(inputRhs), type(incomingType)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual std::shared_ptr<SymbolTableType> getSymbolTableType() const
    {
        int lb = leftExpression->getIntValue();
        int ub = rightExpression->getIntValue();
        // std::shared_ptr<SymbolTableType> arrayElementType =
        //     globalSymbolTable.getTypeType(type->toString());
        std::shared_ptr<SymbolTableArrayType> specificArrayTypePointer =
            std::make_shared<SymbolTableArrayType>(type->getSymbolTableType(), lb, ub);
        // std::cout << "THIRD thing that happens ARRAY TYPE NODE....ARRELEMENTSIZE: "
        //           << arrayElementType->size() << std::endl;
        return specificArrayTypePointer;
    }
    virtual void emitSource() const
    {
        std::cout << "ARRAY[";
        leftExpression->emitSource();
        std::cout << ":";
        rightExpression->emitSource();
        std::cout << "] OF ";
        type->emitSource();
    }
    virtual std::shared_ptr<SymbolTableType> getSymbolTableTypeForVarDecl() const
    {
        int lb = leftExpression->getIntValue();
        int ub = rightExpression->getIntValue();
        // std::shared_ptr<SymbolTableType> arrayElementType =
        //     globalSymbolTable.getTypeType(type->toString());
        std::shared_ptr<SymbolTableArrayType> specificArrayTypePointer =
            std::make_shared<SymbolTableArrayType>(type->getSymbolTableType(), lb, ub);
        // std::cout << "THIRD thing that happens ARRAY TYPE NODE....ARRELEMENTSIZE: "
        //           << arrayElementType->size() << std::endl;
        return specificArrayTypePointer;
    }
    ~ArrayTypeNode()
    {
        delete leftExpression;
        leftExpression = 0;
        delete rightExpression;
        rightExpression = 0;
        delete type;
        type = 0;
    }
};
} // namespace ASTNamespace

#endif