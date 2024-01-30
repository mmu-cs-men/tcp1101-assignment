#include "MachineState.h"
#include <iomanip>
#include <iostream>
#include <sstream>

MachineState::MachineState()
{
    for (int i = 0; i < 64; i++)
    {
        memory[i] = 0;
    }

    for (int i = 0; i < 7; i++)
    {
        registers[i] = 0;
    }
}

std::string MachineState::dumpState()
{
    std::stringstream ss;

    // Dump registers
    ss << "Registers : ";
    for (int i = 0; i < 7; i++)
    {
        ss << std::setfill('0') << std::setw(2) << (int)registers[i];
        if (i < 6)
        {
            ss << " ";
        }
    }
    ss << "#" << std::endl;

    // Dump flags
    ss << "Flags     : " << overflowFlag << " " << underflowFlag << " "
       << carryFlag << " " << zeroFlag << "#" << std::endl;

    // Dump program counter
    ss << "PC        : " << std::dec << programCounter << std::endl
       << std::endl;

    // Dump memory
    ss << "Memory    :" << std::endl;
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0 && i != 0)
            ss << std::endl;
        ss << std::setfill('0') << std::setw(2) << (int)memory[i] << " ";
    }
    ss << "\n#" << std::endl;

    return ss.str();
}
