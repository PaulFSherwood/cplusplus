CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)

SOURCES = \
	ECS/EntityManager.cpp \
	AssetManager/AssetManager.cpp \
    Engine/Engine.cpp \
	main.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = entCompSys

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "\033[1;32m✅ Build complete: $(TARGET) ✅\033[0m"
	rm -f $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

play: all
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✝️ I have Exercised the demons, this house is clean."

debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -fsanitize=address
debug: clean all


.PHONY: all clean run

