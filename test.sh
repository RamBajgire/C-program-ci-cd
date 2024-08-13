#!/bin/bash

# test.sh

# Set the expected input and result
INPUT1=5
INPUT2=7
EXPECTED_RESULT=12

# Run the program and provide input
echo -e "$INPUT1\n$INPUT2" | make run

# Read the generated result
RESULT=$(cat result.txt)

# Compare the result with the expected value
if [ "$RESULT" -eq "$EXPECTED_RESULT" ]; then
    echo "Test passed: $RESULT == $EXPECTED_RESULT"
    exit 0
else
    echo "Test failed: $RESULT != $EXPECTED_RESULT"
    exit 1
fi
