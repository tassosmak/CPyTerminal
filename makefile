# Compiler
CC = gcc -g

# Compiler flags 
CFLAGS = -Wall -Wextra -Iinclude

# Target executable
TARGET = pyterminal

# Source files 
SRCS = pyterminal.c src/flags.c src/utils.c src/commands.c src/JsonHandler.c src/cJSON.c src/FTU.c src/credentials.c src/Login.c



# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) src/*.o

# Rebuild
rebuild: clean all

.PHONY: all clean rebuild