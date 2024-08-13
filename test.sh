#!/bin/bash

# test.sh

# Set the inputs
INPUT1=6
INPUT2=6

# Deliberately set the expected result to an incorrect value
EXPECTED_RESULT=12  # This is intentionally incorrect for testing

# Run the program and provide input
echo -e "$INPUT1\n$INPUT2" | make run

# Read the generated result
RESULT=$(cat result.txt)

# Debug output to check what's actually in the result.txt file
echo "Generated result: $RESULT"
echo "Expected result: $EXPECTED_RESULT"

# Compare the result with the expected value
if [ "$RESULT" -eq "$EXPECTED_RESULT" ]; then
    echo "Test passed: $RESULT == $EXPECTED_RESULT"
    exit 0
else
    echo "Test failed: $RESULT != $EXPECTED_RESULT"
    exit 1
fi
