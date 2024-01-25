#pragma once
#include <string>

class MachineState
{
    public:
        MachineState();
        std::string dumpState();

        unsigned char registers[7];
        unsigned char memory[64];
        unsigned programCounter = 0;
        bool overflowFlag = false;
        bool &carryFlag = overflowFlag; // using unsigned so this is useless lol
        bool underflowFlag = false;
        bool zeroFlag = false;
};