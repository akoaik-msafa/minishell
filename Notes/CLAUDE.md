# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **Minishell** project - a simple shell implementation written in C that mimics basic bash functionality. The project creates a custom shell with features like command execution, pipes, redirections, built-in commands, and signal handling.

## Build Commands

- **Build project:** `make`
- **Clean objects:** `make clean` 
- **Full clean:** `make fclean`
- **Rebuild:** `make re`
- **Run shell:** `./minishell`

The build system uses a custom libft library (compiled automatically) and links with readline and ncurses libraries.

## Project Architecture

### Core Components

**Headers:**
- `includes/header.h` - Main header with function prototypes
- `includes/data.h` - Data structures and enums for shell internals
- `includes/libft.h` - Custom C library functions

**Key Data Structures:**
- `tree_node` - AST node for command parsing (command, pipe, redirect types)
- `token_t` - Token structure for lexical analysis
- `list_head`/`alloc_list` - Custom memory management system

**Source Modules:**
- `src/main.c` - Main program loop and temporary functions
- `src/read_line.c` - User input handling with readline
- `src/create.c` - AST node creation
- `src/ft_malloc.c` - Custom memory allocator with tracking
- `src/my_strdup.c` - Custom string duplication
- `src/ft_splite.c` - String splitting for tokenization

### Memory Management

The project implements a custom memory tracking system using linked lists (`list_head` and `alloc_list` structures). All allocations go through `ft_malloc()` and can be bulk-freed with `free_all()`.

### Current Implementation Status

The shell is in early development:
- Basic readline integration is implemented
- AST node structure is defined for parsing
- Memory management framework is in place
- Main loop and command execution are still in development

## Project Requirements (from subject)

**Mandatory Features to Implement:**
- Interactive prompt with history
- Command execution (PATH resolution, relative/absolute paths)
- Redirections: `<`, `>`, `<<`, `>>`
- Pipes (`|`)
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Built-ins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Quote handling (single and double quotes)

**Bonus Features:**
- Logical operators (`&&`, `||`) with parentheses
- Wildcards (`*`)

## Development Notes

- Uses 42 School coding standards (Norm)
- Must compile with `-Wall -Wextra -Werror`
- No memory leaks allowed (readline exceptions noted in subject)
- Single global variable allowed only for signal handling
- Take bash as reference for behavior