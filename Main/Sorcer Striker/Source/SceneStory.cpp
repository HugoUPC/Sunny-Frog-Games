#include "SceneStory.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleAnim.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <stdio.h>

SceneStory::SceneStory(bool startEnabled) : Module(startEnabled)
{

}

SceneStory::~SceneStory()
{

}

// Load assets
bool SceneStory::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Intro/prueba.png");
	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);

	App->animation->AddAnim(ANIM_TYPE::GOBLINS, 0, -16);


	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

update_status SceneStory::Update()
{
	//App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	//App->render->Blit(bgTexture, -877, -201, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneStory::CleanUp()
{
	App->textures->Unload(bgTexture);

	return true;
}