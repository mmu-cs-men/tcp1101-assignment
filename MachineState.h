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
        bool carryFlag = false;
        bool underflowFlag = false;
        bool zeroFlag = false;
};