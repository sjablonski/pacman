#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

const float FPS = 60;

#include "Engine.hpp"
#include "Board.hpp"
#include "ControlKeys.hpp"

int main(void) {
    Engine *e = Engine::getInstance();
    e->allegroInit();
    e->allegroKeyboardInit();
    e->allegroImageInit();
    ALLEGRO_DISPLAY *display = e->createDisplay();

    Board b(30, 28, "Board.txt");
    b.loadBoard(display);
    b.addImage(e->loadBitmap("images/wall.png"));
    b.addImage(e->loadBitmap("images/blank.png"));

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    float bouncer_x = 14*16;
    float bouncer_y = 23*16;
    bool key[4] = { false, false, false, false };
    bool dir[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        return -1;
    }
    
    bouncer = al_create_bitmap(16, 16);
    if(!bouncer) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    
    al_set_target_bitmap(bouncer);
    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));
    
    event_queue = al_create_event_queue();
    if(!event_queue) {
        al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

    float moveSpeed = 4;
    float old_x;
    float old_y;
    while(!doexit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
    
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            old_x = bouncer_x;
            old_y = bouncer_y;
            if(key[KEY_UP]) {
                dir[KEY_UP] = true;
                dir[KEY_DOWN] = false;
                dir[KEY_LEFT] = false;
                dir[KEY_RIGHT] = false;
            }

            else if(key[KEY_DOWN]) {
                dir[KEY_UP] = false;
                dir[KEY_DOWN] = true;
                dir[KEY_LEFT] = false;
                dir[KEY_RIGHT] = false;
            }

            else if(key[KEY_LEFT]){
                dir[KEY_UP] = false;
                dir[KEY_DOWN] = false;
                dir[KEY_LEFT] = true;
                dir[KEY_RIGHT] = false;
            }

            else if(key[KEY_RIGHT]) {
                dir[KEY_UP] = false;
                dir[KEY_DOWN] = false;
                dir[KEY_LEFT] = false;
                dir[KEY_RIGHT] = true;
            }

            if(dir[KEY_UP]) {
                bouncer_y -= moveSpeed;
            }

            else if(dir[KEY_DOWN]) {
                bouncer_y += moveSpeed;
            }

            else if(dir[KEY_LEFT]) {
                bouncer_x -= moveSpeed;
            }

            else if(dir[KEY_RIGHT]) {
                bouncer_x += moveSpeed;
            }

            if(b.checkMovement(bouncer_x, bouncer_y)) {
                bouncer_x = old_x;
                bouncer_y = old_y;
            }

            if(bouncer_x/16-1 >= 28) bouncer_x = 0*16;
            if(bouncer_x/16-1 < -1) bouncer_x = 27*16;
            if(bouncer_y/16-1 >= 30) bouncer_y = 0*16;
            if(bouncer_y/16-1 < -1) bouncer_y = 29*16;

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                break;

                case ALLEGRO_KEY_LEFT: 
                key[KEY_LEFT] = true;
                break;

                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;

                case ALLEGRO_KEY_LEFT: 
                key[KEY_LEFT] = false;
                break;

                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

                case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
            }
        }
    
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
    
            al_clear_to_color(al_map_rgb(0,0,0));
            b.createBoard();
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
    
            al_flip_display();
        }
        //printf("(%f, %f)\n", bouncer_x, bouncer_y);
    }
    
    al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}