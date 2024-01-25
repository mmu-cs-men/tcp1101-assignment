#pragma once
#include "MachineState.h"

class Runner
{
    public:
        Runner(MachineState &machineState);
        unsigned char getValueAtRegister(int registerNum);
        unsigned char getValueAtAddress(int addressNum);
        void in(int registerNum);
        void out(int registerNum);
        void inc(int registerNum);
        void dec(int registerNum);
        void mov(int value, int registerNum);
        void add(int firstRegisterNum, int secondRegisterNum);
        void sub(int firstRegisterNum, int secondRegisterNum);
        void mul(int firstRegisterNum, int secondRegisterNum);
        void div(int firstRegisterNum, int secondRegisterNum);
        void rol(int registerNum, unsigned char value);
        void ror(int registerNum, unsigned char value);
        void shl(int registerNum, unsigned char value);
        void shr(int registerNum, unsigned char value);
        void load(int registerNum, int addressNum);
        void store(int registerNum, int addressNum);

    private:
        MachineState &machineState;
};
