#include "Board.hpp"
#include "ControlKeys.hpp"

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
			    al_draw_bitmap(image[0],j*16, i*16,0);
            else
                al_draw_bitmap(image[1],j*16, i*16,0);
        }
    }
}

void Board::addImage(ALLEGRO_BITMAP *i) {
    image.push_back(i);
}

bool Board::checkMovement(float x, float y) {
    bool xOverlaps = false;
    bool yOverlaps = false;
    bool collision = false;
    for(int i=0; i<row; i++) {
        for(int j=0; j<column; j++) {
            Tile t(j, i);
            if(board[i][j] == '#') {
                xOverlaps = (x < t.getRight()) && (x+16 > t.getLeft());
                yOverlaps = (y < t.getBottom()) && (y+16 > t.getTop());
                if(xOverlaps && yOverlaps)
                    collision = true;
            }
        }
    }
    return collision;
}

Tile::Tile(float x, float y) {
    this->x = x;
    this->y = y;
    this->top = y*16;
    this->bottom = y*16+16;
    this->left = x*16;
    this->right = x*16+16;
}

int Tile::getTop() {
    return top;
}

int Tile::getBottom() {
    return bottom;
}

int Tile::getLeft() {
    return left;
}

int Tile::getRight() {
    return right;
}