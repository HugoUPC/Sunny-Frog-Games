#include "ScenePlayerSelect.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ScenePlayerSelect::ScenePlayerSelect(bool startEnabled) : Module(startEnabled)
{

}

ScenePlayerSelect::~ScenePlayerSelect()
{

}

// Load assets
bool ScenePlayerSelect::Start()
{
    LOG("Loading background assets");

    bool ret = true;

    Texture1 = App->textures->Load("Assets/Sprites/PlayerSelect.png");



    App->audio->PlayMusic("Assets/Music/characterSelect.ogg", 1.0f);
    PowerUpCollectFx = App->audio->LoadFx("Assets/Fx/powerUp.wav");

    App->render->camera.x = 0;
    App->render->camera.y = 0;


    return ret;
}

update_status ScenePlayerSelect::Update()
{
    if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
    {
        App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
        App->audio->PlayFx(PowerUpCollectFx);
    }


    return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ScenePlayerSelect::PostUpdate()
{
    // Draw everything --------------------------------------
    int x = 0;

    //App->render->Blit(Texture1, -246, 2, NULL); Para saber las coordenadas de los sprites
    //App->render->Blit(Texture1, -492, 0, NULL);
    //App->render->Blit(Texture1, -738, 0, NULL);

    App->render->Blit(Texture1, x, 0, NULL);

    if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
    {
        //App->textures->Unload(Texture1);
        if (x < 0) {
            x += 246;
        }
        App->render->Blit(Texture1, x, 0, NULL);
    }

    if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
    {
        //App->textures->Unload(Texture1);
        if (x > -978) {
            x -= 246;
        }
        App->render->Blit(Texture1, x, 0, NULL);
    }



    return update_status::UPDATE_CONTINUE;
}