# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror

# Target executable
TARGET = hello

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Run the target
run: $(TARGET)
	./$(TARGET)

# Test the output
test: run
	@EXPECTED=11; \
	RESULT=`cat result.txt`; \
	if [ "$$RESULT" -eq "$$EXPECTED" ]; then \
		echo "Test passed: $$RESULT == $$EXPECTED"; \
		exit 0; \
	else \
		echo "Test failed: $$RESULT != $$EXPECTED"; \
		exit 1; \
	fi

# Clean up
clean:
	rm -f $(TARGET) $(OBJS) result.txt
