# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a minishell implementation in C - a simplified Unix shell that supports basic command execution, tokenization, and parsing. The project follows the 42 School coding standards.

## Build Commands

- `make` - Build the minishell executable
- `make clean` - Remove object files  
- `make fclean` - Remove object files and executable
- `make re` - Full rebuild (fclean + make)

The project uses libft (custom C library) and requires readline/ncurses libraries.

## Architecture

### Core Components

**Memory Management**: Custom memory allocator system using linked lists (`struct list_head`, `struct alloc_list`) to track all allocations and enable batch cleanup via `free_all()`.

**Tokenization Pipeline**: 
1. Input splitting (`split_string()`) 
2. Token type identification (WORD, PIPE, redirections)
3. Token array creation with EOF marker

**Data Structures**:
- `token_t` - Contains token type and string value
- `tree_node` - AST node for parsed commands with type (cmd/pipe/redirect), args array, left/right children, filename, and redirect type
- Token types: `t_word`, `t_pipe`, `t_re_in`, `t_re_out`, `t_re_append`, `t_re_heredoc`, `t_eof`

### File Organization

- `src/main.c` - Main loop with readline integration and debug output
- `src/token.c` - Tokenization logic and token type identification
- `src/create.c` - AST node creation and command parsing (currently basic)
- `src/ft_malloc.c` - Custom memory management
- `includes/data.h` - Core data structure definitions
- `includes/header.h` - Function prototypes and includes

### Current State

The shell currently handles:
- Input reading with readline
- Tokenization of commands and operators
- Basic command node creation  
- Memory management with cleanup

**Note**: Parser implementation (`parse_tokens`) is minimal - only creates simple command nodes. Pipe handling, redirections, and command execution are not yet implemented.