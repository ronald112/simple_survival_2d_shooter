#include "header.h"

int main() {
    srand(time(0));
    t_app app;
    t_entity player;
    SDL_Rect dest;
    t_sounds sound;
    t_stage stage;
    long then = SDL_GetTicks(); 
    float remainder = 0;
    int spwn_xy[SPAWN_SPOTS*2];

    t_entity **bullets = (t_entity**)malloc(MAX_ENTITIES * sizeof(t_entity*));
    t_entity **entities = (t_entity**)malloc(MAX_ENTITIES * sizeof(t_entity*));

    init_containers(entities, bullets);

    memset(&app, 0, sizeof(app));
    memset(&player, 0, sizeof(player));
    memset(&sound, 0, sizeof(sound));
    memset(&stage, 0, sizeof(stage));
    
    init_SDL(&app, &sound);
    init_stage(&stage, &app, &player, entities);
    place_spawn_spots(spwn_xy);
    init_bullets(&app, &stage);

    t_entity button_01;
    t_entity button_02;
    t_entity button_03;
    t_entity img_fone;
    t_entity back_image;
    t_entity vol_button;
    button_01.texture = loadTexture("gfx/menu_button_01.png", &app);
    button_02.texture = loadTexture("gfx/menu_button_02.png", &app);
    button_03.texture = loadTexture("gfx/menu_button_03.png", &app);
    img_fone.texture = loadTexture("gfx/background_for_menu.jpg", &app);
    back_image.texture = loadTexture("gfx/back_image.jpg", &app);
    vol_button.texture = loadTexture("gfx/vol_on.png", &app);
    create_button(&app);

    int res = 0;
    int res2 = 0;

    while (1) {
        //Draw Rectangle
        do_input(&app, sound.steps_sounds, &player, &sound);
        draw_menu(&button_01, &button_02, &button_03, &vol_button, &img_fone, &back_image, &app);
        present_scene(&app);
        //
        res = pick_button(&app, &sound);
        if (res == 1) {
            while (player.health > 0) {
        		prepare_scene(&app, &dest);
        		
        		res2 = do_input(&app, sound.steps_sounds, &player, &sound);

                if (res2 == 5)
                    break;

        		SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
        		
        		app.delegate.logic(&app, &stage, &player, entities, bullets, spwn_xy, &sound);
        		
        		app.delegate.draw(&stage, &app, entities, bullets, &player, spwn_xy);

                draw_interface(&vol_button, &app);
        		
        		present_scene(&app);

                capFrameRate(&then, &remainder);
            }
        }
        else if(res == 3)
            break;
        init_containers(entities, bullets);
        init_player(&player, &stage, &app, entities);
    }
    Mix_FreeMusic(sound.main_menu_music);
    Mix_FreeChunk(sound.cave_background_sounds);
    Mix_FreeChunk(sound.steps_sounds);
    Mix_FreeChunk(sound.unable_fire_sounds);
    Mix_FreeChunk(sound.able_fire_sounds);
    Mix_FreeChunk(sound.reload_sounds);
    Mix_CloseAudio();

    free(bullets[0]);
    for (int i = 1; i < MAX_ENTITIES; i++) {
        free(bullets[i]);
        free(entities[i]);
    }
    free(bullets);
    free(entities);


    cleanup(&app, &stage, &button_01
    , &button_02, &button_03, &img_fone, &back_image, &vol_button);

    return 0;
}
