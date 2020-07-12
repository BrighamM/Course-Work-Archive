#ifndef ABSTRACT_REGISTER_POOL_HPP
#define ABSTRACT_REGISTER_POOL_HPP

#include <string>

namespace ASTNamespace
{
class AbstractRegisterPool
{
  public:
    virtual std::string requestRegister() = 0;
};
} // namespace ASTNamespace

#endif
