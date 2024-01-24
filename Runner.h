#pragma once
#include "MachineState.h"

class Runner
{
    public:
        /**
         * @brief Constructs a Runner object, initializing it with a reference
         * to a MachineState object.
         * @param machineState A reference to the MachineState object to
         * interact with the virtual machine's state.
         */
        Runner(MachineState &machineState);

        /**
         * @brief Executes the 'IN' instruction: Reads an integer from standard
         * input and stores it in the specified register.
         * @param registerNum The register number where the input will be
         * stored.
         */
        void in(int registerNum);

        /**
         * @brief Executes the 'OUT' instruction: Prints the value stored in the
         * specified register to standard output.
         * @param registerNum The register number containing the value to be
         * printed.
         */
        void out(int registerNum);

        /**
         * @brief Executes the 'INC' instruction: Increments the value stored in
         * the specified register by 1.
         * @param registerNum The register number to be incremented.
         */
        void inc(int registerNum);

        /**
         * @brief Executes the 'DEC' instruction: Decrements the value stored in
         * the specified register by 1.
         * @param registerNum The register number to be decremented.
         */
        void dec(int registerNum);

        /**
         * @brief Retrieves the value stored in the specified register.
         * @param registerNum The register number to retrieve the value from.
         * @return The value stored in the specified register.
         */
        unsigned char getValueAtRegister(int registerNum);

        /**
         * @brief Stores the specified value in the specified register.
         * @param value The value to be stored.
         * @param registerNum The register number where the value will be
         * stored.
         */
        void mov(int value, int registerNum);

        /**
         * @brief Adds the values stored in two registers and stores the result
         * in the first register.
         * @param firstRegisterNum The register number containing the first
         * value.
         * @param secondRegisterNum The register number containing the second
         * value.
         */
        void add(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Subtracts the value stored in the second register from the
         * value stored in the first register and stores the result in the first
         * register.
         * @param firstRegisterNum The register number containing the first
         * value.
         * @param secondRegisterNum The register number containing the second
         * value.
         */
        void sub(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Multiplies the values stored in two registers and stores the
         * result in the first register.
         * @param firstRegisterNum The register number containing the first
         * value.
         * @param secondRegisterNum The register number containing the second
         * value.
         */
        void mul(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Divides the value stored in the first register by the value
         * stored in the second register and stores the quotient in the first
         * register.
         * @param firstRegisterNum The register number containing the dividend.
         * @param secondRegisterNum The register number containing the divisor.
         */
        void div(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Rotates the bits of the value stored in the specified register
         * to the left by the specified number of positions.
         * @param registerNum The register number containing the value to be
         * rotated.
         * @param value The number of positions to rotate the bits to the left.
         */
        void rol(int registerNum, int value);

        /**
         * @brief Rotates the bits of the value stored in the specified register
         * to the right by the specified number of positions.
         * @param registerNum The register number containing the value to be
         * rotated.
         * @param value The number of positions to rotate the bits to the right.
         */
        void ror(int registerNum, int value);

        /**
         * @brief Shifts the bits of the value stored in the specified register
         * to the left by the specified number of positions.
         * @param registerNum The register number containing the value to be
         * shifted.
         * @param value The number of positions to shift the bits to the left.
         */
        void shl(int registerNum, int value);

        /**
         * @brief Shifts the bits of the value stored in the specified register
         * to the right by the specified number of positions.
         * @param registerNum The register number containing the value to be
         * shifted.
         * @param value The number of positions to shift the bits to the right.
         */
        void shr(int registerNum, int value);

        /**
         * @brief Loads the value stored at the specified memory address into
         * the specified register.
         * @param registerNum The register number where the value will be
         * loaded.
         * @param addressNum The memory address from where the value will be
         * loaded.
         */
        void load(int registerNum, int addressNum);

        /**
         * @brief Stores the value stored in the specified register at the
         * specified memory address.
         * @param registerNum The register number containing the value to be
         * stored.
         * @param addressNum The memory address where the value will be stored.
         */
        void store(int registerNum, int addressNum);

    private:
        MachineState &machineState;
};
