#include "defines.h"
#include "object.h"
#include "prototypes.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

///Defining functions
void InitSpezzy(Spezzy &character)
{
    ///Character's properties
    character.x = 20;
    character.y = 200;
    character.changeX = 40;
    character.changeY = 66;
    character.speed = 7;
    character.boundX = 6;
    character.dy = 0;
    character.dx = 0;
    character.jumpSpeed = -9;
    character.gravity = 0.30;

}
void InitImage(Image *platforms)
{
    ///Platform's position
    platforms[0].x1 = 20;
    platforms[0].x2 = 70;
    platforms[0].y1 = 450;
    platforms[0].y2 = 500;

    platforms[1].x1 = 200;
    platforms[1].x2 = 250;
    platforms[1].y1 = 325;
    platforms[1].y2 = 375;

    platforms[2].x1 = 800;
    platforms[2].x2 = 850;
    platforms[2].y1 = 275;
    platforms[2].y2 = 325;

    platforms[3].x1 = 450;
    platforms[3].x2 = 500;
    platforms[3].y1 = 200;
    platforms[3].y2 = 250;

    platforms[4].x1 = 500;
    platforms[4].x2 = 550;
    platforms[4].y1 = 500;
    platforms[4].y2 = 550;

    platforms[5].x1 = 1100;
    platforms[5].x2 = 1150;
    platforms[5].y1 = 500;
    platforms[5].y2 = 550;
}
///Drawing the main character
void DrawSpezzy(Spezzy &character)
{
    al_draw_filled_rectangle(character.x, character.y, character.x + character.changeX, character.y + character.changeY, al_map_rgb(0, 0, 255));          ///Character
    al_draw_filled_rectangle(character.x + 70, character.y + 15, character.x + 25, character.y + 10, al_map_rgb(0, 255, 0));    ///Gun

}
///Character's movement when you press the up arrow key
void MoveSpezzyUp(bool &jump, Spezzy &character)
{
    jump = true;
    character.dy = character.jumpSpeed;
}
///Character's movement when you press the left arrow key
void MoveSpezzyLeft(Spezzy &character)
{
    character.dx = -5;
    ///Restricts the character's position
    if(character.x < 0)
        character.x = 0;
}
///Character's movement when you press the left arrow key
void MoveSpezzyRight(Spezzy &character)
{
    character.dx = 5;
    ///Restricts the character's position
    if(character.x > 1150)
        character.x = 1150;
}
