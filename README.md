# 42minishell
42 School's minishell project

This project is the first of 42 school's un\*x branch's shell project.
It aims to create a very simple shell as an introduction to forking processes
and process overlaying (fork and execve libc functions).

It is also a great oportunity to build a simple read, eval, exec loop.
This 'copy' goes further with a simple implementation of GNU's readline function,
allowing line editing, autocompletion and history to exit.

# Currently implemented

- Basic line editing (buggy)
- Autocompletion
- Exec commands
- Environement
- Ctrl-C and Ctrl-D signals

# Todo

- Fix bugs with line editing
- History
- Other signals
- Variables
- Norming
