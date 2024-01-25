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

    ss << std::setfill(' ') << std::left << std::setw(10) << "Registers"
       << ": ";

    for (int i = 0; i < 7; i++)
    {
        if (i == 6)
        {
            ss << std::setfill('0') << std::setw(2) << (int)registers[i];
        }
        else
        {
            ss << std::setfill('0') << std::setw(2) << (int)registers[i] << " ";
        }
    }

    ss << "#" << std::endl;
    ss << std::setfill(' ') << std::left << std::setw(10) << "Flags"
       << ": " << overflowFlag << " " << carryFlag << " " << underflowFlag
       << " " << zeroFlag << "#" << std::endl;
    ss << std::setfill(' ') << std::left << std::setw(10) << "PC"
       << ": " << std::dec << (int)programCounter << std::endl
       << std::endl;
    ss << std::setfill(' ') << std::left << std::setw(10) << "Memory"
       << ":" << std::endl;

    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0 && i != 0)
            ss << std::endl;
        ss << std::setfill('0') << std::setw(2) << (int)memory[i] << " ";
    }

    ss << std::endl;
    ss << "#" << std::endl;

    return ss.str();
}