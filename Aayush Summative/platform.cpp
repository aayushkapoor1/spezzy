#include <iostream>
#include "defines.h"
#include "prototypes.h"
#include "object.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

int main()
{
    Image platform;
    if (!loadBitmap(platform, "platform.png"))
        return 1;

    setPosition(platform, 250, 350);

    al_draw_bitmap(platform.bitmap, platform.x, platform.y, 0);

}
