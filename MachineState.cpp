#include "MachineState.h"
#include <iomanip>
#include <iostream>

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

// I tried okay? I tried to make it readable. I would've succeeded if I could
// use printf()
void MachineState::dumpState()
{
    std::cout << std::setfill(' ') << std::left << std::setw(10) << "Registers"
              << ": ";

    for (int i = 0; i < 7; i++)
    {
        if (i == 6)
        {
            std::cout << std::setfill('0') << std::setw(2) << (int)registers[i];
        }
        else
        {
            std::cout << std::setfill('0') << std::setw(2) << (int)registers[i]
                      << " ";
        }
    }

    std::cout << "#" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(10) << "Flags"
              << ": " << overflowFlag << " " << carryFlag << " "
              << underflowFlag << " " << zeroFlag << "#" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(10) << "PC"
              << ": " << std::dec << (int)programCounter << std::endl
              << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(10) << "Memory"
              << ":" << std::endl;

    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0 && i != 0)
            std::cout << std::endl;
        std::cout << std::setfill('0') << std::setw(2) << (int)memory[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "#" << std::endl;
}