#include "ScenePlayerSelect.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ScenePlayerSelect::ScenePlayerSelect(bool startEnabled) : Module(startEnabled)
{
    selected.PushBack({ 1009, 32, 39, 50 });
    selected.PushBack({ 1009, 92, 39, 50 });
    selected.PushBack({ 1009, 152, 39, 50 });
    selected.PushBack({ 1009, 214, 39, 50 });
    selected.speed = 0.1f;
    
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

    position.x = 0;
    position.y = 0;

    return ret;
}

update_status ScenePlayerSelect::Update()
{
    if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
    {
        App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
        App->audio->PlayFx(PowerUpCollectFx);
    }

    if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
    {
       position.x += 246; 
    }

    if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
    {
        position.x -= 246;     
    }

    selected.Update();

    return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ScenePlayerSelect::PostUpdate()
{
    // Draw everything --------------------------------------

    //App->render->Blit(Texture1, -246, 2, NULL); Para saber las coordenadas de los sprites
    //App->render->Blit(Texture1, -492, 0, NULL);
    //App->render->Blit(Texture1, -738, 0, NULL);

    if (position.x == 738) {
        App->render->Blit(Texture1, 738, 0, NULL);
    }
    else if (position.x == 0) {
        App->render->Blit(Texture1, 0, 0, NULL);
    }
    else { App->render->Blit(Texture1, position.x, 0, NULL); }
   

    if (position.x == 0) {
        SDL_Rect rect = selected.GetCurrentFrame(); 
        App->render->Blit(Texture1, 29, 78, &rect); 
    }
    if (position.x == 246) {
        SDL_Rect rect = selected.GetCurrentFrame();
        App->render->Blit(Texture1, 326, 78, &rect);
    }
    if (position.x == 492) {
        SDL_Rect rect = selected.GetCurrentFrame();
        App->render->Blit(Texture1, 616, 78, &rect);
    }
    if (position.x == 738) {
        SDL_Rect rect = selected.GetCurrentFrame();
        App->render->Blit(Texture1, 914, 78, &rect);
    }
   
    return update_status::UPDATE_CONTINUE;
}