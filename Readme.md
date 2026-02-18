*This project has been created as part of the 42 curriculum by satabay, ayonal.*

# minishell

## Description

minishell is a Unix shell implementation built as part of the 42 curriculum. The goal is to recreate the core behavior of bash — handling user input, parsing commands, managing processes, and executing programs — from scratch in C.

The project covers the full pipeline of a shell: reading input via readline, tokenizing and expanding it (including environment variables and quotes), parsing it into a command structure, and finally executing it using low-level system calls like `fork`, `execve`, and `pipe`. Special attention was given to signal handling, file descriptor management, and memory safety.

### Supported Features

- External command execution (e.g. `ls`, `grep`, `cat`)
- Built-in commands: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes (`|`) chaining multiple commands
- Redirections: input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`

---

## Instructions

### Requirements

- GCC or compatible C compiler
- GNU Make
- readline library (`libreadline-dev` on Debian/Ubuntu)

### Compilation
```bash
make
```

This compiles the bundled `libft` and links the final `minishell` binary.

### Running
```bash
./minishell
```

You will be dropped into an interactive prompt:
```
minishell$ echo "Hello, world!"
Hello, world!
minishell$ ls | grep .c
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
minishell$ exit
```

### Cleanup
```bash
make clean
make fclean
make re
```

---

## Resources

### Documentation & References

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the authoritative reference for bash behavior, used to validate expected outputs
- [GNU readline library](https://tiswww.case.edu/php/chet/readline/rltop.html) — used for interactive input and history
- [The Open Group: Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — POSIX specification for shell behavior
- [Linux man pages: execve(2), fork(2), pipe(2), dup2(2), waitpid(2), signal(2)](https://man7.org/linux/man-pages/) — essential system call references
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) — overview of shell architecture and process management
- [Stephen Brennan's Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/) — practical walkthrough of shell construction in C

### AI Usage

AI (Claude) was used during this project for the following purposes:

- **Debugging**: Helping identify logic errors in the expander and redirection handling, particularly edge cases with nested quotes and heredoc stdin restoration.
- **Code review**: Reviewing memory management patterns to catch potential leaks in the parser and free functions.
- **Explaining concepts**: Clarifying behavior differences between `wait` and `waitpid`, and how `dup2` interacts with inherited file descriptors across `fork`.
- **README writing**: Drafting and structuring this README to meet 42 curriculum requirements.

AI was not used to write core logic from scratch. All architectural decisions, data structures, and implementations were designed and written by the authors.