all: compile link

compile:
	g++ -c main.cpp -IC:\Users\nmgoo\OneDrive\Documents\SFML-2.5.1\include -DSFML_STATIC 

link:
	g++ main.o -o sfml-app -LC:\Users\nmgoo\OneDrive\Documents\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	rm -f main *.o