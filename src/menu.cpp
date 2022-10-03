#include <iostream>
#include "defines.h"
#include "object.h"
#include "prototypes.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_SAMPLE *background_music;
extern ALLEGRO_FONT *arial;
extern ALLEGRO_EVENT *ev;
extern int mouseX;
extern int mouseY;

ALLEGRO_FONT *typingFont;
ALLEGRO_FONT *titleFont;
///Prints words for the main menu
void mainmenu(ALLEGRO_FONT *typingFont, ALLEGRO_FONT *titleFont, ALLEGRO_BITMAP *menu)
{
        al_draw_text(titleFont, Red, 100, 75, ALLEGRO_ALIGN_LEFT, "Spezzy");
        al_draw_text(typingFont, Red, 100, 300, ALLEGRO_ALIGN_LEFT, "Play");
        al_draw_text(typingFont, Red, 100, 400, ALLEGRO_ALIGN_LEFT, "How to Play");
        al_draw_text(typingFont, Red, 100, 500, ALLEGRO_ALIGN_LEFT, "Credits");

        al_flip_display();
}
///Function for interaction with the main menu
void menuInteraction(ALLEGRO_FONT *typingFont, ALLEGRO_FONT *titleFont, ALLEGRO_EVENT ev, bool &done, bool &menuState, bool &menuPage, bool &instructionPage, bool &creditsPage, bool &draw)
{
    al_wait_for_event(event_queue, &ev);

    ///Tracks the mouses cursor and sets it to the variables
    if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouseX = ev.mouse.x;
        mouseY = ev.mouse.y;
    }
    ///Closes the game
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        done = true;
        menuState = true;
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        ///Detects when you click down on your mouse
        if(ev.mouse.button == 1)
        {
            ///Checks if the user clicks between certain places on the screen(where the menu words are)
            ///Changes the value of some variables and then send them to the corresponidng screen (e.g. How to play, or Credits)
            if (80 < mouseX && 220 > mouseX && 280 < mouseY && 345 > mouseY && menuPage == true)
            {
                menuPage = false;
                instructionPage = false;
                creditsPage = false;
                menuState = false;
            }
            else if (100 < mouseX && 390 > mouseX && 390 < mouseY && 435 > mouseY && menuPage == true)
            {
                menuPage = false;
                instructionPage = true;
                creditsPage = false;
            }
            else if (100 < mouseX && 265 > mouseX && 500 < mouseY && 540 > mouseY && menuPage == true)
            {
                menuPage = false;
                instructionPage = false;
                creditsPage = true;
            }
            else if (1040 < mouseX && 1165 > mouseX && 590 < mouseY && 638 > mouseY && menuPage == false)
            {
                menuPage = true;
                instructionPage = false;
                creditsPage = false;
                draw = true;
            }
        }
    }
    ///Brings the user to the corresponding page after clicking the words on the main menu
    if(instructionPage)
    {
        al_clear_to_color(Black);
        al_draw_text(typingFont, Red, 600, 50, ALLEGRO_ALIGN_CENTER, "How to Play");
        al_draw_text(arial, White, 25, 150, ALLEGRO_ALIGN_LEFT, "Your mission  Spezzy has just begun. You have finally landed on the planet of DeSporzia.");
        al_draw_text(arial, White, 25, 200, ALLEGRO_ALIGN_LEFT, "You must explore the planet without falling into the void. To get to the end, you must");
        al_draw_text(arial, White, 25, 250, ALLEGRO_ALIGN_LEFT, "travel across the floating boxes using the arrow keys to the final lowest block on the right side of the planet.");
        al_draw_text(arial, White, 25, 300, ALLEGRO_ALIGN_LEFT, " Best of luck Spezzy. We're counting on you!");
        al_draw_text(typingFont, Red, 1050, 600, ALLEGRO_ALIGN_LEFT, "Back");
    }
    else if(creditsPage)
    {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(typingFont, Red, 600, 50, ALLEGRO_ALIGN_CENTER, "Credits");
        al_draw_text(arial, White, 25, 150, ALLEGRO_ALIGN_LEFT, "Created and Developed By: Aayush Kapoor");
        al_draw_text(arial, White, 25, 200, ALLEGRO_ALIGN_LEFT, "Honourable mentions: Lindsay Cullum, Andy Meng and Nick Coballe");
        al_draw_text(typingFont, Red, 1050, 600, ALLEGRO_ALIGN_LEFT, "Back");
    }
    al_flip_display();
}
