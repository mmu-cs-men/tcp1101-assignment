#include "Runner.h"
#include <iostream>

Runner::Runner(MachineState &machineState) : machineState(machineState) {}

void Runner::in(int registerNum) {
    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6) {
        std::cerr << "Error: Invalid register number" << std::endl;
        return;
    }

    // Read an integer from standard input
    int value;
    std::cin >> value;

    // Ensure the value is within the 0-255 range
    if (value < 0 || value > 255) {
        std::cerr << "Error: Input value out of range" << std::endl;
        return;
    }

    // Store the value in the specified register
    machineState.registers[registerNum] = static_cast<unsigned char>(value);
}
