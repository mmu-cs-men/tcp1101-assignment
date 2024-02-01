#pragma once
#include <string>

class MachineState
{
    public:
        /**
         * @brief Initializes MachineState.
         * Note: all memory addresses and registers are set to 0 here.
         */
        MachineState();

        /**
         * @brief Dumps the current state of the machine into a string according
         * to assignment spec.
         *
         * @return A string representation of the current machine state.
         */
        std::string dumpState();

        unsigned char registers[7];
        unsigned char memory[64];
        unsigned programCounter = 0;
        bool overflowFlag = false;
        bool &carryFlag = overflowFlag; // unsigned so this is useless lol
        bool underflowFlag = false;
        bool zeroFlag = false;
};