# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++17 -Wall

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable names
TARGET1 = myprogram
TARGET2 = plotGraph
TARGET3 = invertedIndex
TARGET4 = foldTrees
TARGET5 = wordCounter

# Source files
SRC1 = src/prog.cpp funcionesCPP/funciones.cpp funcionesCPP/reader.cpp funcionesCPP/casos.cpp
SRC2 = src/plotGraph.cpp Dependencias/SFGraphing/src/SFPlot.cpp Dependencias/SFGraphing/src/PlotDataSet.cpp
SRC3 = src/invertedIndex.cpp  # Add more source files if needed
SRC4 = src/foldTrees.cpp
SRC5 = src/wordCounter.cpp

# Header files
HEADERS1 = funcionesH/funciones.h funcionesH/reader.h funcionesH/casos.h
HEADERS2 = Dependencias/SFGraphing/include/SFGraphing/SFPlot.h Dependencias/SFGraphing/include/SFGraphing/PlotDataSet.h
HEADERS3 =  # Add your header files if needed
HEADERS4 =  # Add your header files if needed
HEADERS5 =  # Add your header files if needed

# Include directories
INCLUDE_DIRS = -IDependencias # Adjust the path based on your project structure

.PHONY: all clean

# Default target
all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

$(TARGET1): $(SRC1) $(HEADERS1)
	$(CC) $(CFLAGS) $(SRC1) -o $(TARGET1)

$(TARGET2): $(SRC2) $(HEADERS2)
	$(CC) $(CFLAGS) $(SRC2) -o $(TARGET2) $(SFML_LIBS)

$(TARGET3): $(SRC3) $(HEADERS3)
	$(CC) $(CFLAGS) $(SRC3) -o $(TARGET3)

$(TARGET4): $(SRC4) $(HEADERS4)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SRC4) -o $(TARGET4)

$(TARGET5): $(SRC5) $(HEADERS5)
	$(CC) $(CFLAGS) $(SRC5) -o $(TARGET5)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)
