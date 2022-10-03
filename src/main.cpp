///Aayush Kapoor - ICS3U Summative - June 12th, 2020
///This summative expresses my knowledge on the C and
///Allegro 5 coding language which was learned throughout the year.
///This project also demonstrates  knowledge which was learned by
///extensive, extra reserach. Sit back, turn on your speakes, and enjoy
///Spezzy!

#include <stdio.h>
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

///Global variables
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_SAMPLE *background_music;
ALLEGRO_FONT *arial;
ALLEGRO_SAMPLE_INSTANCE *victoryInstance;
int mouseX;
int mouseY;

extern ALLEGRO_FONT *typingFont;
extern ALLEGRO_FONT *titleFont;

enum KEYS{UP, LEFT, RIGHT};

bool keys[3] = {false, false, false};

int main()
{
    ///Initalize allegro and check if properly called
    if (initializeAllegro(SCREEN_W, SCREEN_H, "Summative Game", display, event_queue, timer, arial, victoryInstance) == -1) {
        printf("Allegro failed to load\n");
        return 1;
    }

    ///Primitive variables
    bool done = false;
    bool jump = false;
    bool menuState = true;
    bool menuPage = true;
    bool instructionPage = false;
    bool creditsPage = false;
    bool draw = false;
    bool victory = false;
    int deathCount = 0;
    mouseX = 0;
    mouseY = 0;

    ///Object variables
    Spezzy character;
    InitSpezzy(character);
    Image platforms[7];
    InitImage(platforms);
    collision c;

    ///Initalize fonts
    ALLEGRO_FONT *titleFont = al_load_ttf_font("TitleFont.ttf", 150, 0);
    ALLEGRO_FONT *typingFont = typingFont = al_load_ttf_font("TypingFont.ttf", 48, 0);

    ///Initalize textfile
    FILE *fptr;
    fptr = fopen("DeathCount.txt", "w");
    if (fptr == NULL)
    {
        printf("Unable to open DeathCount.txt");

	}

	///Initalize and declare bitmap for the menu
    ALLEGRO_BITMAP *menu = nullptr;
    menu = al_load_bitmap("Menu.png");
    al_draw_bitmap(menu, 0, 0, 0);

    ///Runs loop until game is finished
    while(!done)
    {
        ///Initalizes event queue
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        ///Prints menu screen
        if(draw)
            al_draw_bitmap(menu, 0, 0, 0);
        ///Ensures that the menu bitmap is only drawn once
        draw = false;

        ///Prints menu page
        if(menuState)
        {
            if(menuPage)
                mainmenu(typingFont, titleFont, menu);
            ///Calls function for menu interface
            menuInteraction(typingFont, titleFont, ev, done, menuState, menuPage, instructionPage, creditsPage, draw);
            al_flip_display();

        }
        else
        {
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)         ///Allows game to close by red 'X'
            {
                done = true;    ///Causes loop to end
            }
            else if(ev.type == ALLEGRO_EVENT_TIMER)
            {
                ///Player movement
                if(keys[UP] && !(jump))
                    MoveSpezzyUp(jump, character);
                if(keys[LEFT])
                    MoveSpezzyLeft(character);
                if(keys[RIGHT])
                    MoveSpezzyRight(character);

                ///Gravity
                if(character.dy < 9)
                {
                    character.dy += 0.3;
                }
                ///Initalizes of collision
                c.bot = false;
                c.top = false;
                c.left = false;
                c.right = false;

                collision temp = checkCollision(character, platforms);
                c.bot |= temp.bot;
                c.top |= temp.top;
                c.left |= temp.left;
                c.right |= temp.right;
                ///Detects collsion between collision boxes and character
                if(c.bot && character.dy > 0)
                {
                    jump = false;
                    character.dy = 0;
                }
                if(c.top && character.dy < 0)
                {
                    character.dy = 0;

                }
                if(c.left && character.dx < 0)
                {
                    character.dx = 0;
                }
                if(c.right && character.dx > 0)
                {
                    character.dx = 0;
                }
                ///Calls function to check if the character reaches the final platform
                checkVictory(character, platforms, victory);
                if(victory)
                {
                    ///Calls function for victory page
                    victoryAction();
                    ///Prints number of deaths to textfile and then leaves loop
                    fprintf(fptr, "You died %d times last game.\n", deathCount);
                    al_rest(3.5);
                    done = true;
                }
                ///Changes the characters position
                character.y += character.dy;
                character.x += character.dx;
                ///Re-positions character when it falls off the screen
                if (character.y >= 650)
                {
                    character.x = 20;
                    character.y = 200;
                    jump = false;
                    deathCount++;
                }

            }
            ///Recognizes when teh keyboard buttons are pushed
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                }
            }
            ///Recognizes when teh keyboard buttons are not pushed down
            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    character.dx = 0;   ///Resets the x velocity
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    character.dx = 0;   ///Resets the x velocity
                    break;
                }
            }
            if(al_is_event_queue_empty(event_queue))
            {
                ///Prints bitmaps, character and changes screen colour;
                al_clear_to_color(al_map_rgb(0,0,0));
                displayPlatforms(platforms);
                displayBitmaps(platforms);
                DrawSpezzy(character);
                al_flip_display();
            }
        }
    }
    ///Closes file
    fclose(fptr);
    al_destroy_bitmap(menu);
    return 0;
}
