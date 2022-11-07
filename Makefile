CC = g++
INC_DIR = Dependencies\SDL2\include
CPP_FILES := $(wildcard src/*.cpp src/*/*.cpp)
OBJ_FILES := $(patsubst src/%,lib/%,$(CPP_FILES:.cpp=.o))
LIBS:=-L Dependencies\SDL2\lib\x64 -lSDL2main -lSDL2 -lSDL2_image
TARGET:=bin/run
CC_FLAGS = -c -I$(INC_DIR)


$(TARGET): $(OBJ_FILES)
	mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LIBS)

lib/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -o $@ $<


clean:
	rm -f run.exe *.o

play:
	./bin/run