#include "Board.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <fstream>

using namespace std;

Board::Board(int r, int c, const char *fN) {
    this->row = r;
    this->column = c;
    this->fileName = fN;

    board = new char *[row];
    for(int i=0; i<row; i++)
        board[i] = new char[column];
}

Board::~Board() {
    for(int i=0; i<row; i++)
        delete [] board[i];
    delete [] *board;
}

void Board::loadBoard(ALLEGRO_DISPLAY *display) {
    int i=0;
	string linia;

	ifstream plik;
	plik.open(fileName);
	if(plik.good()==false) {
		al_show_native_message_box(display, "Error", "Error", "Error: Load board", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		plik.close();
		exit(EXIT_FAILURE);
	}

	while(getline(plik, linia)) {
		for(int j=0; j<column; j++) {
			board[i][j] = linia[j];
		}
		i++;
	}
	plik.close();
	cout << "Success: Load board "<< fileName << '\n';
}

void Board::createBoard() {
    for(int i=0; i<row; i++) {
        for(int j=0; j<column; j++) {
            if(board[i][j] == '#')
			    al_draw_filled_rectangle(j*16+24, i*16+24, j*16+48, i*16+48, al_map_rgb(255,255,255));
            else
                al_draw_filled_rectangle(j*16+24, i*16+24, j*16+48, i*16+48, al_map_rgb(0,255,0));
        }
    }
}