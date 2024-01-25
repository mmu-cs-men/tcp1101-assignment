#include "Runner.h"
#include <iostream>

Runner::Runner(MachineState &machineState) : machineState(machineState)
{
}

void Runner::in(int registerNum)
{
    machineState.programCounter++;

    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Read an integer from standard input
    int value;
    std::cin >> value;

    // Ensure the value is within the 0-255 range
    if (value < 0 || value > 255)
    {
        std::cout << "Error: Input value out of range" << std::endl;
        return;
    }

    // Store the value in the specified register
    machineState.registers[registerNum] = static_cast<unsigned char>(value);
}

void Runner::out(int registerNum)
{
    machineState.programCounter++;

    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Retrieve the value from the specified register
    unsigned char value = machineState.registers[registerNum];

    // Output the value to standard output
    std::cout << "Register R" << registerNum
              << " contains: " << static_cast<int>(value) << std::endl;
}

void Runner::inc(int registerNum)
{
    machineState.programCounter++;

    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Retrieve the current value of the register
    unsigned char currentValue = machineState.registers[registerNum];

    // Check for overflow
    if (currentValue == 255)
    {
        // Set the overflow flag in MachineState
        machineState.overflowFlag = true;
        machineState.zeroFlag = true;
    }

    // Increment the value of the register
    machineState.registers[registerNum] = currentValue + 1;
}

void Runner::dec(int registerNum)
{
    machineState.programCounter++;

    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Retrieve the current value of the register
    unsigned char currentValue = machineState.registers[registerNum];

    // Check for underflow
    if (currentValue == 0)
    {
        // Set the underflow flag in MachineState
        machineState.underflowFlag = true;
    }
    else if (currentValue == 1)
    {
        machineState.zeroFlag = true;
    }

    // Decrement the value of the register
    machineState.registers[registerNum] = currentValue - 1;
}

unsigned char Runner::getValueAtRegister(int registerNum)
{
    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number. Returning 0."
                  << std::endl;
        return 0; // Return 0 or some other error code that your design
                  // specifies
    }

    // Return the value stored in the specified register
    return machineState.registers[registerNum];
}

unsigned char Runner::getValueAtAddress(int addressNum)
{
    // Validate memory address
    if (addressNum < 0 || addressNum >= 64) // Assuming 64 is the size of memory
    {
        std::cout << "Error: Invalid memory address. Returning 0." << std::endl;
        return 0; // Return 0 or some other error code that your design
                  // specifies
    }

    // Return the value stored at the specified memory address
    return machineState.memory[addressNum];
}

void Runner::mov(int value, int registerNum)
{
    machineState.programCounter++;

    // Check if the register number is within the valid range (0 to 6)
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Check if the value is within the 0-255 range
    if (value < 0 || value > 255)
    {
        std::cout << "Error: Value out of range" << std::endl;

        return;
    }

    // Store the value in the specified register
    machineState.registers[registerNum] = static_cast<unsigned char>(value);
}

void Runner::add(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    // Check if the register numbers are within the valid range (0 to 6)
    if (firstRegisterNum < 0 || firstRegisterNum > 6 || secondRegisterNum < 0 ||
        secondRegisterNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Perform the addition and check for overflow
    int result = machineState.registers[firstRegisterNum] +
                 machineState.registers[secondRegisterNum];

    // Store the result in the second register, truncating to 8 bits if
    // necessary
    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);

    // Optionally set the overflow flag if the result exceeded 8 bits
    machineState.overflowFlag = (result > 255);
    machineState.zeroFlag = (result % 256 == 0 || result == 0);
}

void Runner::sub(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    // Check if the register numbers are within the valid range (0 to 6)
    if (firstRegisterNum < 0 || firstRegisterNum > 6 || secondRegisterNum < 0 ||
        secondRegisterNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Perform the subtraction and check for underflow
    int result = machineState.registers[secondRegisterNum] -
                 machineState.registers[firstRegisterNum];

    // Set or clear the underflow flag based on the result
    machineState.underflowFlag = (result < 0);
    machineState.zeroFlag = (result == 0);

    // Store the result in the second register, ensuring it stays within 0-255
    // range
    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::mul(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    // Validate register numbers
    if (firstRegisterNum < 0 || firstRegisterNum > 6 || secondRegisterNum < 0 ||
        secondRegisterNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Perform multiplication
    int result = machineState.registers[firstRegisterNum] *
                 machineState.registers[secondRegisterNum];

    // Set the carry flag if the result is larger than 255
    machineState.overflowFlag = (result > 255);
    machineState.zeroFlag = (result == 0);

    // Store the result in the second register
    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);
}

void Runner::div(int firstRegisterNum, int secondRegisterNum)
{
    machineState.programCounter++;

    // Validate register numbers
    if (firstRegisterNum < 0 || firstRegisterNum > 6 || secondRegisterNum < 0 ||
        secondRegisterNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Check for division by zero
    if (machineState.registers[secondRegisterNum] == 0)
    {
        std::cout << "Error: Division by zero" << std::endl;
        return;
    }

    // Perform division
    int result = machineState.registers[secondRegisterNum] /
                 machineState.registers[firstRegisterNum];

    // Store the result in the second register
    machineState.registers[secondRegisterNum] =
        static_cast<unsigned char>(result);

    machineState.zeroFlag = (result == 0);
}

void Runner::rol(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    // Validate register number
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Get the current value in the register
    unsigned char regValue = machineState.registers[registerNum];

    // Perform the rotation
    for (unsigned char i = 0; i < value; ++i)
    {
        // Rotate left: shift left and move the shifted-out bit to the right end
        bool msb = regValue & 0x80; // Check the most significant bit
        regValue = (regValue << 1) | (msb >> 7);
    }

    // Store the result back in the register
    machineState.registers[registerNum] = regValue;

    machineState.zeroFlag = (regValue == 0);
}

void Runner::ror(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    // Validate register number
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Get the current value in the register
    unsigned char regValue = machineState.registers[registerNum];

    // Perform the rotation
    for (unsigned char i = 0; i < value; ++i)
    {
        // Rotate left: shift left and move the shifted-out bit to the right end
        bool lsb = regValue & 0x01; // Check the most significant bit
        regValue = (regValue >> 1) | (lsb << 7);
    }

    // Store the result back in the register
    machineState.registers[registerNum] = regValue;

    machineState.zeroFlag = (regValue == 0);
}

void Runner::shl(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    // Validate register number
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Get the current value in the register
    unsigned char regValue = machineState.registers[registerNum];
    unsigned char overflowCheck = regValue;

    // Perform the shift
    for (unsigned char i = 0; i < value; ++i)
    {
        // Check for overflow before the shift
        if (regValue & 0x80) // If the most significant bit is set
        {
            machineState.overflowFlag = true;
        }
        regValue <<= 1; // Shift left by one position
    }

    // Check for underflow, which is not possible with left shift
    // Hence, underflowFlag is not set in this operation

    // Store the result back in the register
    machineState.registers[registerNum] = regValue;

    // Set zeroFlag if the result is zero
    machineState.zeroFlag = (regValue == 0);

    // If the shift value is greater than or equal to the number of bits (8),
    // the result must be zero, and overflow must have occurred.
    if (value >= 8)
    {
        machineState.zeroFlag = true;
        machineState.overflowFlag = true;
    }
    // Additionally, if the original value was non-zero and the shift resulted
    // in zero, it's an overflow situation.
    else if (overflowCheck != 0 && regValue == 0)
    {
        machineState.overflowFlag = true;
    }
}

void Runner::shr(int registerNum, unsigned char value)
{
    machineState.programCounter++;

    // Validate register number
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Get the current value in the register
    unsigned char regValue = machineState.registers[registerNum];
    unsigned char underflowCheck = regValue;

    // Perform the shift
    for (unsigned char i = 0; i < value; ++i)
    {
        // Check for underflow before the shift
        if (regValue & 0x01) // If the least significant bit is set
        {
            machineState.underflowFlag = true;
        }
        regValue >>= 1; // Shift right by one position
    }

    // Store the result back in the register
    machineState.registers[registerNum] = regValue;

    // Set zeroFlag if the result is zero
    machineState.zeroFlag = (regValue == 0);

    // Overflow is not possible with right shift, so overflowFlag is not set
    // here

    // If the shift value is greater than or equal to the number of bits (8),
    // the result must be zero, and underflow must have occurred.
    if (value >= 8)
    {
        machineState.zeroFlag = true;
        machineState.underflowFlag = true;
    }
    // Additionally, if the original value was non-zero and the shift resulted
    // in zero, it's an underflow situation.
    else if (underflowCheck != 0 && regValue == 0)
    {
        machineState.underflowFlag = true;
    }
}

void Runner::load(int registerNum, int addressNum)
{
    machineState.programCounter++;

    // Validate register number
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Validate memory address
    if (addressNum < 0 || addressNum >= 64) // Assuming 64 is the size of memory
    {
        std::cout << "Error: Invalid memory address" << std::endl;
        return;
    }

    // Load the value from the specified memory address into the register
    machineState.registers[registerNum] = machineState.memory[addressNum];
}

void Runner::store(int registerNum, int addressNum)
{
    machineState.programCounter++;

    // Validate register number
    if (registerNum < 0 || registerNum > 6)
    {
        std::cout << "Error: Invalid register number" << std::endl;
        return;
    }

    // Validate memory address
    if (addressNum < 0 || addressNum >= 64) // Assuming 64 is the size of memory
    {
        std::cout << "Error: Invalid memory address" << std::endl;
        return;
    }

    // Store the value from the register into the specified memory address
    machineState.memory[addressNum] = machineState.registers[registerNum];
}
