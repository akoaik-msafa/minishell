#!/bin/bash

# Test script for double heredoc issue
echo "Testing: cat > file <<eof <<eof"
echo ""
echo "Expected behavior: Read 2 heredocs, write second one to file"
echo ""

# Create test input
cat > /tmp/minishell_test_input <<'END'
cat > file <<eof <<eof
first heredoc line
eof
second heredoc line
eof
cat file
exit
END

# Run the test
./minishell < /tmp/minishell_test_input

# Cleanup
rm -f /tmp/minishell_test_input file
