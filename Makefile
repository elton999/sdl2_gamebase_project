# ==============================
# 🔧 General configuration
# ==============================
CXX = g++
SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, build/obj/%.o, $(SRC))
OUT = build/game

CXXFLAGS_DEBUG = -g -Wall
CXXFLAGS_RELEASE = -O2 -mwindows

# ==============================
# 🧩 OS detection
# ==============================
ifeq ($(OS),Windows_NT)
    PLATFORM = windows
else
    PLATFORM = linux
endif

# ==============================
# 💻 Platform-specific setup
# ==============================
ifeq ($(PLATFORM),windows)
    OUT := $(OUT).exe
    INCLUDE = -I lib
    LIBS = -L bin -lmingw32 -lSDL2main -lSDL2 -lglew32 -lglu32 -lopengl32

    DLL_PATH = C:/msys64/ucrt64/bin
    DLLS = SDL2.dll glew32.dll libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll

    COPY_DLLS_CMD = \
        @echo "🔧 Copying required DLLs..."; \
        mkdir -p build; \
        for dll in $(DLLS); do \
            if [ -f "$(DLL_PATH)/$$dll" ]; then \
                cp "$(DLL_PATH)/$$dll" build/; \
                echo "✅ Copied: $$dll"; \
            else \
                echo "⚠️  Missing DLL: $$dll"; \
            fi; \
        done
else
    INCLUDE = $(shell pkg-config --cflags sdl2 glew)
    LIBS = $(shell pkg-config --libs sdl2 glew)
    COPY_DLLS_CMD = @true
endif

# ==============================
# 📁 Copy content folder
# ==============================
COPY_CONTENT_CMD = \
    @echo "📦 Copying content/ ..."; \
    if [ -d content ]; then \
        rm -rf build/content; \
        cp -r content build/; \
        echo "✅ content/ copied"; \
    else \
        echo "⚠️  No content/ folder to copy"; \
    fi

# ==============================
# 🧱 Main build rules
# ==============================
all: debug

debug: CXXFLAGS += $(CXXFLAGS_DEBUG)
debug: build_dirs $(OUT)
	$(COPY_DLLS_CMD)
	$(COPY_CONTENT_CMD)       # >>>

release: CXXFLAGS += $(CXXFLAGS_RELEASE)
release: build_dirs $(OUT)
	$(COPY_DLLS_CMD)
	$(COPY_CONTENT_CMD)       # >>>

# Link the final executable
$(OUT): $(OBJ)
	@echo "🚀 Linking..."
	$(CXX) $(OBJ) $(CXXFLAGS) $(INCLUDE) $(LIBS) -o $@

# Compile each .cpp into .o
build/obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Create build folders
build_dirs:
	@mkdir -p build/obj

# ==============================
# 🧹 Cleaning targets
# ==============================
clean:
	@echo "🧹 Cleaning build directory..."
	@if [ -d build ]; then rm -rf build/*; fi

rebuild: clean all