#ifndef Engine_hpp
#define Engine_hpp

#include <allegro5/allegro.h>

class Engine {
private:
    int width;
    int height;
    const char *title;
    static Engine *instance;

    Engine(int, int, const char*);
public:
    ~Engine();
    static Engine *getInstance(int=616, int=700, const char *title="Pacman");
    void allegroInit();
    void allegroImageInit();
    void allegroKeyboardInit();
    void allegroFontInit();
    ALLEGRO_DISPLAY *createDisplay();
    ALLEGRO_BITMAP *loadBitmap(const char*);
};

#endif