# Norminette Violations Report

## Summary
- **Total Function Length Violations:** 20 functions (>25 lines)
- **Total Parameter Count Violations:** 7 functions (>4 parameters)
- **Total File Function Count Violations:** 0 files (all files have ≤5 functions)

---

## 1. FUNCTIONS LONGER THAN 25 LINES

### File: src/utils/Printing.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `print_ast` | 66-143 | 66 | Function too long (max 25) |

### File: src/Built-ins/heredoc.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `here_doc` | 15-76 | 49 | Function too long (max 25) |

### File: src/Built-ins/redirections.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `here_doc` | 15-76 | 49 | Function too long (max 25) |
| `handle_heredoc_redirection` | 78-111 | 27 | Function too long (max 25) |

### File: src/Built-ins/unset.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `ft_unset` | 15-53 | 35 | Function too long (max 25) |

### File: src/Built-ins/cd_utils.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `extract_quoted_path` | 59-85 | 26 | Function too long (max 25) |

### File: src/parsing/parser.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `print_tree` | 104-165 | 59 | Function too long (max 25) |
| `parse_tokens` | 167-194 | 26 | Function too long (max 25) |

### File: src/parsing/new_redirection_parser.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `new_handle_redirection_parsing` | 44-102 | 52 | Function too long (max 25) |

### File: src/split/split.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `extract_tokens` | 79-104 | 26 | Function too long (max 25) |

### File: src/split/extract_word.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `extract_complete_word` | 71-105 | 33 | Function too long (max 25) |

### File: src/Execution/expand.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `extract_prefix` | 15-43 | 28 | Function too long (max 25) |
| `expand_variable` | 90-114 | 26 | Function too long (max 25) |

### File: src/Execution/command_exec.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `exec_cmd` | 15-52 | 36 | Function too long (max 25) |
| `execute_builtin` | 54-83 | 29 | Function too long (max 25) |
| `execute_command` | 85-120 | 33 | Function too long (max 25) |
| `execute_ast` | 122-149 | 26 | Function too long (max 25) |

### File: src/main.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `while_prompt` | 17-56 | 36 | Function too long (max 25) |

### File: src/export/export_handle.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `handle_new_var` | 52-77 | 26 | Function too long (max 25) |

### File: src/utils/cpy_env_utils.c
| Function | Line Range | Lines | Issue |
|----------|------------|-------|-------|
| `handle_shlvl_init` | 66-87 | 26 | Function too long (max 25) |

---

## 2. FUNCTIONS WITH MORE THAN 4 PARAMETERS

| File | Function | Line | Parameters | Issue |
|------|----------|------|------------|-------|
| src/split/count.c | `handle_char` | 46 | 6 | Too many parameters (max 4) |
| src/split/count.c | `handle_quote_start` | 24 | 5 | Too many parameters (max 4) |
| src/split/split.c | `process_token` | 44 | 5 | Too many parameters (max 4) |
| src/parsing/create.c | `create_redir_node` | 89 | 5 | Too many parameters (max 4) |
| src/export/export_handle.c | `handle_existing_var` | 36 | 5 | Too many parameters (max 4) |
| src/utils/cpy_env_utils.c | `update_shlvl_entries` | 46 | 5 | Too many parameters (max 4) |
| src/parsing/new_redirection_parser.c | `new_handle_redirection_parsing` | 44 | 5 | Too many parameters (max 4) |

---

## 3. MOST CRITICAL VIOLATIONS (Priority Order)

1. **src/utils/Printing.c::print_ast** - 66 lines (41 lines over limit)
2. **src/parsing/parser.c::print_tree** - 59 lines (34 lines over limit)
3. **src/parsing/new_redirection_parser.c::new_handle_redirection_parsing** - 52 lines + 5 parameters (double violation)
4. **src/Built-ins/heredoc.c::here_doc** - 49 lines (24 lines over limit)
5. **src/Execution/command_exec.c** - 4 functions violating length requirements
6. **src/split/count.c::handle_char** - 6 parameters (2 over limit)

---

## 4. ADDITIONAL ISSUES

### Duplicate Symbol Errors
The build currently fails due to duplicate symbols between:
- `src/export/` directory
- `src/export_builtin/` directory

**Error:** 15 duplicate symbols causing linker failure.
**Action Required:** Remove one of these directories or merge them.

### Redirection Bug
**Issue:** `< file wc -l` not working correctly
**Status:** Fixed in src/parsing/new_redirection_parser.c (line 95-98)
**Root Cause:** Parser was using left_node (NULL) instead of right_node when left_node was empty

---

## 5. RECOMMENDED FIX STRATEGY

### Phase 1: Critical Fixes (Build-Breaking)
1. Resolve duplicate symbols (export vs export_builtin)
2. Test the redirection fix

### Phase 2: Function Length Violations (20 functions)
**Priority Order:**
1. Printing.c::print_ast (66 lines)
2. parser.c::print_tree (59 lines)
3. new_redirection_parser.c::new_handle_redirection_parsing (52 lines)
4. heredoc.c::here_doc (49 lines)
5. All remaining functions >30 lines
6. All remaining functions 26-29 lines

### Phase 3: Parameter Count Violations (7 functions)
**Priority Order:**
1. count.c::handle_char (6 params)
2. All functions with 5 parameters
   - Use structs to group related parameters
   - Pass data/context structs instead of individual params

### Phase 4: Testing
1. Run norminette on all fixed files
2. Test all functionality
3. Run full test suite

---

## 6. FILES REQUIRING ATTENTION

| File | Length Violations | Param Violations | Total Issues |
|------|-------------------|------------------|--------------|
| src/Execution/command_exec.c | 4 | 0 | 4 |
| src/parsing/new_redirection_parser.c | 1 | 1 | 2 |
| src/split/count.c | 0 | 2 | 2 |
| src/Built-ins/heredoc.c | 1 | 0 | 1 |
| src/Built-ins/redirections.c | 2 | 0 | 2 |
| src/Built-ins/unset.c | 1 | 0 | 1 |
| src/Built-ins/cd_utils.c | 1 | 0 | 1 |
| src/parsing/parser.c | 2 | 0 | 2 |
| src/split/split.c | 1 | 1 | 2 |
| src/split/extract_word.c | 1 | 0 | 1 |
| src/Execution/expand.c | 2 | 0 | 2 |
| src/main.c | 1 | 0 | 1 |
| src/export/export_handle.c | 1 | 1 | 2 |
| src/utils/cpy_env_utils.c | 1 | 1 | 2 |
| src/utils/Printing.c | 1 | 0 | 1 |
| src/parsing/create.c | 0 | 1 | 1 |

**Total Files Affected:** 16 files
**Total Violations:** 27 violations

---

*Generated: 2025-10-12*
