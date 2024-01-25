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

void MachineState::dumpState()
{
    std::cout << "Registers: ";
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::setfill('0') << std::setw(2) << (int)registers[i]
                  << " ";
    }
    std::cout << "#" << std::endl;

    std::cout << "Flags: " << overflowFlag << " " << carryFlag << " "
              << underflowFlag << " " << zeroFlag << " #" << std::endl;
    std::cout << "PC: " << std::dec << (int)programCounter << std::endl;
    std::cout << "Memory :" << std::endl;

    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0 && i != 0)
            std::cout << std::endl;
        std::cout << std::setfill('0') << std::setw(2) << (int)memory[i] << " ";
    }
    std::cout << "#" << std::endl;
}