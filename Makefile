file1 := main.cpp
#file2 := new.cpp
file2 := geometric.cpp
all:
	g++ -std=c++20 -o proj $(file2) $$(pkg-config --cflags --libs sdl2) -lSDL2_image
clean:
	rm -f proj




	g++ -std=c++20 main.cpp pkg-config --cflags --libs sdl2
