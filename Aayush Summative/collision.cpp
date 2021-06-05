#include <iostream>
#include "prototypes.h"
#include "object.h"


///Checks collision between character and collision box
collision checkCollision(Spezzy &character, Image *platforms)
{

    collision temp;
    temp.bot = false;
    temp.top = false;
    temp.left = false;
    temp.right = false;
    for(int i = 0; i <= 6; i++)
    {
        ///Check for collision with the bottom of the character and the top of the block
        if(character.x < platforms[i].x2 && character.x + character.changeX > platforms[i].x1
           && character.y < platforms[i].y2
           && character.y + character.changeY > platforms[i].y1
           && character.y + character.changeY < platforms[i].y1 + 10)
        {
            temp.bot = true;
        }
        ///Check for collision with the top of the character and the bottom of the block
        if(character.x < platforms[i].x2 && character.x + character.changeX > platforms[i].x1
           && character.y < platforms[i].y2
           && character.y + character.changeY > platforms[i].y1
           && character.y > platforms[i].y2 - 10)
        {
            temp.top = true;
        }
        ///Check for collision with the left of the character and the right of the block
        if(character.x < platforms[i].x2 && character.x + character.changeX > platforms[i].x1
           && character.y < platforms[i].y2
           && character.y + character.changeY > platforms[i].y1
           && character.x > platforms[i].x2 - 10)
        {
            temp.left = true;
        }
        ///Check for collision with the right of the character and the left of the block
        if(character.x < platforms[i].x2 && character.x + character.changeX > platforms[i].x1
           && character.y < platforms[i].y2
           && character.y + character.changeY > platforms[i].y1
           && character.x +character.changeX < platforms[i].x1 + 10)
        {
            temp.right = true;
        }

    }

    return temp;
}
///Function to check if the character reaches the final blcok
bool checkVictory(Spezzy &character, Image *platforms, bool &victory)
{
    ///Checks if the character has made TOP contact with the final block
    if(character.x < platforms[5].x2 && character.x + character.changeX > platforms[5].x1
           && character.y < platforms[5].y2
           && character.y + character.changeY > platforms[5].y1
           && character.y + character.changeY < platforms[5].y1 + 10)
    {
        ///If there is top contact changes the value of the bool value to true
        victory = true;
    }
    else
    {
        victory = false;
    }

    return victory;
}
