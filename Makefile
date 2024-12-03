#
#
# The Quickfall makefile. Allows to build the Quickfall toolchain.
# 
#

ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    TARGET_EXTENSION := .exe
    RM := del /Q
    MKDIR := mkdir
    CP := copy
    PATHSEP := \\
else
    DETECTED_OS := $(shell uname -s)
    TARGET_EXTENSION :=
    RM := rm -rf
    MKDIR := mkdir -p
    CP := cp
    PATHSEP := /
endif

#
# Compiling configuration.
#

# Which compiler to use (must be equal to the command used to compile)
COMPILER = gcc

# Flags that are passed to the compiler
FLAGS = -Wall -Wextra -Wimplicit-function-declaration

#
# Path configuration.
#

# The directory containing the code of Quickfall.
SRC_DIR = src

# The directory containing the benchmarks of Quickfall.
BENCH_SRC_DIR = benchmarks

#
# Output definition
#

# The target of a normal mode compiling.
TARGET = quickfall$(TARGET_EXTENSION)

# The target of a bench mode compiling.
BENCH_TARGET = bench$(TARGET_EXTENSION)


#
# Building variables
#

# The sources that are going to be compiled in normal mode.
SOURCES = $(wildcard ${SRC_DIR}/**/*.c) $(wildcard ${SRC_DIR}/**/**/*.c)

BENCH_SOURCES = ${SOURCES} $(wildcard ${BENCH_SRC_DIR}/**/*.c)

#
# Building logic
#

all: prepare_build $(TARGET)
bench: prepare_build $(BENCH_TARGET)

prepare_build:
	@echo [INFO] Using "${COMPILER}" as a compiler!
	@echo [INFO] Detected current operating system as ${DETECTED_OS}
	$(CHECK_COMMANDS)
	@echo [INFO] Clearing old builds
	$(RM) build
	$(RM) $(TARGET)
	@echo [INFO] Starting building logic

$(TARGET):
	$(COMPILER) $(FLAGS) $(SOURCES) -o $(TARGET)

