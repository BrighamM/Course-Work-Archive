#ifndef REGISTER_LIST_HPP
#define REGISTER_LIST_HPP

#include "./AbstractRegisterList.hpp"
#include <iostream>

namespace ASTNamespace
{
class RegisterList : public AbstractRegisterList
{
  public:
    RegisterList()
        : zeroRegister("$zero"), v_Zero("$v0"), v_One("$v1"), a_Zero("$a0"), a_One("$a1"),
          a_Two("$a2"), a_Three("$a3"), t_Zero("$t0"), t_One("$t1"), t_Two("$t2"), t_Three("$t3"),
          t_Four("$t4"), t_Five("$t5"), t_Six("$t6"), t_Seven("$t7"), t_Eight("$t8"), t_Nine("$t9"),
          s_Zero("$s0"), s_One("$s1"), s_Two("$s2"), s_Three("$s3"), s_Four("$s4"), s_Five("$s5"),
          s_Six("$s6"), s_Seven("$s7"), globalPointer("$gp"), stackPointer("$sp"),
          framePointer("$fp"), returnAddress("$ra")
    {
    }

    std::string getGlobalPointerRegister() const { return globalPointer; }

    std::string getV_ZeroRegister() const { return v_Zero; }

    std::string getZeroRegister() const { return zeroRegister; }

    std::string getA_ZeroRegister() const { return a_Zero; }

    std::string getStackPointerRegister() const { return stackPointer; }

    std::string getFramePointerRegister() const { return framePointer; }

    std::string getReturnAddressRegister() const { return returnAddress; }

    void spillRegisters()
    {
        int totalSizeNeeded = 26 * 4;
        std::cout << std::endl;
        std::cout << "# SPILLING REGISTERS " << std::endl;
        std::cout << "addi " << stackPointer << " " << stackPointer << " -" << totalSizeNeeded
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << framePointer << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << returnAddress << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << v_Zero << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << v_One << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << a_Zero << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << a_One << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << a_Two << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << a_Three << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Zero << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_One << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Two << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Three << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Four << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Five << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Six << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << s_Seven << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Zero << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_One << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Two << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Three << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Four << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Five << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Six << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Seven << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Eight << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        totalSizeNeeded -= 4;

        std::cout << "sw " << t_Nine << " " << totalSizeNeeded << "(" << stackPointer << ")"
                  << std::endl;
        std::cout << std::endl;
    }
    void unSpillRegisters(bool isFunctionCall = false)
    {
        int currOffSet = 0;
        std::cout << std::endl;
        std::cout << "# UNSPILLING REGISTERS " << std::endl;
        std::cout << "lw " << t_Nine << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Eight << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Seven << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Six << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Five << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Four << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Three << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Two << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_One << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << t_Zero << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        if (isFunctionCall)
        {
        }
        else
        {
            std::cout << "lw " << s_Seven << " " << currOffSet << "(" << stackPointer << ")"
                      << std::endl;
        }
        currOffSet += 4;

        std::cout << "lw " << s_Six << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << s_Five << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << s_Four << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << s_Three << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << s_Two << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << s_One << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << s_Zero << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << a_Three << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << a_Two << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << a_One << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << a_Zero << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << v_One << " " << currOffSet << "(" << stackPointer << ")" << std::endl;
        currOffSet += 4;

        std::cout << "lw " << v_Zero << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << returnAddress << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "lw " << framePointer << " " << currOffSet << "(" << stackPointer << ")"
                  << std::endl;
        currOffSet += 4;

        std::cout << "addi " << stackPointer << " " << stackPointer << " " << currOffSet
                  << std::endl;

        std::cout << std::endl;
    }

  private:
    std::string zeroRegister;
    std::string v_Zero;
    std::string v_One;
    std::string a_Zero;
    std::string a_One;
    std::string a_Two;
    std::string a_Three;
    std::string t_Zero;
    std::string t_One;
    std::string t_Two;
    std::string t_Three;
    std::string t_Four;
    std::string t_Five;
    std::string t_Six;
    std::string t_Seven;
    std::string t_Eight;
    std::string t_Nine;
    std::string s_Zero;
    std::string s_One;
    std::string s_Two;
    std::string s_Three;
    std::string s_Four;
    std::string s_Five;
    std::string s_Six;
    std::string s_Seven;
    std::string globalPointer;
    std::string stackPointer;
    std::string framePointer;
    std::string returnAddress;
};
} // namespace ASTNamespace

extern ASTNamespace::RegisterList globalRegisterList;

#endif