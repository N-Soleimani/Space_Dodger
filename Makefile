# Compiler
CXX = g++

# Paths
SFML_INC = C:/Users/AS/Documents/libraries/SFML-2.6.1/include
SFML_LIB = C:/Users/AS/Documents/libraries/SFML-2.6.1/lib

# Flags
CXXFLAGS = -std=c++17 -I"$(SFML_INC)"
LDFLAGS = -L"$(SFML_LIB)" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Files
OBJ = main.o
TARGET = main.exe

# Default target
all: $(TARGET)

# Compile
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Link
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Clean
clean:
	del /Q *.o *.exe

