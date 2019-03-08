#ifndef Board_hpp
#define Board_hpp

#include <allegro5/allegro.h>
#include <vector>

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
};

#endif