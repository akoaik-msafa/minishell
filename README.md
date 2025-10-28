# MINISHELL - COMPLETE EVALUATION SUMMARY

## TABLE OF CONTENTS
1. [Project Overview](#project-overview)
2. [Architecture & Design](#architecture--design)
3. [Complete Execution Flow](#complete-execution-flow)
4. [Memory Management (Garbage Collector)](#memory-management-garbage-collector)
5. [Tokenization & Parsing](#tokenization--parsing)
6. [Abstract Syntax Tree (AST)](#abstract-syntax-tree-ast)
7. [Variable Expansion](#variable-expansion)
8. [Execution System](#execution-system)
9. [Built-in Commands](#built-in-commands)
10. [Redirections](#redirections)
11. [Heredoc Implementation](#heredoc-implementation)
12. [Pipes](#pipes)
13. [Signal Handling](#signal-handling)
14. [Environment Variables](#environment-variables)
15. [Exit Codes](#exit-codes)
16. [Important Evaluation Questions](#important-evaluation-questions)

---

## PROJECT OVERVIEW

**Minishell** is a Unix shell implementation that mimics the behavior of Bash. It handles:
- Command execution (external programs + built-ins)
- Pipes (`|`)
- Redirections (`<`, `>`, `>>`, `<<`)
- Variable expansion (`$VAR`, `$?`)
- Signal handling (Ctrl+C, Ctrl+\, Ctrl+D)
- Environment variables
- Quotes (single `'` and double `"`)

**Total Files**: 48 `.c` files, 5 `.h` headers
**Lines of Code**: ~3500+ lines

**Key Features**:
- Custom garbage collector (automatic memory management)
- Recursive descent parser
- Abstract Syntax Tree (AST) for command representation
- Process isolation using `fork()`
- Proper signal handling in different contexts

---

## ARCHITECTURE & DESIGN

### **Project Structure**
```
minishell/
├── includes/
│   ├── header.h        # Main header with function prototypes
│   ├── data.h          # Data structures (AST, tokens, env)
│   ├── builtin.h       # Built-in function declarations
│   ├── gv.h            # Global variable (g_signal)
│   └── libft.h         # Libft functions
├── src/
│   ├── main.c          # Entry point
│   ├── read_line.c     # Prompt and input
│   ├── Built-ins/      # 7 built-in commands
│   ├── Execution/      # Command execution logic
│   ├── export/         # Export command implementation
│   ├── parsing/        # Tokenization, parsing, AST
│   ├── split/          # String splitting with quotes
│   └── utils/          # Utilities (malloc, env, init)
└── libft/              # Libft library
```

### **Data Flow**
```
User Input → Tokenization → Parsing → AST Creation → Execution
                                          ↓
                              Heredoc Pre-collection (for pipes)
```

### **Key Data Structures**

#### **1. t_data (Global Context)**
```c
typedef struct t_data {
    t_list_head *n_head;        // Garbage collector for temp allocations
    t_env       *env;           // Environment variables
    t_list_head *env_head;      // Garbage collector for env allocations
    int         exit_code;      // Exit code of last command
} t_data;
```

#### **2. t_tree_node (AST Node)**
```c
typedef struct t_tree_node {
    node_type   type;           // cmd_node, pipe_node, redir_node
    char        **args;         // Command arguments
    char        *filename;      // For redirections (filename or delimiter)
    token_type  redir_type;     // t_re_in, t_re_out, t_re_append, t_re_heredoc
    int         heredoc_fd;     // Cached heredoc file descriptor
    char        *expansion;     // Expansion flag for heredoc delimiter
    struct t_tree_node *left;   // Left child
    struct t_tree_node *right;  // Right child
} t_tree_node;
```

#### **3. token_t (Token)**
```c
typedef struct {
    token_type  type;           // t_word, t_pipe, t_re_in, etc.
    char        *str;           // Token string
    int         expand_flag;    // Should expand variables? (0=no, 1=yes)
} token_t;
```

#### **4. t_env (Environment)**
```c
typedef struct t_env {
    char    **envp;            // Environment variables (NAME=VALUE)
    char    **export_only;     // Variables declared but not exported
    int     count;             // Count of environment variables
} t_env;
```

---

## COMPLETE EXECUTION FLOW

### **Step-by-Step Process**

```
1. main() [main.c:75]
   ├─> Initialize garbage collectors (n_head, env_head)
   ├─> Initialize environment (init_env)
   ├─> Setup signal handlers (init_sigaction)
   └─> Enter main loop (while_prompt)

2. while_prompt() [main.c:53]
   ├─> Get user input (readline)
   ├─> Check global signal (g_signal)
   └─> Process prompt

3. process_prompt() [main.c:28]
   ├─> Tokenize input (tokenize_input)
   ├─> Parse tokens (parse_tokens) → Creates AST
   ├─> Pre-collect heredocs (handle_heredocs)
   └─> Execute AST (execute_ast)

4. execute_ast() [command_exec.c:46]
   ├─> If cmd_node: execute_command()
   ├─> If pipe_node: execute_pipe()
   └─> If redir_node: handle redirections

5. After execution:
   ├─> Free all temp allocations (free_all)
   └─> Loop back to prompt
```

### **Detailed Flow Diagram**
```
┌─────────────────────────────────────────────────────────────┐
│                        MAIN LOOP                             │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
                    ┌───────────────┐
                    │ get_user_input│
                    │  readline()   │
                    └───────┬───────┘
                            │
                            ▼
                ┌───────────────────────┐
                │  tokenize_input()     │
                │  Split into tokens    │
                └───────┬───────────────┘
                        │
                        ▼
                ┌───────────────────────┐
                │   parse_tokens()      │
                │   Build AST tree      │
                └───────┬───────────────┘
                        │
                        ▼
                ┌───────────────────────┐
                │  collect_heredocs()   │
                │  Pre-execute heredocs │
                └───────┬───────────────┘
                        │
                        ▼
                ┌───────────────────────┐
                │    execute_ast()      │
                │   Execute command     │
                └───────┬───────────────┘
                        │
                        ▼
                ┌───────────────────────┐
                │     free_all()        │
                │  Clean up memory      │
                └───────┬───────────────┘
                        │
                        └──────► Loop back
```

---

## MEMORY MANAGEMENT (GARBAGE COLLECTOR)

### **Why Custom Malloc?**
Instead of manually tracking every `malloc()` and calling `free()`, the project uses a **garbage collector**.

### **How It Works**

#### **ft_malloc() [ft_malloc.c:15]**
```c
void *ft_malloc(size_t size, t_list_head *n_head)
{
    void *ptr = malloc(size);
    struct alloc_list *node = malloc(sizeof(struct alloc_list));

    node->allocation = ptr;
    node->next = n_head->head;
    n_head->head = node;        // Add to linked list

    return ptr;
}
```

**Process**:
1. Allocate memory normally with `malloc()`
2. Create a tracking node
3. Add node to linked list (garbage collector)
4. Return pointer

#### **free_all() [ft_malloc.c:37]**
```c
void free_all(t_list_head *n_head)
{
    struct alloc_list *current = n_head->head;

    while (current)
    {
        free(current->allocation);  // Free actual data
        tmp = current;
        current = current->next;
        free(tmp);                  // Free tracking node
    }
    n_head->head = NULL;
}
```

### **Two Separate Allocators**
1. **n_head**: Temporary allocations (tokens, AST, command args)
   - Freed after each command execution
2. **env_head**: Environment allocations (persistent)
   - Freed only when shell exits

### **Benefits**
- No memory leaks (everything tracked)
- No manual `free()` needed for most allocations
- Clean separation: temp vs persistent data
- Simple cleanup: one function call

### **Usage Example**
```c
// Instead of: char *str = malloc(100);
char *str = ft_malloc(100, data->n_head);

// No need to free individually
// At end of command: free_all(n_head);
```

---

## TOKENIZATION & PARSING

### **Phase 1: Tokenization**

#### **Process** [split_cmd.c:33]
```
Input: "echo hello | cat > file.txt"
    ↓
Split into strings:
["echo", "hello", "|", "cat", ">", "file.txt"]
    ↓
Create tokens with types:
[t_builtin:"echo", t_word:"hello", t_pipe:"|", t_word:"cat",
 t_re_out:">", t_word:"file.txt", t_eof]
```

#### **Token Types** [data.h:45]
```c
typedef enum {
    t_word,         // Regular word/command/argument
    t_builtin,      // echo, cd, pwd, exit
    t_env_builtin,  // export, unset, env (modify environment)
    t_pipe,         // |
    t_re_in,        // <
    t_re_out,       // >
    t_re_append,    // >>
    t_re_heredoc,   // <<
    t_eof           // End of tokens
} token_type;
```

#### **Tokenization Steps**
1. **Count tokens**: Count words, operators, handling quotes
2. **Split string**: Extract each token with quote awareness
3. **Create token array**: Build `token_t` array
4. **Identify types**: Classify each token (operator, builtin, word)
5. **Set expand_flag**: Determine if token should expand variables

### **Quote Handling**
- **Single quotes (`'`)**: No expansion, literal
  - `'$USER'` → `$USER` (literal)
- **Double quotes (`"`)**: Expansion enabled
  - `"$USER"` → `msafa` (expanded)
- **Quote removal**: Quotes are removed during tokenization
- **Escaped chars**: `\$` → `$` (backslash removed)

### **Expansion Flag**
Each token has `expand_flag`:
- `1`: Expand variables (unquoted or double-quoted)
- `0`: Literal (single-quoted)

---

## ABSTRACT SYNTAX TREE (AST)

### **Why AST?**
The AST represents the command structure in a tree format, making it easy to:
- Handle operator precedence
- Execute commands recursively
- Support nested structures

### **Node Types** [data.h:82]
```c
typedef enum {
    cmd_node,       // Command with arguments
    pipe_node,      // Pipe between two commands
    redir_node      // Redirection
} node_type;
```

### **AST Examples**

#### **Example 1: Simple Command**
```bash
echo hello world
```
```
AST:
cmd_node
  args: ["echo", "hello", "world"]
```

#### **Example 2: Pipe**
```bash
cat file.txt | grep hello
```
```
AST:
pipe_node
  ├─ left: cmd_node(args: ["cat", "file.txt"])
  └─ right: cmd_node(args: ["grep", "hello"])
```

#### **Example 3: Redirection**
```bash
cat < input.txt > output.txt
```
```
AST:
redir_node (< input.txt)
  └─ left: redir_node (> output.txt)
       └─ left: cmd_node(args: ["cat"])
```

#### **Example 4: Complex**
```bash
cat <<EOF | grep hello > out.txt
line1
line2
EOF
```
```
AST:
pipe_node
  ├─ left: redir_node (<<EOF, heredoc_fd=3)
  │         └─ left: cmd_node(args: ["cat"])
  └─ right: redir_node (>out.txt)
             └─ left: cmd_node(args: ["grep", "hello"])
```

### **Parsing Algorithm** [parser.c:85]

**Recursive Descent Parser**:
1. **Find pipe**: If pipe exists, split into left|right, recurse
2. **Find redirection**: If redirection exists, create redir_node
3. **Base case**: No operators → create cmd_node

```c
t_tree_node *parse_tokens(token_t *tokens, int count, ...)
{
    // 1. Find pipe (highest precedence)
    if (pipe_found)
        return create_pipe_node(
            parse_left_side(),
            parse_right_side()
        );

    // 2. Find redirection
    if (redir_found)
        return handle_redirection_parsing();

    // 3. Base case: command
    return create_cmd_node();
}
```

### **Syntax Validation** [parser.c:29]
```c
// Check for errors:
- Pipe at start or end: "| cat" or "cat |"
- Redirection without file: "cat >" or "cat <"
```

---

## VARIABLE EXPANSION

### **What Gets Expanded?**
- `$VAR` → Value of environment variable VAR
- `$?` → Exit code of last command
- `$NONEXISTENT` → Empty string (not error)

### **When Expansion Happens**
1. **During tokenization**: `expand_flag` is set
2. **During AST creation**: Variables in command args are expanded
3. **During heredoc input**: Line-by-line expansion (if not quoted)
4. **During redirection**: Filenames can be expanded

### **Expansion Algorithm** [expand.c:54]

**Recursive expansion**:
```c
char *expand_variable(const char *str, t_data *data)
{
    // 1. Find first $ (extract_prefix)
    prefix = extract_prefix(str, &dollar_pos, data);

    // 2. Get variable name (until non-alphanumeric)
    var_name = str + dollar_pos + 1;
    var_len = get_var_name_length(var_name);

    // 3. Recursively expand rest of string
    suffix = expand_variable(var_name + var_len, data);

    // 4. Get variable value
    if (var_name[0] == '?')
        var_value = itoa(exit_code);
    else
        var_value = find_env_value(var_name, env);

    // 5. Concatenate: prefix + var_value + suffix
    return build_result(prefix, var_value, suffix, data);
}
```

### **Example**
```
Input: "Hello $USER, exit=$?"
       (exit_code = 0, USER=msafa)

Step 1: prefix = "Hello ", var = "USER", suffix = ", exit=$?"
Step 2: Recursively expand suffix:
        prefix = ", exit=", var = "?", suffix = ""
        Result: ", exit=0"
Step 3: Build: "Hello " + "msafa" + ", exit=0"
Result: "Hello msafa, exit=0"
```

### **Escaped Dollar** [expand.c:98]
```c
// \$ is treated as literal $
"echo \$USER" → "echo $USER" (no expansion)
```

**Process**:
1. Check `has_unescaped_dollar()`: Does string have unescaped $?
2. If yes: `expand_variable()`
3. If no: `remove_escape_dollar()` (remove backslashes)

---

## EXECUTION SYSTEM

### **Main Execution Function** [command_exec.c:46]

```c
void execute_ast(t_tree_node *ast, t_data *data)
{
    if (ast->type == cmd_node)
        execute_command(ast, data);
    else if (ast->type == pipe_node)
        execute_pipe(ast, data);
    else if (ast->type == redir_node)
        handle_redirections(ast, data);
}
```

### **Command Execution** [command_exec.c:31]

```c
void execute_command(t_tree_node *node, t_data *data)
{
    // 1. Try built-in first
    builtin_result = execute_builtin(node, data);
    if (builtin_result != -1)
        return;  // Built-in handled it

    // 2. External command
    fork_and_execute(node, data);
}
```

### **Fork and Execute** [cmd_fork.c:34]

```c
void fork_and_execute(t_tree_node *node, t_data *data)
{
    pid = fork();

    if (pid == 0)  // Child process
    {
        signal(SIGINT, SIG_DFL);   // Restore signals
        signal(SIGQUIT, SIG_DFL);
        exec_cmd(node, data->env); // Execute command
        exit(127);                  // If execve fails
    }
    else  // Parent process
    {
        signal(SIGINT, SIG_IGN);   // Ignore signals during wait
        signal(SIGQUIT, SIG_IGN);
        waitpid(pid, &status, 0);  // Wait for child
        set_exit_code_from_status(data, status);
        init_sigaction(&sa);       // Restore signal handlers
    }
}
```

### **External Command Execution** [command_exec.c:15]

```c
void exec_cmd(t_tree_node *node, t_env *env)
{
    // 1. Get command path
    cmd_path = get_cmd_path(node->args[0], env);
    //    - If path contains '/', use as-is: "./script"
    //    - Otherwise, search in PATH: "/usr/bin/ls"

    // 2. Validate (check if executable, is directory, etc.)
    validate_cmd_path(cmd_path);

    // 3. Execute
    execve(cmd_path, node->args, env->export_only);

    // 4. If we reach here, execve failed
    perror(cmd_path);
    exit(127);
}
```

### **Why Fork?**
1. **Isolation**: Child process terminates, parent (shell) continues
2. **Signal handling**: Different signal behavior in child vs parent
3. **Exit codes**: Parent can wait and get child's exit status
4. **Built-ins DON'T fork**: They modify shell state directly

---

## BUILT-IN COMMANDS

**7 Built-ins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

### **Why Built-ins Don't Fork?**
Built-ins modify the shell's state (environment, current directory, exit status). If we fork:
- `cd` would change child's directory, not shell's
- `export` would modify child's environment, not shell's
- `exit` would exit child, not shell

### **1. echo** [echo.c:78]
```c
int ft_echo(char **args)
{
    // 1. Check for -n option (no newline)
    option = process_echo_options(args);  // Handles -n, -nn, -nnn

    // 2. Skip all -n flags
    while (args[i] is -n flag)
        i++;

    // 3. Print arguments with spaces
    print_echo_args(args, start_index);

    // 4. Print newline if no -n option
    if (!option)
        write(1, "\n", 1);

    return 0;
}
```

**Features**:
- Multiple `-n` flags: `echo -n -n -n hello` (no newline)
- Mixed `-n` and `-nnn`: All valid
- Stops at first non-option: `echo -n hello -n` (prints "-n")

### **2. cd** [cd.c:40]
```c
int ft_cd(char **args, t_env *env, t_list_head *n_head)
{
    // 1. Check argument count
    if (args[0] && args[1])
        return error("too many arguments");

    // 2. Get path
    if (!args[0])
        path = getenv("HOME");  // cd with no args → HOME
    else
        path = extract_quoted_path(args[0]);  // Handle quotes

    // 3. Change directory
    result = chdir(path);
    if (result == -1)
        perror("cd");

    return (result == -1) ? 1 : 0;
}
```

**Features**:
- `cd` → Goes to HOME
- `cd path` → Changes to path
- `cd too many args` → Error
- Handles quoted paths: `cd "path with spaces"`

### **3. pwd** [pwd.c]
```c
int ft_pwd(char **args)
{
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return 0;
    }
    perror("pwd");
    return 1;
}
```

**Simple**: Prints current working directory using `getcwd()`.

### **4. export** [export.c:73]
```c
int ft_export(char **args, t_data *data)
{
    // 1. No arguments: print all exported variables (sorted)
    if (!args[0])
    {
        sorted = sorted_env(data->env);
        print_sorted(sorted);  // Format: declare -x VAR="value"
        return 0;
    }

    // 2. Process each argument
    for each arg:
    {
        // Validate identifier: [a-zA-Z_][a-zA-Z0-9_]*
        if (!validate_identifier(arg))
            return error("not a valid identifier");

        // Check if variable exists
        index_env = find_env_var(arg, env->envp);
        index_export = find_env_var(arg, env->export_only);

        if (exists)
            handle_existing_var(arg);  // Update or append
        else
            handle_new_var(arg);       // Add new variable
    }
}
```

**Features**:
- `export VAR=value` → Adds to environment
- `export VAR+=value` → Appends to existing variable
- `export VAR` → Marks as exported (no value)
- `export` → Prints all exported vars (sorted alphabetically)

**Two Arrays**:
1. **env->envp**: Variables exported to child processes
2. **env->export_only**: Variables declared but not set

### **5. unset** [unset.c]
```c
int ft_unset(char **args, t_env *env)
{
    for each arg:
    {
        // Validate identifier
        if (!validate_identifier(arg))
            continue;

        // Find and remove from envp
        index = find_env_var(arg, env->envp);
        if (found)
            remove_from_array(env->envp, index);

        // Find and remove from export_only
        index = find_env_var(arg, env->export_only);
        if (found)
            remove_from_array(env->export_only, index);
    }
    return 0;
}
```

**Features**:
- Removes variable from both `envp` and `export_only`
- Invalid identifiers are ignored (no error)
- Multiple variables: `unset VAR1 VAR2 VAR3`

### **6. env** [env.c]
```c
int ft_env(char **args, t_env *env)
{
    // 1. No arguments allowed
    if (args[0])
        return error("env with arguments not supported");

    // 2. Print all environment variables
    for (int i = 0; env->envp[i]; i++)
        printf("%s\n", env->envp[i]);

    return 0;
}
```

**Features**:
- Prints `envp` (not `export_only`)
- Format: `VAR=value` (one per line)

### **7. exit** [exit.c:33]
```c
int ft_exit(char **args, t_data *data)
{
    // 1. No arguments: exit with last exit code
    if (!args[0])
        exit(data->exit_code);

    // 2. Too many arguments
    if (args[1])
        return error("too many arguments");  // Returns 1, doesn't exit

    // 3. Non-numeric argument
    if (!is_numeric(args[0]))
    {
        write(2, "numeric argument required\n");
        exit(2);
    }

    // 4. Exit with specified code (mod 256)
    exit_code = atoi(args[0]);
    exit((unsigned char)(exit_code % 256));
}
```

**Features**:
- `exit` → Exits with last exit code
- `exit 0` → Exits with 0
- `exit 42` → Exits with 42
- `exit 300` → Exits with 44 (300 % 256)
- `exit abc` → Error, exits with 2
- `exit 1 2` → Error "too many arguments", returns 1 (doesn't exit)

---

## REDIRECTIONS

### **4 Types**
1. **Input redirection** (`<`): Read from file
2. **Output redirection** (`>`): Write to file (truncate)
3. **Append redirection** (`>>`): Write to file (append)
4. **Heredoc** (`<<`): Read from user input until delimiter

### **General Pattern**
```c
1. Save current file descriptor: saved_fd = dup(STDIN/STDOUT)
2. Open file
3. Redirect: dup2(file_fd, STDIN/STDOUT)
4. Close file_fd
5. Execute command (reads/writes from/to redirected fd)
6. Restore: dup2(saved_fd, STDIN/STDOUT)
7. Close saved_fd
```

### **Input Redirection (`<`)** [redirections.c:79]
```c
int handle_redirection_input(t_tree_node *ast, t_data *data)
{
    saved_fd = dup(STDIN_FILENO);           // Save stdin

    infile = open(ast->filename, O_RDONLY); // Open file
    if (infile == -1)
        return perror("open"), -1;

    dup2(infile, STDIN_FILENO);             // Redirect stdin to file
    close(infile);

    execute_ast(ast->left, data);           // Execute command

    dup2(saved_fd, STDIN_FILENO);           // Restore stdin
    close(saved_fd);
    return 0;
}
```

**Example**: `cat < file.txt`
- `cat` reads from stdin
- stdin is redirected to file.txt
- `cat` effectively reads file.txt

### **Output Redirection (`>`)** [redirections.c:15]
```c
int handle_output_redirection(t_tree_node *ast, t_data *data)
{
    saved_fd = dup(STDOUT_FILENO);

    // O_CREAT: Create if doesn't exist
    // O_TRUNC: Clear file if exists
    // 0666: rw-rw-rw- permissions
    outfile = open(ast->filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (outfile == -1)
        return perror("open"), -1;

    dup2(outfile, STDOUT_FILENO);
    close(outfile);

    execute_ast(ast->left, data);

    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
    return 0;
}
```

**Example**: `echo hello > file.txt`
- `echo` writes to stdout
- stdout redirected to file.txt
- file.txt is created/truncated
- "hello\n" written to file.txt

### **Append Redirection (`>>`)** [redirections.c:65]
```c
// Same as >, but uses O_APPEND instead of O_TRUNC
outfile = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
```

**Example**: `echo hello >> file.txt`
- Appends "hello\n" to end of file.txt

### **Multiple Redirections**
```bash
cat < in.txt > out.txt
```

**AST**:
```
redir_node (<in.txt)
  └─ left: redir_node (>out.txt)
       └─ left: cmd_node(["cat"])
```

**Execution order** (innermost first):
1. Redirect stdout to out.txt
2. Redirect stdin to in.txt
3. Execute cat
4. Restore stdin
5. Restore stdout

### **Variable Expansion in Filenames**
```bash
export FILE=output.txt
echo hello > $FILE
```
- Filename expanded before opening: `$FILE` → `output.txt`

---

## HEREDOC IMPLEMENTATION

### **Overview**
Heredoc (`<<`) reads multi-line input from user until delimiter is reached.

**Example**:
```bash
cat <<EOF
line1
line2
EOF
```

### **Architecture**

```
Parent Process (Shell)
    │
    ├─ fork()
    │
    ├─ Child: Read lines, write to temp file
    │   ├─ readline("heredoc> ")
    │   ├─ Check delimiter
    │   ├─ Expand variables (if not quoted)
    │   └─ exit(0)
    │
    ├─ waitpid() - wait for child
    │
    ├─ open(temp_file, O_RDONLY)
    ├─ unlink(temp_file) - delete name, fd still valid
    └─ return fd
```

### **Key Functions**

#### **here_doc()** [heredoc.c:78]
```c
int here_doc(char *delimiter, t_data *data, int expand_flag)
{
    temp_file = "/tmp/heredoc_tmp";

    signal(SIGINT, SIG_IGN);  // Parent ignores Ctrl+C

    pid = fork();
    if (pid == 0)
        heredoc_child_process(...);  // Child collects input

    waitpid(pid, &status, 0);

    // Check if interrupted
    if (check_heredoc_status(status, data) == -1)
        return -1;  // Ctrl+C pressed

    fd_read = open(temp_file, O_RDONLY);
    unlink(temp_file);  // Delete name, fd still valid

    return fd_read;
}
```

#### **heredoc_child_process()** [heredoc.c:57]
```c
void heredoc_child_process(char *delimiter, t_data *data,
                           int expand_flag, char *temp_file)
{
    signal(SIGINT, SIG_DFL);  // Child can be interrupted

    setup_stdin_for_heredoc(&saved_stdin);  // Handle redirected stdin

    fd_write = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);

    read_heredoc_lines(delimiter, data, expand_flag, fd_write);

    if (saved_stdin != -1)
        dup2(saved_stdin, STDIN_FILENO);  // Restore stdin

    close(fd_write);
    exit(0);
}
```

#### **read_heredoc_lines()** [heredoc.c:15]
```c
int read_heredoc_lines(char *delimiter, t_data *data,
                       int expand_flag, int fd_write)
{
    while (1)
    {
        temp_line = readline("heredoc> ");
        if (!temp_line)  // Ctrl+D (EOF)
            break;

        line = my_strdup(temp_line);
        free(temp_line);

        if (strcmp(line, delimiter) == 0)  // Delimiter reached
            break;

        if (expand_flag)
            line = expand_variable(line, data);  // Expand $VAR

        write(fd_write, line, strlen(line));
        write(fd_write, "\n", 1);
    }
    return 0;
}
```

### **Signal Handling in Heredoc**

**Ctrl+C during heredoc**:
1. Child receives SIGINT (has SIG_DFL)
2. Child terminates
3. Parent wakes from waitpid()
4. `check_heredoc_status()` detects signal
5. Returns -1, command doesn't execute
6. Exit code set to 130

```c
int check_heredoc_status(int status, t_data *data)
{
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        data->exit_code = 130;
        write(1, "\n", 1);
        return -1;
    }
    return 0;
}
```

### **Expansion in Heredoc**

**Unquoted delimiter** (`<<EOF`): Expand variables
```bash
cat <<EOF
Hello $USER
EOF
# Output: Hello msafa
```

**Quoted delimiter** (`<<'EOF'` or `<<"EOF"`): No expansion
```bash
cat <<'EOF'
Hello $USER
EOF
# Output: Hello $USER
```

**Determined by** [create.c:114]:
```c
node->expansion[0] = (redir_pos + 1)->expand_flag;
```

### **Stdin Redirection in Heredoc** [heredoc.c:39]

**Problem**: If shell's stdin is redirected (pipe/file), `readline()` can't read from terminal.

**Solution**:
```c
if (!isatty(STDIN_FILENO))  // stdin is not terminal
{
    tty_fd = open("/dev/tty", O_RDONLY);  // Open terminal directly
    saved_stdin = dup(STDIN_FILENO);
    dup2(tty_fd, STDIN_FILENO);  // Replace stdin with terminal
    close(tty_fd);
}
```

**Example**: `echo "exit" | ./minishell`
- Shell's stdin is pipe
- Heredoc needs terminal input
- Open `/dev/tty` and redirect stdin temporarily

### **Unlink After Open**

```c
fd_read = open(temp_file, O_RDONLY);
unlink(temp_file);  // WHY?
return fd_read;
```

**Why unlink?**
1. **File descriptor remains valid**: Unix keeps file data while fd is open
2. **Automatic cleanup**: When fd is closed, kernel deletes file
3. **No leftover files**: Even if shell crashes
4. **Security**: File invisible to other processes
5. **Standard practice**: Bash does this

### **Heredoc Pre-collection** [pipe_exec.c:39]

**Problem**: In pipes, heredoc shouldn't prompt in child process.

**Example**:
```bash
cat <<EOF | grep hello
line1
line2
EOF
```

**Solution**: Before forking for pipe, collect all heredocs:
```c
int collect_heredocs(t_tree_node *node, t_data *data)
{
    if (node->type == redir_node && node->redir_type == t_re_heredoc)
    {
        expand_flag = node->expansion[0];
        node->heredoc_fd = here_doc(node->filename, data, expand_flag);
        return (node->heredoc_fd == -1) ? -1 : 0;
    }

    // Recursively collect in subtrees
    if (node->type == pipe_node)
    {
        collect_heredocs(node->left, data);
        collect_heredocs(node->right, data);
    }

    return 0;
}
```

**Process**:
1. Before executing pipe, traverse AST
2. Find all heredoc nodes
3. Execute heredocs, store fd in `heredoc_fd`
4. During execution, use cached fd instead of re-prompting

---

## PIPES

### **How Pipes Work**

**Concept**: Output of left command becomes input of right command.

```bash
ls | grep txt
```

**Diagram**:
```
Parent:
    ├─ pipe() creates pipefd[2]
    │    pipefd[0] = read end
    │    pipefd[1] = write end
    │
    ├─ fork() → child1
    │    ├─ dup2(pipefd[1], STDOUT) - stdout → pipe write
    │    ├─ close(pipefd[0])
    │    ├─ execute "ls"
    │    └─ exit
    │
    ├─ fork() → child2
    │    ├─ dup2(pipefd[0], STDIN) - stdin ← pipe read
    │    ├─ close(pipefd[1])
    │    ├─ execute "grep txt"
    │    └─ exit
    │
    ├─ close(pipefd[0])
    ├─ close(pipefd[1])
    ├─ waitpid(child1)
    └─ waitpid(child2)
```

### **Implementation** [pipe_exec.c:52]

```c
void execute_pipe(t_tree_node *ast, t_data *data)
{
    int pipefd[2];

    // 1. Create pipe
    if (pipe(pipefd) < 0)
        return perror("pipe failed");

    // 2. Fork child1 (left command)
    pid1 = fork();
    if (pid1 == 0)
        child1(ast->left, pipefd, data);

    // 3. Fork child2 (right command)
    pid2 = fork();
    if (pid2 == 0)
        child2(ast->right, pipefd, data);

    // 4. Parent closes pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // 5. Ignore signals while waiting
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    // 6. Wait for both children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);

    // 7. Set exit code from last command (right side)
    set_exit_code_from_status(data, status);
}
```

### **Child Processes**

#### **Child1 (Left)** [pipe_exec.c:15]
```c
int child1(t_tree_node *cmd_node, int *pipefd, t_data *data)
{
    dup2(pipefd[1], STDOUT_FILENO);  // stdout → pipe write end
    close(pipefd[0]);                 // Close read end (not needed)

    execute_ast(cmd_node, data);      // Execute left command

    exit(data->exit_code);
}
```

#### **Child2 (Right)** [pipe_exec.c:27]
```c
int child2(t_tree_node *cmd_node, int *pipefd, t_data *data)
{
    dup2(pipefd[0], STDIN_FILENO);   // stdin ← pipe read end
    close(pipefd[1]);                 // Close write end (not needed)

    execute_ast(cmd_node, data);      // Execute right command

    exit(data->exit_code);
}
```

### **Multiple Pipes**

```bash
cat file | grep hello | wc -l
```

**AST**:
```
pipe_node
  ├─ left: pipe_node
  │         ├─ left: cmd(cat)
  │         └─ right: cmd(grep)
  └─ right: cmd(wc)
```

**Execution**: Recursive
1. Execute outer pipe
   - Left: Another pipe (cat | grep)
   - Right: wc
2. Execute inner pipe (cat | grep)
3. Result: Three processes, two pipes

### **Exit Code**

**Exit code from rightmost command**:
```bash
false | true   # Exit code: 0 (from true)
true | false   # Exit code: 1 (from false)
```

Implementation:
```c
waitpid(pid1, NULL, 0);      // Discard left exit code
waitpid(pid2, &status, 0);   // Save right exit code
set_exit_code_from_status(data, status);
```

---

## SIGNAL HANDLING

### **Three Signals**
1. **SIGINT** (Ctrl+C): Interrupt
2. **SIGQUIT** (Ctrl+\\): Quit with core dump
3. **EOF** (Ctrl+D): End of file (not a signal, handled by readline)

### **Signal Behavior**

#### **Interactive Prompt**
```c
// [data_init.c:42]
void init_sigaction(struct sigaction *sa)
{
    sa->sa_handler = handle_signals;
    sigaction(SIGINT, sa, NULL);   // Handle Ctrl+C

    sa->sa_handler = SIG_IGN;
    sigaction(SIGQUIT, sa, NULL);  // Ignore Ctrl+\
}
```

**Ctrl+C**: Print newline, redisplay prompt, set exit code 130
```c
void handle_signals(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = 130;           // Global variable
        printf("\n");
        rl_on_new_line();         // Readline: move to new line
        rl_replace_line("", 0);   // Clear input
        rl_redisplay();           // Redisplay prompt
    }
}
```

**Ctrl+\\**: Ignored (no action)

**Ctrl+D**: Exits shell
```c
// [read_line.c:15]
input = readline("minishell$ ");
if (!input)  // readline returns NULL on EOF
    break;   // Exit loop, shell terminates
```

#### **During Command Execution**
```c
// [cmd_fork.c:27]
// Parent ignores signals
signal(SIGINT, SIG_IGN);
signal(SIGQUIT, SIG_IGN);
waitpid(pid, &status, 0);

// Child has default signal behavior
signal(SIGINT, SIG_DFL);
signal(SIGQUIT, SIG_DFL);
```

**Ctrl+C**: Kills child, parent continues
**Ctrl+\\**: Kills child with core dump message

#### **During Heredoc**
- **Parent**: Ignores SIGINT (`SIG_IGN`)
- **Child**: Default SIGINT (`SIG_DFL`)
- **Ctrl+C**: Kills child, heredoc aborted, exit code 130

#### **During Pipe**
- **Parent**: Ignores SIGINT and SIGQUIT during waitpid
- **Children**: Have default signal handlers
- **Ctrl+C**: Kills both children, parent continues

### **Global Variable g_signal** [gv.h:18]

```c
extern int g_signal;
```

**Purpose**: Communicate signal from handler to main loop

**Usage**:
```c
// [main.c:64]
if (g_signal != 0)
{
    data.exit_code = g_signal;  // Set exit code
    g_signal = 0;                // Reset
}
```

**Why global?** Signal handlers can't access local variables safely.

### **Signal Restoration**

After command execution:
```c
init_sigaction(&sa);  // Restore interactive signal handlers
```

---

## ENVIRONMENT VARIABLES

### **Initialization** [init_envp.c]

```c
int init_env(t_env *env, char **envp, t_list_head *head)
{
    // 1. Count environment variables
    env->count = array_len(envp);

    // 2. Copy envp
    init_envp_array(env, envp, head);

    // 3. Initialize export_only to NULL
    env->export_only = NULL;

    // 4. Copy envp to export_only
    init_export_array(env, head);

    // 5. Handle SHLVL (increment shell level)
    handle_shlvl_init(env, head);

    return 1;
}
```

### **SHLVL Handling**

**SHLVL**: Shell level (nesting depth)

```bash
echo $SHLVL   # 1
bash          # Start nested shell
echo $SHLVL   # 2
```

**Implementation**:
1. Find SHLVL in environment
2. Extract value, increment by 1
3. Update both `envp` and `export_only`

### **Two Arrays**

#### **1. env->envp** (Exported variables)
- Used by `env` command
- Passed to child processes via `execve()`
- Contains all exported variables

#### **2. env->export_only** (All variables)
- Used by `export` command
- Contains exported + non-exported variables
- Variables declared but not set: `export VAR` (no value)

**Example**:
```bash
export VAR1=value1
export VAR2
```

**env->envp**: `["VAR1=value1", ...]`
**env->export_only**: `["VAR1=value1", "VAR2", ...]`

### **Variable Operations**

#### **Finding Variable** [export.utils.c]
```c
int find_env_var(char *var_name, char **env)
{
    // Extract name before '=' or '+='
    // Search in env array
    // Return index or -1
}
```

#### **Adding Variable**
```c
export VAR=value
```
1. Validate identifier: `[a-zA-Z_][a-zA-Z0-9_]*`
2. Check if exists
3. If exists: update value
4. If not: expand array, add variable

#### **Appending to Variable**
```c
export PATH+=/new/path
```
1. Find variable
2. Get current value
3. Concatenate: `old_value + new_value`
4. Update variable

#### **Removing Variable**
```c
unset VAR
```
1. Find variable in `envp`
2. Shift array, remove variable
3. Find variable in `export_only`
4. Shift array, remove variable

---

## EXIT CODES

### **Setting Exit Code** [exit_code.c:15]

```c
void set_exit_code_from_status(t_data *data, int status)
{
    if (WIFEXITED(status))  // Normal exit
        data->exit_code = WEXITSTATUS(status);

    else if (WIFSIGNALED(status))  // Killed by signal
    {
        if (WTERMSIG(status) == SIGINT)
            printf("\n");
        else if (WTERMSIG(status) == SIGQUIT)
            printf("Quit (core dumped)\n");

        data->exit_code = 128 + WTERMSIG(status);
    }
}
```

### **Exit Code Values**

| Exit Code | Meaning |
|-----------|---------|
| 0 | Success |
| 1 | General error |
| 2 | Misuse of shell builtin (exit) |
| 126 | Command cannot execute (permission denied) |
| 127 | Command not found |
| 128+n | Killed by signal n |
| 130 | Ctrl+C (SIGINT, n=2) |
| 131 | Ctrl+\\ (SIGQUIT, n=3) |

### **Accessing Exit Code**

```bash
false
echo $?   # 1

true
echo $?   # 0

cat nonexistent
echo $?   # 1

./nonexistent
echo $?   # 127

cat /root/secret  # Permission denied
echo $?   # 126
```

### **Exit Code in Pipes**

**Exit code from rightmost command**:
```bash
false | true
echo $?   # 0

true | false
echo $?   # 1
```

---

## IMPORTANT EVALUATION QUESTIONS

### **Q1: Explain the complete flow from user input to command execution.**

**Answer**:
1. **Prompt**: `readline("minishell$ ")` gets user input
2. **Tokenization**: `tokenize_input()` splits input into tokens
   - Handle quotes, operators, expansion flags
3. **Parsing**: `parse_tokens()` builds AST
   - Recursive descent parser
   - Syntax validation
4. **Heredoc Collection**: `collect_heredocs()` pre-executes heredocs for pipes
5. **Execution**: `execute_ast()` recursively executes AST
   - Commands, pipes, redirections
6. **Cleanup**: `free_all()` frees all temporary allocations
7. **Loop**: Back to prompt

---

### **Q2: How does the garbage collector work?**

**Answer**:
- **ft_malloc()**: Wraps `malloc()`, adds pointer to linked list
- **free_all()**: Traverses linked list, frees all allocations
- **Two allocators**:
  - `n_head`: Temporary (freed after each command)
  - `env_head`: Persistent (freed at exit)
- **Benefits**: No memory leaks, automatic cleanup

---

### **Q3: How do you handle quotes?**

**Answer**:
- **During tokenization**: Quotes affect splitting and expansion
  - Single quotes: No expansion, literal
  - Double quotes: Expansion enabled
  - Quotes are removed
- **expand_flag**: Each token stores whether to expand variables
  - Set during tokenization based on quote type
- **Escaped characters**: `\$` → `$` (backslash removed)

---

### **Q4: How does variable expansion work?**

**Answer**:
- **Recursive algorithm**:
  1. Find first `$`, extract prefix
  2. Get variable name (alphanumeric + underscore)
  3. Recursively expand rest of string
  4. Look up variable in environment
  5. Special case: `$?` → exit code
  6. Concatenate: `prefix + value + suffix`
- **Escaped dollars**: `\$` treated as literal `$`

---

### **Q5: Why do you fork for external commands but not built-ins?**

**Answer**:
- **Built-ins**: Modify shell state (cd, export, exit)
  - If forked, changes would be in child, not parent
  - Example: `cd /tmp` in child doesn't affect shell's directory
- **External commands**: Separate programs
  - Run in child process for isolation
  - Child termination doesn't affect shell

---

### **Q6: Explain heredoc implementation in detail.**

**Answer**:
1. **Fork child process**:
   - Parent ignores SIGINT (waits without interruption)
   - Child has default SIGINT (can be killed by Ctrl+C)
2. **Child collects input**:
   - `readline("heredoc> ")` until delimiter
   - Expand variables if delimiter unquoted
   - Write to temporary file `/tmp/heredoc_tmp`
   - Exit
3. **Parent continues**:
   - Check if child was interrupted (Ctrl+C)
   - Open temp file for reading
   - **Unlink temp file** (deletes name, fd still valid)
   - Return fd
4. **Execution**:
   - Redirect stdin to heredoc fd
   - Execute command
   - Restore stdin

**Why unlink?** Automatic cleanup when fd is closed.

---

### **Q7: What happens when user presses Ctrl+C?**

**Answer**:

**At prompt**:
- Signal handler called: `handle_signals(SIGINT)`
- Set `g_signal = 130`
- Print newline
- Clear readline buffer
- Redisplay prompt

**During command**:
- Parent ignores SIGINT
- Child receives SIGINT, terminates
- Parent wakes, gets child status
- Exit code set to 130 (128 + 2)

**During heredoc**:
- Child receives SIGINT, terminates
- Parent detects signal, aborts heredoc
- Command doesn't execute
- Exit code 130

---

### **Q8: How do pipes work?**

**Answer**:
1. **Create pipe**: `pipe(pipefd)` creates read/write ends
2. **Fork child1** (left command):
   - Redirect stdout to pipe write end: `dup2(pipefd[1], STDOUT)`
   - Close read end
   - Execute left command
3. **Fork child2** (right command):
   - Redirect stdin to pipe read end: `dup2(pipefd[0], STDIN)`
   - Close write end
   - Execute right command
4. **Parent**:
   - Close both pipe ends
   - Wait for both children
   - Exit code from right command

---

### **Q9: How do you handle multiple redirections?**

**Answer**:
- **AST structure**: Nested redirection nodes
  - Example: `cat < in > out`
  - AST: `redir(<) → redir(>) → cmd(cat)`
- **Execution order**: Innermost first
  1. Redirect stdout to out
  2. Redirect stdin to in
  3. Execute cat
  4. Restore stdin
  5. Restore stdout

---

### **Q10: Explain the parsing algorithm.**

**Answer**:
- **Recursive descent parser**:
  1. **Find pipe** (highest precedence): Split, recurse on left/right
  2. **Find redirection**: Create redir_node, recurse
  3. **Base case**: No operators → create cmd_node
- **Syntax validation**:
  - Pipe at start/end: Error
  - Redirection without file: Error

---

### **Q11: How do you handle export with and without values?**

**Answer**:
- **Two arrays**:
  - `envp`: Exported variables (passed to children)
  - `export_only`: All variables (including non-exported)
- **export VAR=value**: Add to both arrays
- **export VAR**: Add to `export_only` only
- **export** (no args): Print sorted `export_only`

---

### **Q12: What is the difference between envp and export_only?**

**Answer**:
- **envp**: Variables visible to child processes
  - Used by `env` command
  - Passed to `execve()`
- **export_only**: All declared variables
  - Used by `export` command
  - Includes variables without values

---

### **Q13: How do you handle exit codes?**

**Answer**:
- **Normal exit**: `WIFEXITED(status)` → `WEXITSTATUS(status)`
- **Signal termination**: `WIFSIGNALED(status)` → `128 + WTERMSIG(status)`
- **Storage**: `data->exit_code`
- **Expansion**: `$?` → `data->exit_code`
- **Pipes**: Exit code from rightmost command

---

### **Q14: Why do you use AST instead of executing directly?**

**Answer**:
- **Structure**: AST represents command structure clearly
- **Precedence**: Handles operator precedence (pipe > redirection)
- **Recursion**: Easy recursive execution
- **Flexibility**: Easy to add new features
- **Clarity**: Separates parsing from execution

---

### **Q15: How do you handle signals during waitpid?**

**Answer**:
- **Before waitpid**: `signal(SIGINT, SIG_IGN)` - ignore Ctrl+C
- **Reason**: Prevent parent from terminating while waiting
- **Child**: Has default signal handlers, can be interrupted
- **After waitpid**: `init_sigaction()` - restore handlers

---

### **Q16: What happens if heredoc delimiter is quoted?**

**Answer**:
- **Quoted delimiter** (`<<'EOF'` or `<<"EOF"`):
  - `expand_flag = 0`
  - No variable expansion in heredoc input
  - `$USER` remains literal `$USER`
- **Unquoted delimiter** (`<<EOF`):
  - `expand_flag = 1`
  - Variables expanded
  - `$USER` → `msafa`

---

### **Q17: How do you prevent prompting heredoc in pipe child?**

**Answer**:
- **Pre-collection**: Before forking for pipe, traverse AST
- **collect_heredocs()**: Find all heredoc nodes, execute them
- **Store fd**: Save fd in `heredoc_fd` field of AST node
- **During execution**: Use cached fd instead of re-prompting

---

### **Q18: How do you handle stdin redirection in heredoc?**

**Answer**:
**Problem**: If shell's stdin is redirected (pipe), `readline()` can't read from keyboard.

**Solution**:
- Check `isatty(STDIN_FILENO)`
- If not a terminal:
  - Open `/dev/tty` (terminal device)
  - Redirect stdin to `/dev/tty`
  - Read heredoc input
  - Restore original stdin

---

### **Q19: What system calls do you use for pipes?**

**Answer**:
- `pipe()`: Create pipe
- `fork()`: Create child processes
- `dup2()`: Redirect file descriptors
- `close()`: Close unused pipe ends
- `waitpid()`: Wait for children
- `execve()`: Execute commands

---

### **Q20: How do you handle command not found?**

**Answer**:
1. **Search PATH**: `get_cmd_path()` searches directories in PATH
2. **Absolute/relative path**: If command contains `/`, use as-is
3. **Not found**: Print error, exit with 127
4. **Validation**: Check if executable, not directory
5. **Permission denied**: Exit with 126

---

### **Q21: Explain the difference between cd and other built-ins.**

**Answer**:
All built-ins run in parent process, but:
- **cd**: Changes current directory using `chdir()`
  - Must run in parent to affect shell's directory
- **export/unset**: Modify environment
  - Must run in parent to affect shell's environment
- **exit**: Terminates shell
  - Must run in parent to exit shell itself
- **echo/pwd**: Don't modify state, but still run in parent for consistency

---

### **Q22: What happens with too many arguments to exit?**

**Answer**:
```c
ft_exit(["arg1", "arg2"], data)
```
- Prints error: "minishell: exit: too many arguments"
- Returns 1 (doesn't exit!)
- Shell continues running

---

### **Q23: How do you handle env with arguments?**

**Answer**:
- Our implementation: Print error, not supported
- Bash: `env` can set environment variables and run commands
- We only support: `env` (print environment)

---

### **Q24: Explain memory management in tokenization.**

**Answer**:
1. **Tokenization**: Allocate strings with `ft_malloc(n_head)`
2. **Token array**: Allocate with `ft_malloc(n_head)`
3. **Parsing**: Create AST nodes with `ft_malloc(n_head)`
4. **Execution**: Use allocated structures
5. **Cleanup**: `free_all(n_head)` frees everything at once
6. **Next command**: Reset `n_head->head = NULL`, start fresh

---

### **Q25: What happens if pipe() or fork() fails?**

**Answer**:
- **pipe() fails**: Print error, return from execute_pipe()
- **fork() fails**: Print error, set exit code to 1
- Shell continues running (doesn't crash)

---

## TESTING SCENARIOS

### **Basic Commands**
```bash
echo hello world
/bin/ls -la
pwd
cd /tmp
cd
```

### **Redirections**
```bash
echo hello > file.txt
cat < file.txt
echo world >> file.txt
cat <<EOF
line1
line2
EOF
```

### **Pipes**
```bash
ls | grep txt
cat file | grep hello | wc -l
```

### **Variable Expansion**
```bash
echo $USER
echo $HOME
echo $?
export VAR=value
echo $VAR
```

### **Quotes**
```bash
echo 'hello $USER'      # No expansion
echo "hello $USER"      # Expansion
echo "hello \"world\""  # Escaped quotes
```

### **Signals**
```bash
cat   # Ctrl+C should interrupt
cat <<EOF   # Ctrl+C should abort heredoc
sleep 10    # Ctrl+C should kill command
```

### **Edge Cases**
```bash
""       # Empty command
echo ""  # Empty argument
exit 300 # Exit code modulo 256
cd too many args  # Error
export 123=value  # Invalid identifier
```

### **Complex**
```bash
export VAR=file; cat < $VAR | grep hello > output.txt
cat <<EOF | grep $USER
hello $USER
world
EOF
```

---

## KEY TAKEAWAYS FOR EVALUATION

1. **Memory**: Custom garbage collector, two allocators (temp/persistent)
2. **Parsing**: Recursive descent, builds AST
3. **Execution**: Recursive AST traversal
4. **Fork**: External commands fork, built-ins don't
5. **Signals**: Different handling in prompt/command/heredoc
6. **Pipes**: Two forks, pipe() for IPC
7. **Redirections**: Save fd, redirect, execute, restore
8. **Heredoc**: Fork child, write temp file, unlink after open
9. **Expansion**: Recursive, handles $VAR and $?
10. **Environment**: Two arrays (envp, export_only)

---

**GOOD LUCK WITH YOUR EVALUATION!**
