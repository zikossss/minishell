# Minishell

A minimalist shell implementation I built in C, inspired by Bash. I recreated the basic functionality of a Unix shell, providing a command-line interface for interacting with the operating system.

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Technical Implementation](#technical-implementation)
- [Signals](#signals)
- [Limitations](#limitations)

## 🎯 About

Minishell is a 42 school project where I built a simplified version of a Unix shell from scratch. This project gave me deep insights into process management, file descriptors, signal handling, and shell parsing mechanisms.

## ✨ Features

### Core Functionality
- Interactive command prompt with readline support
- Command history navigation
- Executable search and launch based on PATH variable
- Support for absolute and relative paths

### Redirections
- **Input redirection** (`<`): Redirects input from a file
- **Output redirection** (`>`): Redirects output to a file (overwrites)
- **Append redirection** (`>>`): Redirects output to a file (appends)
- **Heredoc** (`<<`): Reads input until a delimiter is encountered

### Pipes
- Command chaining using pipes (`|`)
- Support for multiple pipe sequences

### Environment Variables
- Variable expansion (`$USER`, `$HOME`, etc.)
- Exit status expansion (`$?`)
- Environment variable management

### Signal Handling
- `Ctrl-C` (SIGINT): Interrupts current command
- `Ctrl-D` (EOF): Exits the shell
- `Ctrl-\` (SIGQUIT): Ignored in interactive mode

## 📁 Project Structure

Here's how I organized the project:

```
minishell/
├── built_ins/              # Built-in command implementations
├── command_execution/      # Command execution logic
├── execution/              # Process and pipeline execution
├── expantion/              # Variable and parameter expansion
├── helper_functions/       # Utility functions
├── heredoc/                # Heredoc implementation
├── main/                   # Main entry point and initialization
├── parce_and_redirection/  # Parsing and redirection handling
├── tokenization/           # Lexical analysis and tokenization
├── makefile                # Build configuration
└── minishell.h             # Header file with structures and prototypes
```

## 🔧 Installation

### Prerequisites
- GCC compiler
- GNU Readline library
- Make

### Building the Project

```bash
# Clone the repository
git clone https://github.com/zikossss/minishell.git
cd minishell

# Compile the project
make

# Run minishell
./minishell
```

### MacOS Compilation Issues

If you're on a MacBook and encounter compilation errors related to readline functions, you'll need to properly link the Homebrew-installed readline library. I had to modify my Makefile with the following flags:

**Add to CFLAGS:**
```makefile
CFLAGS += -I/usr/local/opt/readline/include
```

**Add to LDFLAGS:**
```makefile
LDFLAGS += -L/usr/local/opt/readline/lib -lreadline
```

These paths ensure the compiler can find the readline headers during compilation and link against the readline library properly.

### Additional Make Commands

```bash
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Rebuild the project
```

## 🚀 Usage

Once launched, minishell displays a prompt where you can enter commands:

```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ ls -la | grep minishell
-rwxr-xr-x  1 user  staff  123456 Jan 22 10:30 minishell

minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42

minishell$ cat << EOF > output.txt
> Line 1
> Line 2
> EOF

minishell$ exit
```

## 🔨 Built-in Commands

I implemented the following built-in commands:

| Command | Description | Usage |
|---------|-------------|-------|
| `echo` | Display a line of text | `echo [-n] [string ...]` |
| `cd` | Change directory | `cd [path]` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variable | `export VAR=value` |
| `unset` | Unset environment variable | `unset VAR` |
| `env` | Display environment variables | `env` |
| `exit` | Exit the shell | `exit [status]` |

## 🏗️ Technical Implementation

### Parsing Pipeline

Here's how I structured the parsing process:

1. **Tokenization**: Input is broken down into tokens (words, operators, special characters)
2. **Expansion**: Environment variables and special parameters are expanded
3. **Parsing**: Tokens are analyzed to construct a command structure
4. **Redirection Handling**: File descriptors are set up based on redirection operators
5. **Execution**: Commands are executed in child processes with proper piping

### Process Management

I implemented process management using:
- `fork()` to create child processes
- `execve()` for command execution
- `waitpid()` to manage process groups
- Sequential forking to handle multiple pipes

### Memory Management

I emphasized proper memory management throughout the project:
- No memory leaks in parent process
- Proper cleanup of child processes
- File descriptor management to prevent leaks

## ⚡ Signals

I handled signals to mimic bash behavior:

- **Interactive mode**: `Ctrl-C` displays a new prompt, `Ctrl-\` is ignored
- **Command execution**: Signals are passed to child processes
- **Heredoc mode**: `Ctrl-C` interrupts heredoc input

## ⚠️ Limitations

I didn't implement the following features:

- Logical operators (`&&`, `||`)
- Command separator (`;`)
- Backslash escaping (`\`)
- Wildcards (`*`, `?`)
- Subshells and command substitution
- Job control (`bg`, `fg`, `jobs`)

## 📚 What I Learned

This project gave me hands-on experience with:

- Unix process creation and management
- File descriptor manipulation
- Signal handling in C
- Parser implementation
- System calls and low-level I/O operations
- Team collaboration and code architecture

## 🤝 Contributing

This is an educational project I completed as part of the 42 curriculum. While I'm not actively seeking contributions, I welcome feedback and suggestions!

## 📝 License

This project is part of the 42 school curriculum and follows their guidelines for student projects.

---

**Note**: I prioritized learning and understanding shell mechanics over feature completeness. This implementation serves as a foundation for understanding how shells work at a fundamental level.
