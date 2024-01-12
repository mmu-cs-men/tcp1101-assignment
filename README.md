# TCP1101 Assignment
This repo houses code for our Programming Fundamentals assignment.

## Code Guidelines
Below are some guidelines that you should follow to ensure clean and maintainable code.

### 1. Naming Conventions
Use clear and descriptive names. Variables should use "camelCase" and classes should use "PascalCase".

### 2. Comment Formatting
Format your doc comments according to the Doxygen style. Use ChatGPT or Copilot to generate docs for classes and functions if you don't want to bother learning Doxygen.

### 3. Line Length
Try not to write super long lines. If you can, break it up into smaller chunks or simply use the next line.

### 4. Single Responsibility
Each class and function should perform only one function.

### 5. Document Code
Add documentation to every single class and function that you create (except for constructors).

### 6. Do not use `using namespace std`
We use it always in our course to save some typing but you shouldn't use it in actual code for two main reasons:

1. Theres a good chance it will conflict with an existing name.

2. When reading through code, it will be hard to tell where standard library functions are being called. For example, you might be reading through a piece of code and see `sort()` and wonder where it's coming from until you realize you included the `<algorithm>` header. If it was `std::sort()`, there would be zero confusion.

### 7. Define Variables
The rule of thumb is: don't introduce a name until you have a use for it. Undefined variables can still be used and are a source of bugs. Additionally, leaving variables undefined is hard to read. Imagine a long file where a variable was initialized on line 1, then finally given a value on line 560 when you could have just given the value on line 560 itself.