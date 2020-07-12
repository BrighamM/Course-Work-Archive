#ifndef ABSTRACT_PSUEDO_REGISTER_HPP
#define ABSTRACT_PSUEDO_REGISTER_HPP

#include "./RegisterPool.hpp"
#include <string>

namespace ASTNamespace
{
class AbstractPsuedoRegister
{
  public:
    virtual std::string getRegisterName() const = 0;
};
} // namespace ASTNamespace

#endif
