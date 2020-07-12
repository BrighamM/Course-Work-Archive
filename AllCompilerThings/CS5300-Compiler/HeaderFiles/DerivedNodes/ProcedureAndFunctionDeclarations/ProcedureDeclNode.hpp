#ifndef PROCEDURE_DECL_NODE_HPP
#define PROCEDURE_DECL_NODE_HPP

#include "BodyNode.hpp"
#include "FormalParametersListTypeNode.hpp"
#include "ProcedureAndFunctionDeclNode.hpp"
#include "ProcedureSignatureNode.hpp"
#include <utility>

// ProcedureDecl : ProcedureSignature SEMICOLON_TOKEN FORWARD_TOKEN SEMICOLON_TOKEN {$$ = new
// ASTNamespace::ProcedureDeclNode($1);}
//               | ProcedureSignature SEMICOLON_TOKEN Body SEMICOLON_TOKEN          {$$ = new
//               ASTNamespace::ProcedureDeclNode($1,$3);};

namespace ASTNamespace
{
class ProcedureDeclNode : public ProcedureAndFunctionDeclNode
{
    ProcedureSignatureNode* procedureSignature;
    BodyNode* body; // if body == NULL THIS IS A FORWARD
  public:
    ProcedureDeclNode(ProcedureSignatureNode* inputSignature)
        : procedureSignature(inputSignature), body(NULL)
    {
    }
    ProcedureDeclNode(ProcedureSignatureNode* inputSignature, BodyNode* inputBody)
        : procedureSignature(inputSignature), body(inputBody)
    {
    }
    virtual void emit() const
    {
        std::cout << "" << std::endl;
        // First make a label?
        std::cout << procedureSignature->getProcedureName() << ":" << std::endl;

        std::cout << "or " << globalRegisterList.getFramePointerRegister() << " "
                  << globalRegisterList.getStackPointerRegister() << " "
                  << globalRegisterList.getZeroRegister() << std::endl;

        globalSymbolTable.pushNewScope();

        // std::vector<bool> myBooleanRefVector = globalSymbolTable.getProcedurePrototypeBoolVector(
        //     procedureSignature->getProcedureName());

        if (procedureSignature->hasParams())
        {
            std::vector<FormalParametersListTypeNode*> paramList =
                procedureSignature->getParametersList();
            for (int i = 0; i < paramList.size(); i++)
            {
                // bool listIsRef = paramList[i]->getRefBool();
                globalSymbolTable.saveVarsListToSymbolTable(
                    paramList[i]->getStringIdentityList(), paramList[i]->getParamListType(),
                    paramList[i]->getParamListType()->size(),
                    globalRegisterList.getFramePointerRegister());
            }
        }

        // if (procedureSignature->hasParams())
        // {
        //     std::vector<std::string> theListINeed;
        //     std::vector<FormalParametersListTypeNode*> paramList =
        //         procedureSignature->getParametersList();
        //     for (int i = 0; i < paramList.size(); i++)
        //     {

        //         // bool listIsRef = paramList[i]->getRefBool();
        //         std::vector<std::string> tempIDList = paramList[i]->getStringIdentityList();
        //         for (int i = 0; i < tempIDList.size(); i++)
        //         {
        //             theListINeed.emplace_back(tempIDList[i]);
        //         }
        //     }

        //     for (int i = 0; i < theListINeed.size(); i++)
        //     {
        //         // std::shared_ptr<SymbolTableType> myTempType =
        //         //     globalSymbolTable.getVarConstType(theListINeed[i]);
        //         // std::string baseRegister =
        //         //     globalSymbolTable.getVarIdentierBaseRegister(theListINeed[i]);
        //         // int baseRegisterOffset =
        //         //     globalSymbolTable.getVarIdentifierBaseRegisterOffSet(theListINeed[i]);
        //         // PsuedoRegister psuedoRegister;
        //         // std::cout << "lw " << psuedoRegister.getRegisterName() << " " <<
        //         // baseRegisterOffset
        //         //           << "(" << globalRegisterList.getStackPointerRegister() << ")"
        //         //           << std::endl;
        //         // std::cout << "sw " << psuedoRegister.getRegisterName() << " " <<
        //         // baseRegisterOffset
        //         //           << "(" << baseRegister << ")" << std::endl;
        //     }
        // }

        // (identifier,type)
        // std::vector<std::pair<std::string, std::shared_ptr<SymbolTableType>>> myInfoVector;
        // std::pair<std::string, std::shared_ptr<SymbolTableType>> unitPair;
        // unitPair = std::make_pair()

        // Now I have all the things done... now run?
        // Now I need to pull off the input args, from the stack
        // For example there are two items I need to pull off with swap.cpsl
        // the first thing I will pull off is a... so it better have been the
        // last thing that was pushed onto the stack

        // FOR EACH ARG, I NEED TO PULL THEIR DATA OFF THE STACK IN REVERSE DECLARED ORDER.
        /**
         * So for example, I am a procedure with the following args... myProcedure(a,b,c,...)
         * First I have the boolean vector that tells me whether some arg was passed
         * by reference or by value.
         *
         * So I am going to traverse my arg array in reverse... I should really draw a picture...
         */

        /**
         * WHEN I GET SOMETHING BY VALUE, I AM GOING PUT THAT THING ONTO THE SYMBOLTABLE, AND
         * THEN I AM GOING STORE THE VALUE I JUST RECEIVED FOR THAT THING, IN THE ADDRESS OF THAT
         * THING ON THE SYMBOLTABLE
         */
        body->emit();
        globalSymbolTable.popLastScope();
        std::cout << "jr " << globalRegisterList.getReturnAddressRegister() << std::endl;
    }
    virtual void emitSource() const
    {
        procedureSignature->emitSource();
        std::cout << ";";
        if (body == NULL)
        {
            std::cout << "FORWARD;" << std::endl;
        }
        else
        {
            std::cout << std::endl;
            body->emitSource();
            std::cout << ";" << std::endl;
        }
    }
    virtual void putPrototypeOnSymbolTable() const
    {
        std::string identifierForSymbolTable = procedureSignature->getProcedureName();
        std::vector<bool> myBoolVectorForSymbolTable;

        if (procedureSignature->hasParams())
        {
            std::vector<FormalParametersListTypeNode*> paramList =
                procedureSignature->getParametersList();
            for (int i = 0; i < paramList.size(); i++)
            {
                bool listIsRef = paramList[i]->getRefBool();
                std::vector<std::string> stringIdentityList = paramList[i]->getStringIdentityList();
                for (int j = 0; j < stringIdentityList.size(); j++)
                {
                    myBoolVectorForSymbolTable.emplace_back(listIsRef);
                }
            }
        }
        globalSymbolTable.storeProcedurePrototype(identifierForSymbolTable,
                                                  myBoolVectorForSymbolTable);
    }
    ~ProcedureDeclNode()
    {
        delete procedureSignature;
        procedureSignature = 0;
        delete body;
        body = 0;
    }
};
} // namespace ASTNamespace

#endif