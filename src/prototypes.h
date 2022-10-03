#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include "defines.h"
#include "object.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;

///Prototypes for all the sunction
int initializeAllegro(int width, int height, const char title[], ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue, ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&arial,  ALLEGRO_SAMPLE_INSTANCE *victoryInstance);
void InitSpezzy(Spezzy &character);
void DrawSpezzy(Spezzy &character);
void MoveSpezzyUp(bool &jump, Spezzy &character);
void MoveSpezzyLeft (Spezzy &character);
void MoveSpezzyRight (Spezzy &character);
collision checkCollision(Spezzy &character, Image *platforms);
void InitImage(Image *platforms);
void displayPlatforms(Image *platforms);
void displayBitmaps(Image *platforms);
void mainmenu(ALLEGRO_FONT *typingFont, ALLEGRO_FONT *titleFont, ALLEGRO_BITMAP *menu);
void menuInteraction(ALLEGRO_FONT *typingFont, ALLEGRO_FONT *titleFont, ALLEGRO_EVENT ev, bool &done, bool &menuState, bool &menuPage, bool &instructionPage, bool &creditsPage, bool &draw);
bool checkVictory(Spezzy &character, Image *platforms, bool &victory);
void victoryAction();
#endif // PROTOTYPES_H_INCLUDED
