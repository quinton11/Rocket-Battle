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

#output: main.o vector2d.o timeSetting.o homescreen.o gamescreen.o entities.o controllers.o
#	$(CC) main.o Vector2d.o TimeSetting.o HomeScreen.o GameEntity.o GameManager.o GGraphics.o KeyBoardHandler.o Rocket.o Screen.o TextureManager.o -L Dependencies\SDL2\lib\x64 -lSDL2main -lSDL2 -lSDL2_image -o run

#controllers.o: src\Controllers\KeyBoardHandler.cpp
#	$(CC) -c src\Controllers\KeyBoardHandler.cpp $(IFLAG)


#entities.o: src\Entities\GameEntity.cpp src\Entities\Rocket.cpp
#	$(CC) -c src\Entities\GameEntity.cpp src\Entities\Rocket.cpp $(IFLAG)

#gamescreen.o: src\GameManager\GameManager.cpp src\GameManager\GGraphics.cpp src\GameManager\TextureManager.cpp
#	$(CC) -c src\GameManager\GameManager.cpp src\GameManager\GGraphics.cpp src\GameManager\TextureManager.cpp $(IFLAG)
#homescreen.o: src\Screens\HomeScreen.cpp src\Screens\Screen.cpp
#	$(CC) -c src\Screens\HomeScreen.cpp src\Screens\Screen.cpp $(IFLAG)

#timeSetting.o: src\Utils\TimeSetting.cpp
#	$(CC) -c src\Utils\TimeSetting.cpp $(IFLAG)

#vector2d.o: src\VectorMath\Vector2d.cpp
#	$(CC) -c src\VectorMath\Vector2d.cpp $(IFLAG)

#main.o: src\main.cpp
#	$(CC) -c src\main.cpp $(IFLAG)

clean:
	rm -f output.exe *.o