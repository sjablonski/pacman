#ifndef Board_hpp
#define Board_hpp

#include <allegro5/allegro.h>
#include <vector>
#include "ControlKeys.hpp"

class Board {
    int row;
    int column;
    char **board;
    const char *fileName;
    std::vector <ALLEGRO_BITMAP*> image;

public:
    Board(int, int, const char*);
    ~Board();
    void loadBoard(ALLEGRO_DISPLAY*);
    void createBoard();
    void addImage(ALLEGRO_BITMAP*);
    bool checkMovement(float, float);
};

class Tile {
    int x;
    int y;
    int top;
    int bottom;
    int left;
    int right;

public:
    Tile(float, float);
    bool isWall();
    int getTop();
    int getBottom();
    int getLeft();
    int getRight();
};

#endif