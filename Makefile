output: main.o vector2d.o timeSetting.o homescreen.o gamescreen.o entities.o controllers.o
	g++ main.o Vector2d.o TimeSetting.o HomeScreen.o GameEntity.o GameManager.o GGraphics.o KeyBoardHandler.o Rocket.o Screen.o TextureManager.o -L Dependencies\SDL2\lib\x64 -lSDL2main -lSDL2 -lSDL2_image -o output

controllers.o: src\Controllers\KeyBoardHandler.cpp
	g++ -c src\Controllers\KeyBoardHandler.cpp -I Dependencies\SDL2\include


entities.o: src\Entities\GameEntity.cpp src\Entities\Rocket.cpp
	g++ -c src\Entities\GameEntity.cpp src\Entities\Rocket.cpp -I Dependencies\SDL2\include

gamescreen.o: src\GameManager\GameManager.cpp src\GameManager\GGraphics.cpp src\GameManager\TextureManager.cpp
	g++ -c src\GameManager\GameManager.cpp src\GameManager\GGraphics.cpp src\GameManager\TextureManager.cpp -I Dependencies\SDL2\include
homescreen.o: src\Screens\HomeScreen.cpp src\Screens\Screen.cpp
	g++ -c src\Screens\HomeScreen.cpp src\Screens\Screen.cpp -I Dependencies\SDL2\include

timeSetting.o: src\Utils\TimeSetting.cpp
	g++ -c src\Utils\TimeSetting.cpp -I Dependencies\SDL2\include

vector2d.o: src\VectorMath\Vector2d.cpp
	g++ -c src\VectorMath\Vector2d.cpp -I Dependencies\SDL2\include

main.o: src\main.cpp
	g++ -c src\main.cpp -I Dependencies\SDL2\include