#ifndef REGISTER_POOL_HPP
#define REGISTER_POOL_HPP

#include "./AbstractRegisterPool.hpp"
#include <vector>

namespace ASTNamespace
{
class RegisterPool : public AbstractRegisterPool
{
  public:
    RegisterPool()
    {
        poolOfRegisters.emplace_back("$t0");
        poolOfRegisters.emplace_back("$t1");
        poolOfRegisters.emplace_back("$t2");
        poolOfRegisters.emplace_back("$t3");
        poolOfRegisters.emplace_back("$t4");
        poolOfRegisters.emplace_back("$t5");
        poolOfRegisters.emplace_back("$t6");
        poolOfRegisters.emplace_back("$t7");
        poolOfRegisters.emplace_back("$t8");
        poolOfRegisters.emplace_back("$t9");
        poolOfRegisters.emplace_back("$s0");
        poolOfRegisters.emplace_back("$s1");
        poolOfRegisters.emplace_back("$s2");
        poolOfRegisters.emplace_back("$s3");
        poolOfRegisters.emplace_back("$s4");
        poolOfRegisters.emplace_back("$s5");
        poolOfRegisters.emplace_back("$s6");
        poolOfRegisters.emplace_back("$s7");
        // poolOfRegisters ordering is $t0, $t1,...,$s6,$s7
    }

    virtual std::string requestRegister()
    {
        std::string firstRegister;
        firstRegister = poolOfRegisters[0];
        poolOfRegisters.erase(poolOfRegisters.begin());
        return firstRegister;
    }

    std::string getLastRegister()
    {
        std::string lastRegister;
        lastRegister = poolOfRegisters[poolOfRegisters.size() - 1];
        poolOfRegisters.pop_back();
        return lastRegister;
    }

    virtual void returnRegister(std::string returningRegister)
    {
        poolOfRegisters.insert(poolOfRegisters.begin(), returningRegister);
    }
    void returnLastRegister(std::string returningRegister)
    {
        poolOfRegisters.emplace_back(returningRegister);
    }

  private:
    std::vector<std::string> poolOfRegisters;
};
} // namespace ASTNamespace

extern ASTNamespace::RegisterPool globalRegisterPool;

#endif
