#include <stdio.h>
#include "prototypes.h"
#include "object.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
///Global variables
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_SAMPLE_INSTANCE *victoryInstance;
///Function prints the collision boxes
void displayPlatforms(Image *platforms)
{
    for (int i = 0; i <= 6; i++)
    {
        al_draw_filled_rectangle(platforms[i].x1, platforms[i].y1, platforms[i].x2, platforms[i].y2, al_map_rgb(255, 255, 0));
    }
}
///Function prints platform bitmaps and the game background
void displayBitmaps(Image *platforms)
{
    ///Prints background
    ALLEGRO_BITMAP *background = nullptr;
    background = al_load_bitmap("BG.png");
    al_draw_bitmap(background, 0, 0, 0);
    al_destroy_bitmap(background);
    ///Prints platforms to cover the collision boxes
    ALLEGRO_BITMAP *block[6] = {nullptr};
    for (int i = 0; i <=6; i++)
    {
        block[i] = al_load_bitmap("Crate.png");
        al_draw_bitmap(block[i], platforms[i].x1, platforms[i].y1, 0);
        al_destroy_bitmap(block[i]);
    }
}
///Function for when the character reaches the final platform
void victoryAction()
{
    ///Sets background colour
    al_clear_to_color(Black);
    ///Set-up for the victory music
    al_reserve_samples(1);
    ALLEGRO_SAMPLE *victory_Music;
    victory_Music = al_load_sample("Victory.wav");
    victoryInstance = al_create_sample_instance(victory_Music);
    al_set_sample_instance_playmode(victoryInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(victoryInstance, al_get_default_mixer());
    al_play_sample_instance(victoryInstance);
    ///Prints the park background
    ALLEGRO_BITMAP *park = nullptr;
    park = al_load_bitmap("Park.png");
    al_draw_bitmap(park, 0, 0, 0);
    al_destroy_bitmap(park);
    ///Prints the big victory on top of the park
    ALLEGRO_BITMAP *victory = nullptr;
    victory = al_load_bitmap("Victory.png");
    al_draw_bitmap(victory, 400, 100, 0);
    al_destroy_bitmap(victory);

    al_flip_display();
}
