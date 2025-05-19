CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRC = src/Game.cpp src/Map.cpp src/Tile.cpp src/Character.cpp src/Player.cpp src/Enemy.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
