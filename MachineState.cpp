#include "MachineState.h"

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