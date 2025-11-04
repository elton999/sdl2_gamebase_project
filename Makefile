CXX = g++
SRC = $(wildcard src/*.cpp)
OUT = build/game.exe
INCLUDE = -I lib
LIBS = -L bin -lglew32 -lmingw32 -lglu32 -lSDL2main -lSDL2 -lopengl32
CXXFLAGS_DEBUG = -g -Wall
CXXFLAGS_RELEASE = -O2 -mwindows

all: debug

debug:
	$(CXX) $(SRC) $(CXXFLAGS_DEBUG) $(INCLUDE) $(LIBS) -o $(OUT)

release:
	$(CXX) $(SRC) $(CXXFLAGS_RELEASE) $(INCLUDE) $(LIBS) -o $(OUT)