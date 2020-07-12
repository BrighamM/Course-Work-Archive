#ifndef STRING_CONSTANTS_HPP
#define STRING_CONSTANTS_HPP

#include "./AbstractStringConstants.hpp"
#include <algorithm>

namespace ASTNamespace
{
class StringConstants : public AbstractStringConstants
{
  public:
    StringConstants() {}
    // std::string getUnifiedStringName(std::string inputString)
    // {
    //     std::string originalCopy(inputString);
    //     std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
    //     if ((inputString == INTSTRING1) || (inputString == INTSTRING2_RETURN))
    //     {
    //         return INTSTRING2_RETURN;
    //     }
    //     else if ((inputString == BOOLSTRING1) || (inputString == BOOLSTRING2_RETURN))
    //     {
    //         return BOOLSTRING2_RETURN;
    //     }
    //     else if ((inputString == CHARSTRING1) || (inputString == CHARSTRING2_RETURN))
    //     {
    //         return CHARSTRING2_RETURN;
    //     }
    //     else if (inputString == STRINGSTRING1_RETURN)
    //     {
    //         return STRINGSTRING1_RETURN;
    //     }
    //     else if (inputString == TRUESTRING1_RETURN)
    //     {
    //         return TRUESTRING1_RETURN;
    //     }
    //     else if (inputString == FALSESTRING1_RETURN)
    //     {
    //         return FALSESTRING1_RETURN;
    //     }
    //     else
    //     {
    //         return originalCopy;
    //     }
    // }

    // bool isPrimitive(std::string inputString)
    // {
    //     std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
    //     if ((inputString == INTSTRING1) || (inputString == INTSTRING2_RETURN))
    //     {
    //         return true;
    //     }
    //     else if ((inputString == BOOLSTRING1) || (inputString == BOOLSTRING2_RETURN))
    //     {
    //         return true;
    //     }
    //     else if ((inputString == CHARSTRING1) || (inputString == CHARSTRING2_RETURN))
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    // int getPrimitiveSize(std::string inputString)
    // {
    //     std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
    //     if ((inputString == INTSTRING1) || (inputString == INTSTRING2_RETURN))
    //     {
    //         return 4;
    //     }
    //     else if ((inputString == BOOLSTRING1) || (inputString == BOOLSTRING2_RETURN))
    //     {
    //         return 4;
    //     }
    //     else if ((inputString == CHARSTRING1) || (inputString == CHARSTRING2_RETURN))
    //     {
    //         return 4;
    //     }
    //     else
    //     {
    //         return -1;
    //     }
    // }
    int getByteSizeFourInt() { return BYTESIZEFOURINT; }
    int getTrueIntValue() { return TRUEINTVALUE; }
    int getFalseIntValue() { return FALSEINTVALUE; }

    std::string getLowerCaseIntString() { return LCINTSTRING; }
    std::string getUpperCaseIntString() { return UCINTSTRING; }

    std::string getLowerCaseIntegerString() { return LCINTEGERSTRING; }
    std::string getUpperCaseIntegerString() { return UCINTEGERSTRING; }

    std::string getLowerCaseBoolString() { return LCBOOLSTRING; }
    std::string getUpperCaseBoolString() { return UCBOOLSTRING; }

    std::string getLowerCaseBooleanString() { return LCBOOLEANSTRING; }
    std::string getUpperCaseBooleanString() { return UCBOOLEANSTRING; }

    std::string getLowerCaseCharString() { return LCCHARSTRING; }
    std::string getUpperCaseCharString() { return UCCHARSTRING; }

    std::string getLowerCaseCharacterString() { return LCCHARACTERSTRING; }
    std::string getUpperCaseCharacterString() { return UCCHARACTERSTRING; }

    std::string getLowerCaseStringString() { return LCSTRINGSTRING; }
    std::string getUpperCaseStringString() { return UCSTRINGSTRING; }
    std::string getLowerCaseTrueString() { return LCTRUESTRING; }
    std::string getLowerCaseFalseString() { return LCFALSESTRING; }

  private:
    const std::string LCINTSTRING = "int";
    const std::string UCINTSTRING = "INT";
    const std::string LCINTEGERSTRING = "integer";
    const std::string UCINTEGERSTRING = "INTEGER";
    const std::string LCBOOLSTRING = "bool";
    const std::string UCBOOLSTRING = "BOOL";
    const std::string LCBOOLEANSTRING = "boolean";
    const std::string UCBOOLEANSTRING = "BOOLEAN";
    const std::string LCCHARSTRING = "char";
    const std::string UCCHARSTRING = "CHAR";
    const std::string LCCHARACTERSTRING = "character";
    const std::string UCCHARACTERSTRING = "CHARACTER";
    const std::string LCSTRINGSTRING = "string";
    const std::string UCSTRINGSTRING = "STRING";

    const std::string LCTRUESTRING = "true";
    const std::string UCTRUESTRING = "TRUE";
    const std::string LCFALSESTRING = "false";
    const std::string UCFALSESTRING = "FALSE";

    const std::string TRUESTRINGVALUE = "1";
    const std::string FALSESTRINGVALUE = "0";

    const int TRUEINTVALUE = 1;
    const int FALSEINTVALUE = 0;
    const int BYTESIZEFOURINT = 4;
};
} // namespace ASTNamespace

extern ASTNamespace::StringConstants globalStringConstants;

#endif