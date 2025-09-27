#!/bin/bash

# Comprehensive test script for minishell
# Tests pipes, multiple pipes, redirection out, heredoc, and quotes

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
PASS_COUNT=0
FAIL_COUNT=0
TEST_COUNT=0

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_output="$3"
    local check_type="${4:-output}" # output, file, or exit_code

    ((TEST_COUNT++))
    echo -e "${BLUE}Test $TEST_COUNT: $test_name${NC}"
    echo "Command: $command"

    # Clean up any existing test files
    rm -f test_output.txt test_file.txt input.txt

    case "$check_type" in
        "output")
            # Test standard output
            actual_output=$(echo "$command" | $MINISHELL 2>/dev/null | tail -n +2)
            expected_bash=$(echo "$command" | bash 2>/dev/null)
            if [[ "$actual_output" == "$expected_bash" ]]; then
                echo -e "${GREEN}✓ PASS${NC}"
                ((PASS_COUNT++))
            else
                echo -e "${RED}✗ FAIL${NC}"
                echo "Expected: '$expected_bash'"
                echo "Got: '$actual_output'"
                ((FAIL_COUNT++))
            fi
            ;;
        "file")
            # Test file output
            echo "$command" | $MINISHELL >/dev/null 2>&1
            if [[ -f "$expected_output" ]]; then
                echo -e "${GREEN}✓ PASS - File created${NC}"
                cat "$expected_output" 2>/dev/null || true
                ((PASS_COUNT++))
            else
                echo -e "${RED}✗ FAIL - File not created${NC}"
                ((FAIL_COUNT++))
            fi
            ;;
        "exit_code")
            echo "$command" | $MINISHELL >/dev/null 2>&1
            exit_code=$?
            if [[ $exit_code -eq $expected_output ]]; then
                echo -e "${GREEN}✓ PASS - Exit code $exit_code${NC}"
                ((PASS_COUNT++))
            else
                echo -e "${RED}✗ FAIL - Expected exit code $expected_output, got $exit_code${NC}"
                ((FAIL_COUNT++))
            fi
            ;;
    esac
    echo ""
}

# Function to create test files
setup_test_files() {
    echo -e "line1\nline2\nline3" > input.txt
    echo "test content" > test_file.txt
}

echo -e "${YELLOW}=== MINISHELL COMPREHENSIVE TEST SUITE ===${NC}"
echo ""

# Setup test environment
setup_test_files

echo -e "${YELLOW}=== SINGLE PIPE TESTS ===${NC}"

# Basic pipe tests
run_test "Basic pipe: echo to cat" "echo hello | cat"
run_test "Pipe with ls and wc" "ls | wc -l"
run_test "Pipe with echo and grep" "echo -e 'hello\nworld\nhello' | grep hello"
run_test "Pipe with cat and sort" "cat input.txt | sort"
run_test "Pipe with echo and head" "echo -e 'a\nb\nc\nd\ne' | head -3"
run_test "Pipe with echo and tail" "echo -e 'a\nb\nc\nd\ne' | tail -2"
run_test "Empty input pipe" "echo '' | cat"
run_test "Multiple words through pipe" "echo 'hello world test' | wc -w"

echo -e "${YELLOW}=== MULTIPLE PIPE TESTS ===${NC}"

# Multiple pipe tests
run_test "Three command pipe" "echo -e 'c\na\nb' | sort | head -1"
run_test "Four command pipe" "echo -e '1\n2\n3\n4\n5' | head -3 | tail -1 | cat"
run_test "Complex pipe chain" "echo 'hello world' | tr ' ' '\n' | sort | head -1"
run_test "Long pipe chain" "echo -e 'apple\nbanana\ncherry' | sort | head -2 | tail -1"
run_test "Pipe with numbers" "echo -e '5\n2\n8\n1' | sort -n | head -1"

echo -e "${YELLOW}=== OUTPUT REDIRECTION TESTS ===${NC}"

# Output redirection tests
run_test "Simple output redirect" "echo hello > test_output.txt" "test_output.txt" "file"
run_test "Overwrite existing file" "echo world > test_output.txt" "test_output.txt" "file"
run_test "Redirect with spaces" "echo 'hello world' > test_output.txt" "test_output.txt" "file"
run_test "Redirect empty output" "echo '' > test_output.txt" "test_output.txt" "file"
run_test "Redirect command output" "ls > test_output.txt" "test_output.txt" "file"

# Append redirection tests
run_test "Append to file" "echo first > test_output.txt && echo second >> test_output.txt" "test_output.txt" "file"
run_test "Multiple appends" "echo line1 > test_output.txt && echo line2 >> test_output.txt && echo line3 >> test_output.txt" "test_output.txt" "file"

echo -e "${YELLOW}=== HEREDOC TESTS ===${NC}"

# Heredoc tests (simplified since interactive testing is complex)
echo "Testing heredoc functionality..."
echo "cat << EOF
This is a heredoc test
Multiple lines
EOF" | $MINISHELL > heredoc_output.txt 2>/dev/null

if [[ -s heredoc_output.txt ]]; then
    echo -e "${GREEN}✓ Basic heredoc test passed${NC}"
    ((PASS_COUNT++))
else
    echo -e "${RED}✗ Basic heredoc test failed${NC}"
    ((FAIL_COUNT++))
fi
((TEST_COUNT++))

echo ""

echo -e "${YELLOW}=== QUOTES HANDLING TESTS ===${NC}"

# Single quotes tests
run_test "Single quotes basic" "echo 'hello world'"
run_test "Single quotes with spaces" "echo 'hello    world'"
run_test "Single quotes with special chars" "echo 'hello$USER'"
run_test "Single quotes empty" "echo ''"

# Double quotes tests
run_test "Double quotes basic" "echo \"hello world\""
run_test "Double quotes with spaces" "echo \"hello    world\""
run_test "Double quotes empty" "echo \"\""

# Mixed quotes tests
run_test "Mixed quotes 1" "echo 'hello' \"world\""
run_test "Mixed quotes 2" "echo \"hello 'world'\""

echo -e "${YELLOW}=== COMPLEX COMBINATION TESTS ===${NC}"

# Pipes with redirection
run_test "Pipe with output redirect" "echo hello | cat > test_output.txt" "test_output.txt" "file"
run_test "Multiple pipes with redirect" "echo -e 'c\na\nb' | sort | head -1 > test_output.txt" "test_output.txt" "file"

# Quotes with pipes
run_test "Quoted command in pipe" "echo 'hello world' | wc -w"
run_test "Pipe with quoted args" "echo hello | grep 'hello'"

# Quotes with redirection
run_test "Quoted filename redirect" "echo test > 'test_output.txt'" "test_output.txt" "file"
run_test "Quoted content redirect" "echo 'hello world' > test_output.txt" "test_output.txt" "file"

# Complex combinations
run_test "Pipes, quotes, and redirect" "echo 'hello world test' | wc -w > test_output.txt" "test_output.txt" "file"
run_test "Multiple pipes with quotes" "echo 'apple banana cherry' | tr ' ' '\n' | sort | head -1"

echo -e "${YELLOW}=== EDGE CASES ===${NC}"

# Edge cases
run_test "Empty command" ""
run_test "Only spaces" "   "
run_test "Pipe at end" "echo hello |" "" "exit_code"
run_test "Pipe at start" "| cat" "" "exit_code"
run_test "Multiple consecutive pipes" "echo hello || cat" "" "exit_code"
run_test "Redirect without filename" "echo hello >" "" "exit_code"
run_test "Invalid command" "nonexistentcommand" "" "exit_code"
run_test "Unclosed quotes" "echo 'hello" "" "exit_code"

# Cleanup
rm -f test_output.txt test_file.txt input.txt heredoc_output.txt

echo -e "${YELLOW}=== TEST SUMMARY ===${NC}"
echo -e "Total tests: $TEST_COUNT"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"

if [[ $FAIL_COUNT -eq 0 ]]; then
    echo -e "${GREEN}All tests passed! 🎉${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed. Check the output above.${NC}"
    exit 1
fi