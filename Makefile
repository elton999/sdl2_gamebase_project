CXX = g++
OUT = build/game.exe
SRC = $(shell find src -name "*.cpp")
CXXFLAGS_DEBUG = -g -Wall
CXXFLAGS_RELEASE = -O2 -mwindows

ifeq ($(OS),Windows_NT)
    INCLUDE = -I lib
    LIBS = -L bin -lmingw32 -lSDL2main -lSDL2 -lglew32 -lglu32 -lopengl32
else
    INCLUDE = $(shell pkg-config --cflags sdl2 glew)
    LIBS = $(shell pkg-config --libs sdl2 glew)
    OUT = build/game
endif

all: debug

debug:
	$(CXX) $(SRC) $(CXXFLAGS_DEBUG) $(INCLUDE) $(LIBS) -o $(OUT)

release:
	$(CXX) $(SRC) $(CXXFLAGS_RELEASE) $(INCLUDE) $(LIBS) -o $(OUT)