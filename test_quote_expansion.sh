#!/bin/bash

# Test script for quote and variable expansion
# Expected behavior:
# Input: ""$A B "CD"
# After $A expansion: ""1 B "CD"
# After empty string removal: 1 B "CD"
# After splitting by spaces: 1 , B, "CD"
# After quote stripping: 1 , B, CD

echo "=== Testing Quote and Variable Expansion ==="
echo ""

echo "Setting up test environment:"
echo 'export A="1"'
echo 'echo ""$A B "CD"'
echo ""

echo "Expected output: 1 B CD"
echo "Actual output from minishell:"

# Run the test
echo -e 'export A="1"\necho ""$A B "CD"\nexit' | ./minishell

echo ""
echo "=== Comparison with bash ==="
echo "Output from bash:"
bash -c 'export A="1"; echo ""$A B "CD"'
