#ifndef PSUEDO_REGISTER_HPP
#define PSUEDO_REGISTER_HPP

#include "./AbstractPsuedoRegister.hpp"

namespace ASTNamespace
{
class PsuedoRegister : public AbstractPsuedoRegister
{
  public:
    PsuedoRegister() : isFunctionCall(false)
    {
        registerName = globalRegisterPool.requestRegister();
    }
    PsuedoRegister(bool isFCall) : isFunctionCall(isFCall)
    {
        registerName = globalRegisterPool.getLastRegister();
    }
    ~PsuedoRegister()
    {
        if (isFunctionCall)
        {
            globalRegisterPool.returnLastRegister(registerName);
        }
        else
        {
            globalRegisterPool.returnRegister(registerName);
        }
    }

    virtual std::string getRegisterName() const { return registerName; }

  private:
    std::string registerName;
    bool isFunctionCall;
};
} // namespace ASTNamespace

#endif
