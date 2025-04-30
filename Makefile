CXX := g++

SRC := $(wildcard src/*.cpp) main.cpp

TARGET := Practica

CXXFLAGS := -std=c++17 -Iinclude -DNOMINMAX

# Чекаю имя оболочки, т.е. оську
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) # Для Лины
	CXXFLAGS += $(shell pkg-config --cflags sdl2)
	LDFLAGS := $(shell pkg-config --libs sdl2)
else ifeq ($(UNAME_S), Darwin) # Для Макоси
	CXXFLAGS += -I/usr/local/include/SDL2
	LDFLAGS := -L/usr/local/lib -lSDL2
else # Для Винды
	CXXFLAGS += -I./SDL2/include
	LDFLAGS := -L./SDL2/library -lmingw32 -lSDL2main -lSDL2
	TARGET := practica.exe

# Статистически линкую две библиотеки, которых не хватало когда я компилил до этого
# Это вроде как специфика Винды
	LDFLAGS += -static-libgcc -static-libstdc++ -static -static-SDL2
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean