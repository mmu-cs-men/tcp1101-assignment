#pragma once

class MachineState
{
    public:
        MachineState();
        void dumpState();

        unsigned char registers[7];
        unsigned char memory[64];
        unsigned programCounter = 0;
        bool overflowFlag = false;
        bool &carryFlag = overflowFlag; // using unsigned so this is useless lol
        bool underflowFlag = false;
        bool zeroFlag = false;
};