UNAME_S := $(shell uname -s)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
LDFLAGS =

# --- Platform specific flags ---
ifeq ($(UNAME_S),Linux)		# Linux
	CXXFLAGS += $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
	LDFLAGS  += $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)
endif

ifeq ($(UNAME_S),Darwin) 	# macOS
	CXXFLAGS += -I/opt/homebrew/include/SDL2
	LDFLAGS += -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_image
endif

ifeq ($(OS),Windows_NT)		# Windows (MinGW cross-compile or native MSYS2)
    CXX = x86_64-w64-mingw32-g++
    CXXFLAGS += -IC:/SDL2/include
    LDFLAGS  += -LC:/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
endif


# --- Project structure ---
SOURCES = \
		ECS/Core/Application.cpp \
    ECS/Core/Main.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = ecs-prototype

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
	@echo "✝ I have Exercised the demons, this house is clean."

debug: CXXFLAGS = -std=c++20 -Wall -Wextra -g -fsanitize=address
debug: clean all

.PHONY: all clean run play debug
