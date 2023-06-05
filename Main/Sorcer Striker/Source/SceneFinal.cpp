#include "SceneFinal.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneFinal::SceneFinal(bool startEnabled) : Module(startEnabled)
{

}

SceneFinal::~SceneFinal()
{

}

// Load assets
bool SceneFinal::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Sprites/Final.png");
	App->audio->PlayMusic("Assets/Music/Final.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneFinal::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneFinal::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}