# Expand Flag System Explanation

## Data Types

### 1. `char expand_flag` (in tokens)
- **Location**: `token_t` structure
- **Size**: 1 byte (char)
- **Values**: 0 or 1
- **Source**: Set during tokenization based on quoting rules
- **Purpose**: Stores whether a token should be expanded

### 2. `char *expand_flags` (in AST nodes)
- **Location**: `tree_node` structure
- **Size**: Array of chars (allocated dynamically)
- **Values**: Array where `[0]` contains the expand flag
- **Source**: Copied from token's `expand_flag`
- **Purpose**: Preserves expand information in AST

### 3. `int expand_flag` (function parameter)
- **Location**: Function parameters (like `here_doc`)
- **Size**: 4 bytes (int)
- **Values**: 0 or 1 (converted from char)
- **Source**: Extracted from AST node's `expand_flags[0]`
- **Purpose**: Passed to execution functions

## Flow Chart

```
Tokenization:
  Input: cat << "EOF"
  ↓
  Token parsing determines quotes
  ↓
  char expand_flag = 0 (quoted)
  ↓
  Stored in token_t.expand_flag

AST Building:
  Token with expand_flag
  ↓
  create_redir_node(..., token.expand_flag)
  ↓
  char *expand_flags = malloc(2)
  expand_flags[0] = token.expand_flag
  ↓
  Stored in tree_node.expand_flags

Execution:
  AST node with expand_flags
  ↓
  int expand_flag = ast->expand_flags[0]
  ↓
  here_doc(..., expand_flag)
  ↓
  Heredoc uses int expand_flag for decisions
```

## Key Differences

| Type | Storage | Purpose | Lifetime |
|------|---------|---------|----------|
| `char expand_flag` | Token | Parsing result | Until AST built |
| `char *expand_flags` | AST Node | Persistent storage | Until execution |
| `int expand_flag` | Parameter | Execution input | Function scope |

## Why Multiple Types?

1. **Tokens**: Use `char` for memory efficiency (many tokens)
2. **AST**: Use `char *` array for extensibility (could store multiple flags)
3. **Functions**: Use `int` for standard parameter passing and logic