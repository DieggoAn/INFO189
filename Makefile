# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++17 -Wall

# Target executable name
TARGET = myprogram

# Source files
SRC = prog.cpp funcionesCPP/funciones.cpp funcionesCPP/reader.cpp funcionesCPP/casos.cpp

# Header files
HEADERS = funcionesH/funciones.h funcionesH/reader.h funcionesH/casos.h

# Default target
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(SFML_LIBS)

clean:
	rm -f $(TARGET)
