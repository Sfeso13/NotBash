
# 🐚 NotBash

*This project has been created as part of the 42 curriculum.*


## 🏆 Credits & Contributions
**NotBash** was a collaborative effort as part of the 42 curriculum.
 - Teammate: [Adil Ech](https://github.com/adil-ech) – Hosted the repository, initial project setup, parsing logic and signal handling.
 - My Contributions:
   - Implemented a custom environment for the shell (srcs/exec/builtins/environment)
   - Implemented builtin commands from scratch (srcs/exec/builtins)
   - Worked on external command handling (srcs/exec/externals/)
   - Implemented execution logic of commands, pipes and redirections
   - Improved signal handling (sig.c)

---

## 📋 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Setup](#-setup)
- [Usage and Controls](#-usage)

---

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Film%20Projector.png" alt="Film Projector" width="25" height="25" /> About

**NotBash** is a simplified Unix shell with the following functionality:
 - Execute external programs using execve
 - Handle built-in commands: echo, cd, pwd, export, unset, env, exit
 - Manage pipes (|) and redirections (<, >, >>, <<)
 - Handle environment variables and $ expansions
 - Respond to signals (Ctrl-C, Ctrl-D)
 - Provide error messages and proper exit codes

Technically, it focuses on:
 - Process creation and management
 - File descriptor duplication and redirection
 - Command parsing and tokenization
 - Signal handling and cleanup
 - Memory safety and leak prevention

---

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Control%20Knobs.png" alt="Control Knobs" width="25" height="25" /> Features

- ✅ Built-in commands implemented
- ✅ External command execution with execve
- ✅ Pipe support
- ✅ Input/output redirections
- ✅ Environment variable management
- ✅ Signal handling (SIGINT, SIGQUIT)
- ✅ Proper memory management

---

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Card%20File%20Box.png" alt="Card File Box" width="25" height="25" /> Project Structure

<details>
   <summary>Click to expand</summary>
  
```
.
├── debug_print.c
├── includes/
│   ├── exec/
│   │   ├── builtins.h
│   │   ├── builtins_utils.h
│   │   ├── exec.h
│   │   └── exec_utils.h
│   ├── global/
│   │   ├── helpers.h
│   │   ├── minishell.h
│   │   └── structs.h
│   └── parsing/
│       └── parsing.h
├── main.c
├── Makefile
├── readme.md
├── sig.c
└── srcs/
    ├── exec/
    │   ├── builtins/
    │   │   ├── directories/
    │   │   │   ├── cd.c
    │   │   │   ├── echo.c
    │   │   │   └── pwd.c
    │   │   └── environment/
    │   │       ├── env.c
    │   │       ├── env_utils.c
    │   │       ├── exit.c
    │   │       ├── export.c
    │   │       ├── export_print.c
    │   │       ├── export_utils.c
    │   │       ├── export_var.c
    │   │       ├── getenv.c
    │   │       ├── reset_env.c
    │   │       ├── status.c
    │   │       ├── unset.c
    │   │       ├── validate_id.c
    │   │       └── validate_id_unset.c
    │   ├── externals/
    │   │   ├── args_split.c
    │   │   ├── check_args.c
    │   │   ├── get_io_files.c
    │   │   ├── here_doc.c
    │   │   ├── here_doc_utils.c
    │   │   ├── multi_utils.c
    │   │   ├── prepare_args.c
    │   │   ├── prepare_args_utils.c
    │   │   ├── preparing_iofiles.c
    │   │   └── preparing_iofiles_utils.c
    │   ├── builtins.c
    │   ├── exec.c
    │   ├── exec_utils.c
    │   ├── externals.c
    │   ├── improved_cmp.c
    │   ├── multi_exec.c
    │   ├── multi_exec_utils.c
    │   └── single_process.c
    ├── helpers/
    │   ├── arr_len.c
    │   ├── clear_env.c
    │   ├── clear_shell.c
    │   ├── clear_tokens.c
    │   ├── count_custom_words.c
    │   ├── count_words.c
    │   ├── delone_env.c
    │   ├── delone_shell.c
    │   ├── delone_token.c
    │   ├── env_size.c
    │   ├── free_tab.c
    │   ├── ft_atoi.c
    │   ├── ft_bzero.c
    │   ├── ft_cal... (truncated for brevity)
    │   ├── ft_strdup.c
    │   ├── ft_strlen.c
    │   ├── ft_strjoin.c
    │   ├── ft_strlcat.c
    │   ├── ft_strlcpy.c
    │   ├── ft_strncmp.c
    │   ├── ft_strncpy.c
    │   ├── ft_substr.c
    │   ├── ft_trim.c
    │   ├── ft_split.c
    │   ├── ft_splithelpers.c
    │   ├── ft_old_split.c
    │   ├── ft_isalnum.c
    │   ├── ft_realloc.c
    │   ├── ft_putstr_fd.c
    │   ├── ft_itoa.c
    │   ├── get_env_value.c
    │   ├── search_token.c
    │   └── ...
    └── parsing/
        ├── analyze_in_expand.c
        ├── cmd_filler.c
        ├── cmd_fillhelp.c
        ├── cleaners.c
        ├── displayread.c
        ├── exdoc.c
        ├── exdochelp.c
        ├── expa_helptw.c
        ├── expa_hepdw.c
        ├── expa_nhelp.c
        ├── expa_nhelptwo.c
        ├── expantion.c
        ├── expantion_helpers.c
        ├── expantion_init.c
        ├── isbuiltin.c
        ├── misplacing.c
        ├── not_supported.c
        ├── rmquotes.c
        ├── syncatcher.c
        ├── syncatchhelpers.c
        ├── tokenize_f.c
        └── tokenize_help.c

```
</details>

---

## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Gear.png" alt="Gear" width="25" height="25" /> Setup

1. **Clone the repository**
```bash
git clone https://github.com/Sfeso13/NotBash.git
cd NotBash
```
2. **Compile the program**
```bash
make
```
This creates a runnable program called `minishell`.

3. **Clean compiled objects**
```bash
make clean      # remove object files
make fclean     # remove object files and library
make re         # rebuild everything
```

---


## <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Abacus.png" alt="Abacus" width="25" height="25" /> Usage

1. **Start the shell**
```bash
./minishell
```

2. **Start typing running shell commands**
```bash
ls -la | grep .c > out.txt
cat < in.txt | wc -l
export MYVAR=hello
```

