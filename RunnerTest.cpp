#include "Runner.h"
#include "MachineState.h"
#include <cassert>
#include <iostream>

// Test for the mov function
void testMovFunction()
{
    MachineState ms;
    Runner runner(ms);

    runner.mov(100, 0); // Move value 100 to register 0
    assert(ms.registers[0] == 100);
    std::cout << "testMovFunction passed." << std::endl;
}

// Test for the add function
void testAddFunction()
{
    MachineState ms;
    Runner runner(ms);

    ms.registers[0] = 10;
    ms.registers[1] = 20;
    runner.add(0, 1); // Add registers 0 and 1; store result in register 1
    assert(ms.registers[1] == 30);
    std::cout << "testAddFunction passed." << std::endl;
}

// Test for the sub function
void testSubFunction()
{
    MachineState ms;
    Runner runner(ms);

    ms.registers[0] = 10;
    ms.registers[1] = 20;
    runner.sub(0, 1); // Subtract register 0 from 1; store result in register 1
    assert(ms.registers[1] == 10);
    std::cout << "testSubFunction passed." << std::endl;
}

// Test for the mul function
void testMulFunction()
{
    MachineState ms;
    Runner runner(ms);

    ms.registers[0] = 5;
    ms.registers[1] = 6;
    runner.mul(0, 1); // Multiply registers 0 and 1; store result in register 1
    assert(ms.registers[1] == 30);
    std::cout << "testMulFunction passed." << std::endl;
}

// Test for the div function
void testDivFunction()
{
    MachineState ms;
    Runner runner(ms);

    ms.registers[0] = 5;  // First register (divisor)
    ms.registers[1] = 30; // Second register (dividend)

    runner.div(0, 1); // Divide value in register 1 by value in register 0;
                      // store result in register 1

    assert(ms.registers[1] == 6); // Expected result is 6
    std::cout << "testDivFunction passed." << std::endl;
}

void demoRunnerFunctions()
{
    MachineState ms;
    Runner runner(ms);

    // Demonstrate the 'mov' function
    runner.mov(50, 0); // Move 50 into register 0
    std::cout << "After mov: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate the 'inc' function
    runner.inc(0); // Increment value in register 0
    std::cout << "After inc: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate the 'dec' function
    runner.dec(0); // Decrement value in register 0
    std::cout << "After dec: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Similar demonstrations for add, sub, mul, div, rol, ror, shl, shr, load,
    // store Ensure you set up the initial conditions correctly for each
    // operation

    // Example for 'add'
    ms.registers[1] = 20; // Set register 1 to 20
    runner.add(0, 1);     // Add register 0 and 1; store result in register 1
    std::cout << "After add: Register 1 contains "
              << static_cast<int>(ms.registers[1]) << std::endl;

    // Continue with other functions...
}

void demoInAndOutFunctions()
{
    MachineState ms;
    Runner runner(ms);

    // Example usage of 'in' function
    std::cout << "Enter an integer value for Register 0: ";
    runner.in(0); // Reads user input and stores it in register 0

    // Example usage of 'out' function
    std::cout << "Displaying value in Register 0: ";
    runner.out(0); // Prints the value in register 0 to the console
}

void demoAdditionalFunctions()
{
    MachineState ms;
    Runner runner(ms);

    // Set up a value in memory for the 'load' demonstration
    ms.memory[5] = 55; // Assuming memory[5] is a valid address
    runner.load(0, 5); // Load the value from memory[5] into register 0
    std::cout << "After load: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate 'shr' (shift right)
    runner.shr(0, 1); // Shift right by 1
    std::cout << "After shr: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate 'shl' (shift left)
    runner.shl(0, 1); // Shift left by 1
    std::cout << "After shl: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate 'ror' (rotate right)
    runner.ror(0, 1); // Rotate right by 1
    std::cout << "After ror: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate 'rol' (rotate left)
    runner.rol(0, 1); // Rotate left by 1
    std::cout << "After rol: Register 0 contains "
              << static_cast<int>(ms.registers[0]) << std::endl;

    // Demonstrate 'store'
    runner.store(0, 6); // Store the value from register 0 into memory[6]
    std::cout << "After store: Memory[6] contains "
              << static_cast<int>(ms.memory[6]) << std::endl;
}
int main()
{
    demoAdditionalFunctions();
    std::cout << "Additional functions demo passed." << std::endl;

    demoInAndOutFunctions();
    std::cout << "In and Out functions demo passed." << std::endl;

    demoRunnerFunctions();
    std::cout << "Runner functions demo passed." << std::endl;

    testMovFunction();
    testAddFunction();
    testSubFunction();
    testMulFunction();
    testDivFunction();

    std::cout << "All tests passed." << std::endl;
    return 0;
}
