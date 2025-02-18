# Calc - Command Line Calculator

A simple yet powerful command-line calculator written in C that supports basic arithmetic operations.

## Current Features

- Basic arithmetic operations (+, -, *, /)
- Command-line interface
- Dynamic memory allocation for handling large inputs
- Support for floating-point numbers

## Planned Features

### Short-term
- [ ] Support for parentheses in expressions
- [ ] Error handling for division by zero
- [ ] Input validation and sanitization
- [ ] Support for negative numbers
- [ ] Command history

### Mid-term
- [ ] Scientific calculator functions (sin, cos, tan, log, etc.)
- [ ] Support for variables and constants (π, e)
- [ ] Memory functions (M+, M-, MR, MC)
- [ ] Expression evaluation with operator precedence
- [ ] Unit conversion capabilities

### Long-term
- [ ] Custom function definitions
- [ ] Support for complex numbers
- [ ] Matrix operations
- [ ] Graphing capabilities in ASCII art
- [ ] Save calculations to file
- [ ] Load expressions from file
- [ ] Interactive mode with REPL
- [ ] Plugin system for extending functionality

## Building

```bash
# Format code
clang-format -i *.c *.h

# Compile
clang -fsanitize=address -g -Wall -o calc *.c

# Run
./calc
```

## Usage

Currently supports basic arithmetic expressions:
```bash
$ ./calc
User input: 12+21+31
```

## Contributing

Feel free to open issues and submit pull requests.

## License

This project is licensed under the MIT License
