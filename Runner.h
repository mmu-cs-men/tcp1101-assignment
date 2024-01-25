#pragma once
#include "MachineState.h"

class Runner
{
    public:
        Runner(MachineState &machineState);

        /**
         * @brief Retrieves the value stored in a specific register.
         *
         * @param registerNum The register number to query.
         * @return The value stored in the specified register.
         */
        unsigned char getValueAtRegister(int registerNum);

        /**
         * @brief Retrieves the value stored at a specific memory address.
         *
         * @param addressNum The memory address to query.
         * @return The value stored at the specified memory address.
         */
        unsigned char getValueAtAddress(int addressNum);

        /**
         * @brief Reads an integer from standard input and stores it in a
         * register.
         *
         * @param registerNum The register number where the input will be
         * stored.
         */
        void in(int registerNum);

        /**
         * @brief Outputs the value of a register to standard output.
         *
         * @param registerNum The register number to output.
         */
        void out(int registerNum);

        /**
         * @brief Increments the value of a register by 1.
         *
         * @param registerNum The register number to increment.
         */
        void inc(int registerNum);

        /**
         * @brief Decrements the value of a register by 1.
         *
         * @param registerNum The register number to decrement.
         */
        void dec(int registerNum);

        /**
         * @brief Moves a value into a register.
         *
         * @param value The value to move into the register.
         * @param registerNum The register number that will receive the value.
         */
        void mov(int value, int registerNum);

        /**
         * @brief Adds the values of two registers and stores the result in the
         * second register.
         *
         * @param firstRegisterNum The first register number.
         * @param secondRegisterNum The second register number where the result
         * will be stored.
         */
        void add(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Subtracts the value of the first register from the second and
         * stores the result in the second register.
         *
         * @param firstRegisterNum The register number from which to subtract.
         * @param secondRegisterNum The register number where the result will be
         * stored.
         */
        void sub(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Multiplies the values of two registers and stores the result
         * in the second register.
         *
         * @param firstRegisterNum The first register number.
         * @param secondRegisterNum The second register number where the result
         * will be stored.
         */
        void mul(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Divides the value of the second register by the first and
         * stores the result in the second register.
         *
         * @param firstRegisterNum The register number to divide by.
         * @param secondRegisterNum The register number where the result will be
         * stored.
         */
        void div(int firstRegisterNum, int secondRegisterNum);

        /**
         * @brief Performs a rotate left operation on the value of a register.
         *
         * @param registerNum The register number to rotate.
         * @param value The number of positions to rotate by.
         */
        void rol(int registerNum, unsigned char value);

        /**
         * @brief Performs a rotate right operation on the value of a register.
         *
         * @param registerNum The register number to rotate.
         * @param value The number of positions to rotate by.
         */
        void ror(int registerNum, unsigned char value);

        /**
         * @brief Performs a shift left operation on the value of a register.
         *
         * @param registerNum The register number to shift.
         * @param value The number of positions to shift by.
         */
        void shl(int registerNum, unsigned char value);

        /**
         * @brief Performs a shift right operation on the value of a register.
         *
         * @param registerNum The register number to shift.
         * @param value The number of positions to shift by.
         */
        void shr(int registerNum, unsigned char value);

        /**
         * @brief Loads the value from a memory address into a register.
         *
         * @param registerNum The register number where the value will be
         * stored.
         * @param addressNum The memory address from which to load the value.
         */
        void load(int registerNum, int addressNum);

        /**
         * @brief Stores the value from a register into a memory address.
         *
         * @param registerNum The register number from which to store the value.
         * @param addressNum The memory address where the value will be stored.
         */
        void store(int registerNum, int addressNum);

    private:
        MachineState &machineState;
};
