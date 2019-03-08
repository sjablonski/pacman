clean:
	rm -rf pacman.exe

rule:
	g++ main.cpp Engine.cpp Board.cpp \
	    -o pacman.exe \
	    -Wall -Wextra -pedantic \
	    -lallegro-5.0.10-monolith-mt

test: clean rule
	pacman.exe