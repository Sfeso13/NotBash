# 🐚 Minishell

`minishell` is a Unix shell project from the 42 curriculum designed to help students understand and build their own command-line interpreter. The project focuses on process creation, pipes, redirections, and environment management.

## 📚 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [File Structure](#-file-structure)
- [Subject Breakdown](#-subject-breakdown)
- [License](#-license)
- [Subject PDF](#-subject-pdf)

## 📖 Overview

Minishell is a simplified recreation of a real Unix shell like `bash` or `zsh`. It supports executing commands, piping, redirections, environment variables, and built-in shell commands. The goal is to understand how a shell works under the hood by re-implementing its core functionalities.

## ✨ Features

- ✅ Prompt that reads user input line by line
- ✅ Parse and split commands with arguments
- ✅ Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Execute external programs using `execve`
- ✅ Input/output redirections: `<`, `>`, `>>`, `<<`
- ✅ Pipe (`|`) support
- ✅ Environment variables management and `$` expansion
- ✅ Signal handling (`Ctrl-C`, `Ctrl-D`, etc.)
- ✅ Error messages and exit codes

## ⚙️ Installation

```bash
git clone https://github.com/adil-ech/minishell
cd minishell
make
```

This will generate the `minishell` executable.

## 🚀 Usage

```bash
./minishell
```

Start typing commands like in a real shell:

```bash
ls -la | grep .c > out.txt
cat < in.txt | wc -l
export MYVAR=hello
```

## 📁 File Structure

```
minishell/
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── executor.c
│   ├── builtins/
│   ├── signals.c
│   ├── environment.c
│   ├── redirections.c
├── include/
│   └── minishell.h
├── libft/
├── Makefile
```

## 📄 Subject Breakdown

### ✅ Mandatory Part

- Built-in command implementation
- Environment variable parsing and expansion
- Command execution and file descriptor duplication
- Redirection and pipeline management
- Memory and resource cleanup
- Signal handling with `SIGINT`, `SIGQUIT`, `SIGTERM`

### ❌ Bonus Part

*Not implemented in this version.*

## 📬 License

This project is part of the 42 Network curriculum and intended for academic use only.

## 📄 Subject PDF

You can read the official 42 Minishell subject here:\
👉 [Minishell Subject PDF](./en.subject.pdf)

