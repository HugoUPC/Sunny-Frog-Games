#include "SceneDescription.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneDescription::SceneDescription(bool startEnabled) : Module(startEnabled)
{

}

SceneDescription::~SceneDescription()
{

}

// Load assets
bool SceneDescription::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Sprites/Description.png");
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneDescription::Update()
{
	//680 porque serian dos paginas de 240x340, cuando acaba de pasar esa pagina se va solo a la intro
	if (App->render->camera.y < 680) {
		App->render->camera.y += 1;
	}
	if (App->render->camera.y >= 680) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	//pa ir directo al gameplay xd
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneDescription::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}