#include "SceneStory4.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <stdio.h>

SceneStory4::SceneStory4(bool startEnabled) : Module(startEnabled)
{

}

SceneStory4::~SceneStory4()
{

}

// Load assets
bool SceneStory4::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/Intro/prueba.png");
	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);


	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

update_status SceneStory4::Update()
{
	//App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory4::PostUpdate()
{
	App->render->Blit(texture, -492, -347, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory4::CleanUp()
{
	//App->textures->Unload(bgTexture);
	App->textures->Unload(texture);

	return true;
}