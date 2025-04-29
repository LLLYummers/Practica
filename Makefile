CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -DNOMINMAX -I./SDL2/inc
LDFLAGS := -L./SDL2/lib
LDLIBS := -lSDL2

SOURCES := $(wildcard src/*.cpp) main.cpp
TARGET := practica.exe

all: $(TARGET) copy_dll

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

copy_dll:
	cp SDL2/lib/SDL2.dll ./

clean:
	rm -f $(TARGET) *.exe *.dll

.PHONY: all clean copy_dll