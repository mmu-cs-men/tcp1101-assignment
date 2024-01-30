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
    std::cout << "Enter input to be put into R" << registerNum << ": ";
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

    if (currentValue == 255)
    {
        machineState.overflowFlag = true;
        machineState.zeroFlag = true;
    }

    machineState.registers[registerNum] = currentValue + 1;
}

void Runner::dec(int registerNum)
{
    machineState.programCounter++;

    unsigned char currentValue = machineState.registers[registerNum];

    if (currentValue == 0)
    {
        machineState.underflowFlag = true;
    }
    else if (currentValue == 1)
    {
        machineState.zeroFlag = true;
    }

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

    if (result > 255)
    {
        machineState.overflowFlag = true;
    }
    else if (result % 256 == 0 || result == 0)
    {
        machineState.zeroFlag = true;
    }

    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::sub(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    int result = machineState.registers[secondRegisterNum] -
                 machineState.registers[firstRegisterNum];

    if (result < 0)
    {
        machineState.underflowFlag = true;
    }
    else if (result == 0)
    {
        machineState.zeroFlag = true;
    }

    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::mul(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    int result = machineState.registers[firstRegisterNum] *
                 machineState.registers[secondRegisterNum];

    if (result > 255)
    {
        machineState.overflowFlag = true;
    }
    else if (result == 0)
    {
        machineState.zeroFlag = true;
    }

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

    if (result == 0)
    {
        machineState.zeroFlag = true;
    }

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

    if (regValue == 0)
    {
        machineState.zeroFlag = true;
    }

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

    if (regValue == 0)
    {
        machineState.zeroFlag = true;
    }

    machineState.registers[registerNum] = regValue;
}

void Runner::shl(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    unsigned char regValue = machineState.registers[registerNum];

    for (unsigned char i = 0; i < value; ++i)
    {
        if (regValue & 0x80)
        {
            machineState.carryFlag = true;
        }
        regValue <<= 1;
    }

    if (regValue == 0)
    {
        machineState.zeroFlag = true;
    }

    machineState.registers[registerNum] = regValue;
}

void Runner::shr(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    unsigned char regValue = machineState.registers[registerNum];

    for (unsigned char i = 0; i < value; ++i)
    {
        if (regValue & 0x01)
        {
            machineState.carryFlag = true;
        }
        regValue >>= 1;
    }

    if (regValue == 0)
    {
        machineState.zeroFlag = true;
    }

    machineState.registers[registerNum] = regValue;
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
