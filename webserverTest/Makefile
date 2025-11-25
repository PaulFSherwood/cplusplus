UNAME_S := $(shell uname -s)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I./external
LIBS =-lpaho-mqttpp3 -lpaho-mqtt3as
ASAN ?= 0

# --- Platform specific flags ---
ifeq ($(UNAME_S),Linux)		# Linux
	CXXFLAGS += $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
	LIBS += $(shell pkg-config --libs -lpaho-mqttpp3 -lpaho-mqtt3as) 
endif

ifeq ($(UNAME_S),Darwin) 	# macOS
	CXXFLAGS += -I/opt/homebrew/include/SDL2
	LIBS += -lpaho-mqttpp3 -lpaho-mqtt3as
endif

ifeq ($(OS),Windows_NT)		# Windows (MinGW cross-compile or native MSYS2)
    CXX = x86_64-w64-mingw32-g++
    CXXFLAGS += -IC:/SDL2/include
    LIBS += -lpaho-mqttpp3 -lpaho-mqtt3as
endif

# AddressSanitizer toggle (kept separate from release/debug opts)
ifeq ($(ASAN),1)
  CXXFLAGS += -g -O1 -fno-omit-frame-pointer -fsanitize=address -D_GLIBCXX_ASSERTIONS
  LIBS += -fsanitize=address
endif

# UBSan option (pairs well with ASAN)
UBSAN ?= 0
ifeq ($(UBSAN),1)
  CXXFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined
  LIBS += -fsanitize=undefined
endif

# --- Project structure ---
SIM_SOURCE := $(wildcard sim/*.cpp)
CORE_SOURCE := $(wildcard core/*.cpp)
ECS_SOURCE := $(wildcard ecs/*.cpp)

SOURCES = $(SIM_SOURCE) $(CORE_SOURCE) $(ECS_SOURCE) main.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = webServer

all: release

release: CXXFLAGS += -O2
release: $(TARGET)

DEBUG_COMMON = -O0 -g3 -fno-omit-frame-pointer -DDEBUG -D_GLIBCXX_ASSERTIONS

debug: CXXFLAGS += $(DEBUG_COMMON)
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
	@echo "\033[1;32m✅ Build complete: $(TARGET) ✅\033[0m"
	rm -f $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

play: all
	./$(TARGET)

run-debug: debug
	ulimit -c unlimited; ./$(TARGET)

gdb: debug
	gdb ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✝ I have Exercised the demons, this house is clean."

.PHONY: all clean run play debug
