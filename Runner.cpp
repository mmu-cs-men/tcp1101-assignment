#include "Runner.h"
#include <cstdlib>
#include <iostream>

Runner::Runner(MachineState &machineState) : machineState(machineState)
{
}

void Runner::in(int registerNum)
{
    machineState.programCounter++; // there's gotta be a better way to do this

    int value;
    std::cin >> value;

    if (value < 0 || value > 255)
    {
        std::cout << "Error: Input value out of range" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    machineState.registers[registerNum] = static_cast<unsigned char>(value);
}

void Runner::out(int registerNum)
{
    machineState.programCounter++;

    unsigned char value = machineState.registers[registerNum];

    std::cout << static_cast<int>(value) << std::endl;
}

void Runner::inc(int registerNum)
{
    machineState.programCounter++;

    unsigned char currentValue = machineState.registers[registerNum];

    // Why would you do this??
    machineState.overflowFlag = machineState.zeroFlag = (currentValue == 255);

    machineState.registers[registerNum] = currentValue + 1;
}

void Runner::dec(int registerNum)
{
    machineState.programCounter++;

    unsigned char currentValue = machineState.registers[registerNum];

    machineState.underflowFlag = (currentValue == 0);
    machineState.zeroFlag = (currentValue == 1);

    machineState.registers[registerNum] = currentValue - 1;
}

// no program counter bcuz this is a helper functions for the parser
unsigned char Runner::getValueAtRegister(int registerNum)
{
    return machineState.registers[registerNum];
}

// no program counter bcuz this is a helper functions for the parser
// hmm, this should prob be in MachineState then... oh well
unsigned char Runner::getValueAtAddress(int addressNum)
{
    return machineState.memory[addressNum];
}

void Runner::mov(int value, int registerNum)
{
    machineState.programCounter++;
    machineState.registers[registerNum] = static_cast<unsigned char>(value);
}

void Runner::add(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    int result = machineState.registers[firstRegisterNum] +
                 machineState.registers[secondRegisterNum];

    machineState.overflowFlag = (result > 255);
    machineState.zeroFlag = (result % 256 == 0 || result == 0);

    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::sub(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    int result = machineState.registers[secondRegisterNum] -
                 machineState.registers[firstRegisterNum];

    machineState.underflowFlag = (result < 0);
    machineState.zeroFlag = (result == 0);

    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::mul(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    int result = machineState.registers[firstRegisterNum] *
                 machineState.registers[secondRegisterNum];

    machineState.overflowFlag = (result > 255);
    machineState.zeroFlag = (result == 0);

    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::div(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    if (machineState.registers[secondRegisterNum] == 0)
    {
        std::cout << "Error: Division by zero" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int result = machineState.registers[secondRegisterNum] /
                 machineState.registers[firstRegisterNum];

    machineState.zeroFlag = (result == 0);

    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::rol(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    unsigned char regValue = machineState.registers[registerNum];

    for (unsigned char i = 0; i < value; ++i)
    {
        bool msb = regValue & 0x80;
        regValue = (regValue << 1) | (msb >> 7);
    }

    machineState.zeroFlag = (regValue == 0);

    machineState.registers[registerNum] = regValue;
}

void Runner::ror(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    unsigned char regValue = machineState.registers[registerNum];

    for (unsigned char i = 0; i < value; ++i)
    {
        bool lsb = regValue & 0x01;
        regValue = (regValue >> 1) | (lsb << 7);
    }

    machineState.zeroFlag = (regValue == 0);

    machineState.registers[registerNum] = regValue;
}

void Runner::shl(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    unsigned char regValue = machineState.registers[registerNum];
    unsigned char overflowCheck = regValue;

    for (unsigned char i = 0; i < value; ++i)
    {
        // if msb is set then overflow
        if (regValue & 0x80)
        {
            machineState.overflowFlag = true;
        }
        regValue <<= 1;
    }

    machineState.zeroFlag = (regValue == 0);

    machineState.registers[registerNum] = regValue;

    if (value >= 8)
    {
        machineState.zeroFlag = true;
        machineState.overflowFlag = true;
    }
}

void Runner::shr(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    unsigned char regValue = machineState.registers[registerNum];
    unsigned char underflowCheck = regValue;

    for (unsigned char i = 0; i < value; ++i)
    {
        // if lsb is set then underflow
        if (regValue & 0x01)
        {
            machineState.underflowFlag = true;
        }
        regValue >>= 1;
    }

    machineState.registers[registerNum] = regValue;

    machineState.zeroFlag = (regValue == 0);

    if (value >= 8)
    {
        machineState.zeroFlag = true;
        machineState.underflowFlag = true;
    }
}

void Runner::load(int registerNum, int addressNum)
{
    machineState.programCounter++;
    machineState.registers[registerNum] = machineState.memory[addressNum];
}

void Runner::store(int registerNum, int addressNum)
{
    machineState.programCounter++;
    machineState.memory[addressNum] = machineState.registers[registerNum];
}
