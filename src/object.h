#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
///Spezzy the main character
struct Spezzy
{
    int ID;
    int x;
    int y;
    int changeX;
    int changeY;
    int lives;
    int speed;
    int score;
    int boundX;
    int boundY;
    float dy;
    float dx;
    int jumpSpeed;
    float gravity;
};
///Struct for collision between character and boxes
struct collision
{
    bool bot;
    bool top;
    bool left;
    bool right;
};
///Struct for platform coordinates
struct Image
{
    ALLEGRO_BITMAP *bitmap;
    int x1;
    int y1;
    int x2;
    int y2;
};



#endif // OBJECT_H_INCLUDED
