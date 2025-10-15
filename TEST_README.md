# Minishell Test Suite

A comprehensive bash script to test your minishell implementation with 100 test cases.

## Features

This test suite includes 100 test cases covering:

1. **Echo Command (10 tests)** - Basic echo, flags, quotes, special characters
2. **PWD Command (5 tests)** - Basic pwd, with arguments, after cd operations
3. **CD Command (10 tests)** - Home, root, relative/absolute paths, error cases
4. **ENV Command (5 tests)** - Display environment variables
5. **Export Command (10 tests)** - Variable creation, modification, edge cases
6. **Unset Command (5 tests)** - Variable removal, error handling
7. **Exit Command (5 tests)** - Exit codes, argument validation
8. **Pipes (10 tests)** - Single and multiple pipes, with builtins and commands
9. **Output Redirections (10 tests)** - >, >>, multiple redirections
10. **Input Redirections (5 tests)** - <, error handling
11. **Heredoc (5 tests)** - <<, with variables, multiple lines
12. **Environment Variables (10 tests)** - Expansion, quotes, special variables
13. **Quotes (5 tests)** - Single, double, mixed, nested quotes
14. **Command Execution (5 tests)** - Absolute/relative paths, command not found
15. **Error Handling (5 tests)** - Syntax errors, permissions, invalid commands

## Usage

### Prerequisites

Make sure your minishell is compiled:

```bash
make
```

### Running the Tests

Execute the test script:

```bash
./test_minishell.sh
```

### Output

The script provides:
- Color-coded test results (green for pass, red for fail)
- Section-by-section organization
- Detailed summary at the end
- List of failed tests for debugging
- Success rate percentage

### Example Output

```
╔════════════════════════════════════════════════════════════════╗
║          MINISHELL COMPREHENSIVE TEST SUITE                    ║
╚════════════════════════════════════════════════════════════════╝

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  1. ECHO COMMAND TESTS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ✓ Test 1: echo simple text
  ✓ Test 2: echo with -n flag
  ...
```

## Test Categories Explained

### 1. Builtin Commands
Tests all required builtin commands: echo, cd, pwd, export, unset, env, exit

### 2. Redirections
Tests all redirection types:
- Output: `>` and `>>`
- Input: `<`
- Heredoc: `<<`

### 3. Pipes
Tests pipe functionality with single and multiple pipes

### 4. Environment Variables
Tests variable expansion in different contexts

### 5. Quote Handling
Tests single quotes (no expansion) and double quotes (with expansion)

### 6. Error Handling
Tests various error conditions and edge cases

## Customization

You can modify the test script to:
- Add more test cases
- Change the minishell executable path (default: `./minishell`)
- Modify the test directory (default: `./test_tmp`)
- Adjust color schemes

## Cleanup

The script automatically cleans up temporary files created during testing.

## Exit Codes

- `0`: All tests passed
- `1`: One or more tests failed

## Notes

- Some tests compare output with bash behavior
- Tests are designed to be non-destructive
- Temporary files are created in `./test_tmp` directory
- The script requires bash to run

## Troubleshooting

If tests fail:
1. Check if minishell executable exists
2. Verify you have necessary permissions
3. Review failed test details in the summary
4. Run individual commands manually for debugging

## Contributing

To add new tests:
1. Choose the appropriate section or create a new one
2. Use the `run_test` function for output comparison
3. Use `run_test_with_file` for file creation tests
4. Update the test counter and documentation

## License

This test suite is provided as-is for educational purposes.
