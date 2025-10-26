#!/bin/bash

echo "=== Additional Quote and Variable Expansion Tests ==="
echo ""

# Test 1: Empty quotes with variable
echo "Test 1: ""$A B \"CD\""
echo "Expected: 1 B CD"
echo -n "Minishell: "
echo -e 'export A="1"\necho ""$A B "CD"\nexit' | ./minishell 2>/dev/null | grep -v "minishell"
echo -n "Bash: "
bash -c 'export A="1"; echo ""$A B "CD"'
echo ""

# Test 2: Variable in single quotes (should not expand)
echo "Test 2: '\$A' (single quotes)"
echo "Expected: \$A"
echo -n "Minishell: "
echo -e "echo '\$A'\nexit" | ./minishell 2>/dev/null | grep -v "minishell"
echo -n "Bash: "
bash -c "echo '\$A'"
echo ""

# Test 3: Variable in double quotes (should expand)
echo "Test 3: \"\$A\" (double quotes)"
echo "Expected: 1"
echo -n "Minishell: "
echo -e 'export A="1"\necho "$A"\nexit' | ./minishell 2>/dev/null | grep -v "minishell"
echo -n "Bash: "
bash -c 'export A="1"; echo "$A"'
echo ""

# Test 4: Multiple empty quotes
echo "Test 4: \"\"\"\" (four empty quotes)"
echo "Expected: (empty line)"
echo -n "Minishell: "
echo -e 'echo """"""\nexit' | ./minishell 2>/dev/null | grep -v "minishell"
echo -n "Bash: "
bash -c 'echo """"""'
echo ""

# Test 5: Mixing single and double quotes
echo "Test 5: \"A\"'B'\"C\""
echo "Expected: ABC"
echo -n "Minishell: "
echo -e "echo \"A\"'B'\"C\"\nexit" | ./minishell 2>/dev/null | grep -v "minishell"
echo -n "Bash: "
bash -c "echo \"A\"'B'\"C\""
echo ""
