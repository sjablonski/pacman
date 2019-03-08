#include "Engine.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <iostream>

using namespace std;

Engine* Engine::instance = 0;

Engine::Engine(int w, int h, const char *t) {
    this->width = w;
    this->height = h;
    this->title = t;
}

Engine::~Engine() {
}

Engine *Engine::getInstance(int width, int height, const char *title) {
    if(!instance)
        instance = new Engine(width, height, title);
    return instance;
}

void Engine::allegroInit() {
    if(!al_init()) {
        cerr << "Error: Allegro init library. \n";
        exit(EXIT_FAILURE);
    } else {
        cout << "Success: Allegro init library. \n";
    }
}

void Engine::allegroImageInit() {
    if(!al_init_image_addon()) {
		cerr << "Error: Allegro init image addon. \n";
        exit(EXIT_FAILURE);
	} else {
        cout << "Success: Allegro init image addon. \n";
    }
}

void Engine::allegroKeyboardInit() {
    if(!al_install_keyboard()) {
		cerr << "Error: Allegro install keyboard. \n";
        exit(EXIT_FAILURE);
	} else {
        cout << "Success: Allegro install keyboard. \n";
    }
}

void Engine::allegroFontInit() {
    al_init_font_addon();
}

ALLEGRO_DISPLAY *Engine::createDisplay() {
    ALLEGRO_DISPLAY *window = al_create_display(width, height);
    if(!window) {
        cerr << "Error: Create display. \n";
        exit(EXIT_FAILURE);
    } else {
        cout << "Success: Create display. \n";
    }
    al_set_window_title(window, title);
    return window;
}

ALLEGRO_BITMAP *Engine::loadBitmap(const char *bitmapName) {
    ALLEGRO_BITMAP image = al_load_bitmap(bitmapName);
    if(!image)
        cerr << "Error: Load bitmap " << bitmapName << '\n';
    else
        cout << "Success: Load bitmap " << bitmapName << '\n';
}