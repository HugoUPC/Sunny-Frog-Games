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

	Texture1 = App->textures->Load("Assets/Sprites/PlayerSelectt.png");
	//App->render->Blit(Texture1, -246, 2, NULL); Para saber las coordenadas de los sprites
	//App->render->Blit(Texture1, -492, 0, NULL);
	//App->render->Blit(Texture1, -738, 0, NULL);

	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status ScenePlayerSelect::Update()
{
	

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ScenePlayerSelect::PostUpdate()
{
	// Draw everything --------------------------------------
	int x = 0;
	int y = 0;
	//App->render->Blit(Texture1, x, y, NULL);

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && x >= -738 && x <= 0)
	{
		x += 246;
		//y -= 2;
		//App->render->Blit(Texture1, -246, 2, NULL);
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && x >= -738 && x <= 0)
	{
		x -= 246;
		//y += 2;
		//App->render->Blit(Texture1, -492, 0, NULL);
	}

	App->render->Blit(Texture1, x, y, NULL);

	return update_status::UPDATE_CONTINUE;
}