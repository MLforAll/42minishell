# 42minishell
42 School's minishell project

This project is the first of 42 school's un\*x branch's shell projects.
It aims to create a very simple shell as an introduction to forking
and process overlaying (fork and execve libc functions).

It is also a great oportunity to build a simple read, eval, exec loop.
This 'copy' goes further with a simple implementation of GNU's readline function,
allowing line editing, autocompletion and history to exist.

# Currently implemented

- Exec commands
- `cd`, `env`, `setenv`, `unsetenv`, `echo` and `source` builitins
- Environement (R/W)
- Line editing
- Double quotes
- Autocompletion
- Commands history (in RAM)
- Pipes (intercommand \`\`|'' kind)
- Ctrl-C and Ctrl-D signals
