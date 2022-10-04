#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;

int initializeAllegro(int width, int height, const char title[], ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue, ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&arial,  ALLEGRO_SAMPLE_INSTANCE *victoryInstance) {


    // set frame rate
    const float FPS = 60;
    // make background white
    ALLEGRO_COLOR background = al_map_rgb(255, 255, 255);

    // Initialize Allegro
	al_init();
	al_init_image_addon();
    al_init_acodec_addon();

	// initialize display
	display = al_create_display(width, height);
	if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
	}
	al_set_window_title(display, title);

   	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}


    //Initalize audio
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(2);
    ALLEGRO_SAMPLE *background_music;
    ALLEGRO_SAMPLE *victory_Music;
    background_music = al_load_sample("audio.wav");
    victory_Music = al_load_sample("Victory.wav");
    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(background_music);
    victoryInstance = al_create_sample_instance(victory_Music);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(victoryInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(victoryInstance, al_get_default_mixer());
    al_play_sample_instance(songInstance);

    if (!background_music) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize background_music!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

	// need to add image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    arial = al_load_ttf_font("arial.ttf", 24, 0);
    if (!arial){
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primative add on
 	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//Create timer
	timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
   	}

	// set up event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

    //Registers timer events
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(background);

	al_flip_display();
	al_start_timer(timer);

	return 0;
}
