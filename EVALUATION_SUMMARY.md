# **MINISHELL PROJECT - COMPREHENSIVE EVALUATION SUMMARY**

## **Overview**
This is a fully functional Unix shell implementation written in C that mimics bash behavior. The shell can execute commands, handle pipes, redirections, environment variables, and includes several built-in commands. It uses an **Abstract Syntax Tree (AST)** approach for parsing and execution.

---

## **1. PROGRAM FLOW - FROM START TO FINISH**

### **Entry Point: main()**
When the program starts:

1. **Initialize memory management**: Create two garbage collector heads (`n_head` for command allocations, `env_head` for environment)
2. **Copy environment variables**: From system `envp` to our internal structure
3. **Setup signal handlers**: Handle Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT)
4. **Enter main loop**: Start the interactive prompt

### **Main Loop: while_prompt()**
The shell continuously:

1. **Display prompt**: Shows `minishell$ ` and waits for input
2. **Read user input**:
   - If running in terminal: uses `readline()` with history support
   - If piped input: reads from stdin character by character
3. **Process the command**: Calls `process_prompt()`
4. **Clean up**: Frees all allocations for that command
5. **Repeat**: Until EOF (Ctrl+D) or explicit `exit`

---

## **2. COMMAND PROCESSING PIPELINE**

When you enter a command, it goes through these stages:

### **Stage 1: Tokenization** (`tokenize_input()`)
**Purpose**: Break the input string into meaningful pieces (tokens)

**Example**: `echo "hello" | cat > file.txt`

Becomes:
```
["echo"]  ["hello"]  ["|"]  ["cat"]  [">"]  ["file.txt"]
```

**Process**:
- Call `splite_token()` to split input into word/operator strings
- Identify each token's type:
  - **Operators**: `|`, `<`, `>`, `<<`, `>>`
  - **Built-ins**: `echo`, `cd`, `pwd`, `exit`
  - **Env builtins**: `export`, `unset`, `env`
  - **Words**: Everything else
- Handle quotes:
  - Single quotes (`'`): Make everything literal (no variable expansion)
  - Double quotes (`"`): Allow variable expansion
- Track which tokens need `$` expansion

### **Stage 2: Parsing** (`parse_tokens()`)
**Purpose**: Build an Abstract Syntax Tree (AST) that represents command structure

**Parsing Priority**:
1. **Pipes** (highest priority): Split on `|` and create pipe nodes
2. **Redirections**: Split on `<`, `>`, `<<`, `>>` and create redirection nodes
3. **Simple commands** (lowest priority): Create command nodes with arguments

**Example AST for**: `cat file1 | grep error > output.txt`

```
        [PIPE]
       /      \
   [CMD]      [REDIR >]
    cat       /        \
   file1   [CMD]    output.txt
           grep
           error
```

**AST Node Types**:
- **cmd_node**: Contains command name and arguments array
- **pipe_node**: Has left child (producer) and right child (consumer)
- **redir_node**: Has left child (command) and filename/file descriptor

### **Stage 3: Heredoc Collection** (`collect_heredocs()`)
**Purpose**: Process all heredocs (`<<`) before execution

**Why separate stage?**
- Prevents re-prompting during execution
- Allows proper signal handling during heredoc input

**Process**:
- Traverse entire AST
- Find all heredoc nodes
- For each heredoc:
  - Read lines until delimiter is found
  - Expand variables if needed (based on quote context)
  - Store content in temporary file
  - Save file descriptor in node

### **Stage 4: Execution** (`execute_ast()`)
**Purpose**: Execute the command tree

**Execution Strategy**:

**For cmd_node** (simple command):
1. Check if it's a builtin
   - If yes: Execute directly in parent process (to modify shell environment)
   - If no: Fork and execute as external command
2. Set exit code based on result

**For pipe_node**:
1. Create pipe with `pipe()`
2. Fork child 1:
   - Redirect stdout to pipe write end
   - Execute left subtree (producer)
3. Fork child 2:
   - Redirect stdin to pipe read end
   - Execute right subtree (consumer)
4. Parent closes pipe ends and waits for children
5. Exit code comes from rightmost process

**For redir_node** (redirection):
1. Save original file descriptor
2. Open target file with appropriate mode:
   - `<` : Read mode
   - `>` : Write mode (truncate)
   - `>>`: Write mode (append)
   - `<<`: Use pre-collected heredoc fd
3. Redirect using `dup2()`
4. Execute child command
5. Restore original file descriptor

---

## **3. KEY FEATURES**

### **A. Built-in Commands**
**Executed in parent process** (don't fork):

- **echo [-n]**: Print arguments, `-n` suppresses newline
- **cd [path]**: Change directory (`chdir()`)
- **pwd**: Print current directory (`getcwd()`)
- **export [VAR=value]**: Set environment variables for child processes
- **unset VAR**: Remove environment variables
- **env**: Display all environment variables
- **exit [n]**: Exit shell with code `n` (default: last exit code)

**Why in parent?** These commands need to modify the shell's own state (environment, directory), which wouldn't persist after a fork.

### **B. Variable Expansion**
**Syntax**: `$VARIABLE` or `$?`

**Special variables**:
- `$?`: Last command exit code
- `$HOME`, `$PATH`, etc.: Environment variables

**Expansion rules**:
- Inside double quotes (`"`): **Expanded**
  - Example: `echo "$HOME"` → `/home/user`
- Inside single quotes (`'`): **NOT expanded** (literal)
  - Example: `echo '$HOME'` → `$HOME`
- Escaped with backslash: **NOT expanded**
  - Example: `echo \$HOME` → `$HOME`

**Process**:
1. Find `$` in string
2. Extract variable name
3. Look up value in environment
4. Replace `$VAR` with value
5. Recursively expand rest of string
6. Concatenate results

### **C. Redirections**

| Operator | Name | Behavior |
|----------|------|----------|
| `<` | Input | Read from file instead of stdin |
| `>` | Output | Write to file (overwrite) instead of stdout |
| `>>` | Append | Write to file (append) instead of stdout |
| `<<` | Heredoc | Read from inline content until delimiter |

**Example**: `cat < input.txt | grep error > output.txt`
- `cat` reads from `input.txt`
- Output goes through pipe
- `grep` writes result to `output.txt`

### **D. Pipes**
**Symbol**: `|`

**Mechanism**:
1. Create pipe (has read end and write end)
2. Left command writes to write end
3. Right command reads from read end
4. Data flows automatically through kernel buffer

**Chain example**: `cmd1 | cmd2 | cmd3`
- Parsed as: `cmd1 | (cmd2 | cmd3)`
- Two pipes created
- Data flows: cmd1 → cmd2 → cmd3

### **E. Signal Handling**

| Signal | Key | Behavior |
|--------|-----|----------|
| SIGINT | Ctrl+C | Set global flag `g_signal=130`, display new prompt |
| SIGQUIT | Ctrl+\ | Ignored (no core dump) |

**During command execution**:
- Child processes get default signal handlers
- Parent ignores signals while waiting
- After child finishes, restore shell's handlers

---

## **4. MEMORY MANAGEMENT - GARBAGE COLLECTOR**

### **Problem**: Manual `malloc`/`free` is error-prone, leads to leaks

### **Solution**: Custom garbage collection system

**How it works**:

1. **Allocation**: Call `ft_malloc(size, head)` instead of `malloc()`
   - Allocates memory normally
   - Creates tracking node
   - Adds to linked list

2. **Tracking**: Every allocation is recorded in a linked list:
   ```
   head → [alloc1] → [alloc2] → [alloc3] → NULL
   ```

3. **Cleanup**: Call `free_all(head)` once per command
   - Walks through entire list
   - Frees every allocation
   - Frees tracking nodes
   - Sets head to NULL

**Two separate garbage collectors**:
- `n_head`: Per-command allocations (freed after each command)
- `env_head`: Environment allocations (freed at program exit)

**Custom functions with GC**:
- `my_strdup()`: String duplication with tracking
- `my_strjoin()`: String concatenation with tracking
- `my_ft_strtrim()`: String trimming with tracking

---

## **5. DATA STRUCTURES**

### **Token** (`token_t`)
```c
{
    type: t_word | t_pipe | t_re_in | ...
    str: "actual text"
    expand_flag: 0 (no expand) | 1 (expand)
}
```

### **AST Node** (`tree_node`)
```c
{
    type: cmd_node | pipe_node | redir_node
    args: ["command", "arg1", "arg2", NULL]  // for cmd_node
    filename: "file.txt"                     // for redir_node
    redir_type: t_re_in | t_re_out | ...    // for redir_node
    heredoc_fd: file descriptor              // for heredoc
    left: pointer to left child
    right: pointer to right child
}
```

### **Environment** (`t_env`)
```c
{
    envp: ["PATH=/bin:/usr/bin", "HOME=/home/user", ...]
    export_only: ["VAR1=value", "VAR2=value", ...]
    count: number of variables
}
```

### **Data Container** (`t_data`)
```c
{
    n_head: garbage collector for commands
    env: environment variables
    env_head: garbage collector for environment
    current_expand_flag: whether to expand variables
    exit_code: last command's exit status
}
```

---

## **6. EXTERNAL COMMAND EXECUTION**

**Process** (`fork_and_execute()`):

1. **Fork**: Create child process
   ```c
   pid = fork();
   ```

2. **In child process**:
   ```c
   - Reset signal handlers to default
   - Find command in PATH using get_cmd_path()
     • Absolute path (/bin/ls): use directly
     • Relative path (./script): check accessibility
     • Command name (ls): search in PATH directories
   - Validate command exists and is executable
   - Execute: execve(path, args, environment)
   - If execve fails: exit with code 127
   ```

3. **In parent process**:
   ```c
   - Wait for child to finish
   - Get exit status with waitpid()
   - Convert status to exit code (0-255)
   - Store in data->exit_code
   ```

**Exit codes**:
- `0`: Success
- `1-125`: Command-specific errors
- `126`: Command not executable
- `127`: Command not found
- `130`: Killed by Ctrl+C (SIGINT)

---

## **7. ENVIRONMENT VARIABLE SYSTEM**

**Two arrays maintained**:

1. **`envp`**: Regular environment (PATH, HOME, USER, etc.)
   - Inherited from parent shell
   - Modified by `export VAR=value`
   - Passed to child processes

2. **`export_only`**: Export-declared variables
   - Variables set with `export` but no value
   - Example: `export VAR` (without `=value`)
   - Also passed to child processes

**Operations**:
- `export VAR=value`: Add to both arrays
- `export VAR+=value`: Append to existing value
- `unset VAR`: Remove from both arrays
- `env`: Display only `envp` (not `export_only`)

**SHLVL handling**:
- Tracks shell nesting level
- Incremented on shell start
- Decremented on exit (in parent shell)

---

## **8. QUOTE HANDLING**

### **Single Quotes** (`'...'`)
- Everything inside is **literal**
- No variable expansion
- No escape sequences
- **Example**: `echo '$HOME'` → `$HOME`

### **Double Quotes** (`"..."`)
- Variable expansion **enabled**
- Whitespace preserved
- **Example**: `echo "Hello $USER"` → `Hello msafa`

### **No Quotes**
- Variables expanded
- Whitespace splits arguments
- **Example**: `echo $HOME` → `/home/msafa`

### **Escaped Characters**
- `\$`: Literal dollar sign
- `\"`: Literal quote
- **Example**: `echo \$HOME` → `$HOME`

---

## **9. ERROR HANDLING**

### **Syntax errors**:
- Pipe at start/end: `| command` or `command |`
- Redirection without file: `cat >`
- Unclosed quotes: `echo "hello`

**Response**: Print error, don't execute

### **Runtime errors**:
- Command not found: Exit code 127
- Permission denied: Exit code 126
- File not found (redirection): Exit code 1

### **Signal handling**:
- Ctrl+C during command: Kill command, show new prompt
- Ctrl+C during heredoc: Cancel heredoc, show prompt

---

## **10. CRITICAL COMPONENTS**

### **File**: `main.c`
- Program entry point
- Main loop
- Signal initialization

### **File**: `split_cmd.c`, `extract_word.c`
- Tokenization logic
- Quote handling
- Operator detection

### **File**: `parser.c`, `create.c`
- AST construction
- Syntax validation
- Node creation

### **File**: `command_exec.c`
- Main execution dispatcher
- Builtin vs external decision
- AST traversal

### **File**: `pipe_exec.c`
- Pipe creation and management
- Process forking for pipes
- Heredoc collection

### **File**: `builtin_exec.c` + Built-ins directory
- All builtin command implementations
- Direct execution without fork

### **File**: `expand.c`
- Variable expansion algorithm
- Quote-aware parsing
- Recursive expansion

### **File**: `ft_malloc.c`
- Garbage collection system
- Memory leak prevention

---

## **11. ANSWERING EVALUATOR QUESTIONS**

### **"How does your shell work?"**
> "The shell follows a pipeline architecture: it reads user input, tokenizes it into words and operators while handling quotes, builds an Abstract Syntax Tree based on operator precedence (pipes, then redirections, then commands), pre-processes heredocs, and finally executes the tree recursively. Commands can be builtins executed directly in the parent process, or external commands executed in forked child processes."

### **"How do you handle pipes?"**
> "Pipes are implemented using the `pipe()` system call which creates a unidirectional data channel. We fork two child processes: the left process redirects its stdout to the pipe's write end using `dup2()`, and the right process redirects its stdin to the pipe's read end. The parent process closes both pipe ends and waits for both children. The exit code comes from the rightmost process in the pipeline."

### **"How does variable expansion work?"**
> "We parse the string to find unescaped dollar signs, extract the variable name, look it up in the environment, and replace it with the value. Special handling for `$?` which returns the last exit code. Expansion respects quote context: single quotes disable it entirely, double quotes enable it, and backslash escapes individual characters. The process is recursive to handle multiple variables in one string."

### **"How do you prevent memory leaks?"**
> "We implemented a garbage collection system using `ft_malloc()` instead of `malloc()`. Every allocation is tracked in a linked list. After processing each command, we call `free_all()` which walks the list and frees everything at once. We maintain two separate garbage collectors: one per-command and one for the environment that persists for the entire session."

### **"What's the difference between pipes and redirections?"**
> "Redirections change where a single command reads from or writes to - typically involving files. Pipes connect the output of one command directly to the input of another command, creating a data pipeline. Technically, pipes use in-memory kernel buffers while redirections use file descriptors pointing to actual files."

### **"How do builtins differ from external commands?"**
> "Builtins like `cd`, `export`, and `exit` must run in the parent process because they need to modify the shell's own state - changing directory, updating environment variables, or terminating the shell itself. These changes wouldn't persist if executed in a forked child process. External commands run in child processes created with `fork()` and don't affect the parent shell's state."

### **"How do you handle signals?"**
> "We use `sigaction()` to set custom handlers. SIGINT (Ctrl+C) sets a global flag to 130 and displays a new prompt without terminating the shell. SIGQUIT (Ctrl+\) is ignored entirely. During command execution, child processes get default signal handlers, allowing them to be interrupted normally, while the parent remains responsive."

---

## **12. PROJECT STRENGTHS**

✅ **Clean architecture**: Clear separation between tokenization, parsing, and execution
✅ **AST-based execution**: Flexible and extensible design
✅ **Robust memory management**: Garbage collection prevents leaks
✅ **Comprehensive features**: All required builtins, pipes, redirections, expansions
✅ **Quote-aware parsing**: Proper handling of single/double quotes
✅ **Signal handling**: Non-terminating Ctrl+C behavior
✅ **Heredoc pre-processing**: Avoids re-prompting issues
✅ **Well-documented code**: Clear function names and structure

---

## **VISUAL FLOW DIAGRAM**

```
┌─────────────────────────────────────────────────────────┐
│  USER TYPES: echo "Hello $USER" | grep Hello > out.txt │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
          ┌──────────────────────┐
          │   TOKENIZATION       │
          │  ["echo"] ["Hello    │
          │  $USER"] ["|"]       │
          │  ["grep"] ["Hello"]  │
          │  [">"] ["out.txt"]   │
          └──────────┬───────────┘
                     │
                     ▼
          ┌──────────────────────┐
          │   PARSING (AST)      │
          │         [PIPE]       │
          │        /     \       │
          │    [CMD]   [REDIR>]  │
          │     echo   /      \  │
          │           [CMD]   file
          │           grep         │
          └──────────┬───────────┘
                     │
                     ▼
          ┌──────────────────────┐
          │   EXPANSION          │
          │  "Hello $USER" →     │
          │  "Hello msafa"       │
          └──────────┬───────────┘
                     │
                     ▼
          ┌──────────────────────┐
          │   EXECUTION          │
          │  fork() → echo       │
          │  fork() → grep       │
          │  pipe() connects     │
          │  output redirected   │
          └──────────┬───────────┘
                     │
                     ▼
          ┌──────────────────────┐
          │   CLEANUP            │
          │  free_all(n_head)    │
          │  exit_code = 0       │
          └──────────────────────┘
```

---

## **QUICK REFERENCE - KEY CONCEPTS**

### **Execution Flow**
```
Input → Tokenize → Parse (AST) → Collect Heredocs → Execute → Cleanup
```

### **AST Node Types**
- **cmd_node**: Simple command with arguments
- **pipe_node**: Connects two commands with pipe
- **redir_node**: Redirects input/output to/from files

### **Memory Management**
- `ft_malloc()`: Allocate with tracking
- `free_all()`: Free everything at once
- Two collectors: per-command and environment

### **Process Execution**
- **Builtins**: Execute in parent (modify shell state)
- **External**: Fork child, find in PATH, execve()

### **Important System Calls**
- `fork()`: Create child process
- `pipe()`: Create pipe for inter-process communication
- `dup2()`: Duplicate file descriptor for redirection
- `execve()`: Replace process with new program
- `waitpid()`: Wait for child process
- `chdir()`: Change directory
- `getcwd()`: Get current directory

---

This comprehensive summary covers all aspects of your minishell implementation. You should now be able to confidently explain any part of the project during your evaluation. Good luck!
