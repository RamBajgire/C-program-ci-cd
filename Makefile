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

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)

# Run the target
run: $(TARGET)
	./$(TARGET)
