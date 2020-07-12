#ifndef CHARCONST_EXPRESSION_NODE_HPP
#define CHARCONST_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

// CHARCONST_TOKEN {$$ = new ASTNamespace::CHARCONSTExpressionNode($1);};
namespace ASTNamespace
{
class CHARCONSTExpressionNode : public ExpressionNode
{
  public:
    CHARCONSTExpressionNode(char untouchedChar)
        : directCopy(1, untouchedChar), asciiVal(untouchedChar), charValue(untouchedChar)
    {
    }
    virtual void emit() const { std::cout << "" << std::endl; }
    virtual void emitSource() const { std::cout << "_ASCIIVAL_=> " << asciiVal; }
    int getAsciiVal() { return asciiVal; }
    char getCharVal() { return charValue; }
    std::string getStringVal() { return directCopy; }
    virtual PsuedoRegister getTheeIntoRegister() const
    {
        PsuedoRegister psuedoRegister;
        int tempIntChar = asciiVal;
        char tempCharChar = charValue;
        if (tempIntChar == 10)
        {
            std::cout << "li " << psuedoRegister.getRegisterName() << " "
                      << "\'"
                      << "\\n"
                      << "\'" << std::endl;
        }
        else if (tempIntChar == 9)
        {
            std::cout << "li " << psuedoRegister.getRegisterName() << " "
                      << "\'"
                      << "\\t"
                      << "\'" << std::endl;
        }
        else
        {
            std::cout << "li " << psuedoRegister.getRegisterName() << " "
                      << "\'" << tempCharChar << "\'" << std::endl;
        }
        return psuedoRegister;
    }
    virtual std::shared_ptr<SymbolTableType> getType() const { return SymbolTableCharType::get(); }

    // Virtuals for Constant Folding
    virtual int getIntValue() const { return false; }
    virtual std::string getStringValue() const { return ""; }
    virtual char getCharValue() const { return charValue; }
    virtual bool getBoolValue() const { return false; }
    ~CHARCONSTExpressionNode() {}

  private:
    std::string directCopy;
    char charValue;
    int asciiVal;
};
} // namespace ASTNamespace

#endif