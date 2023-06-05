#include "SceneFinal.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

SceneFinal::SceneFinal(bool startEnabled) : Module(startEnabled)
{
	cuadrado.PushBack({ 251,59,14,14 });
	cuadrado.PushBack({ 272,59,14,14 });
	cuadrado.PushBack({ 293,59,14,14 });
	cuadrado.PushBack({ 313,59,14,14 });
	cuadrado.PushBack({ 333,59,14,14 });
	cuadrado.speed = 1.0f;
	cuadrado.loop;

	letras.PushBack({});
	letras.PushBack({});
	letras.PushBack({});
	letras.PushBack({});
	letras.PushBack({});
	letras.PushBack({});
	letras.speed = 1.0f;
	letras.loop;

	n.PushBack({ 244,95,7,6 });
	u.PushBack({275,105,6,6});
	b.PushBack({ 254,84,7,7 });
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

	timeout = SDL_GetTicks() + 1000;

	cuadrado.Reset();

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
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 10000)) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	cuadrado.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneFinal::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, 0, 0, NULL);

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2000) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2500)) {
		SDL_Rect rect = cuadrado.GetCurrentFrame();
		App->render->Blit(textura, 4, 32, &rect);
		SDL_Rect rect1 = letras.GetCurrentFrame();
		App->render->Blit(textura, 6, 34, &rect1);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2500) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = cuadrado.GetCurrentFrame();
		App->render->Blit(textura, 20, 32, &rect);
		SDL_Rect rect1 = letras.GetCurrentFrame();
		App->render->Blit(textura, 22, 34, &rect1);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3500)) {
		SDL_Rect rect = cuadrado.GetCurrentFrame();
		App->render->Blit(textura, 36, 32, &rect);
		SDL_Rect rect1 = letras.GetCurrentFrame();
		App->render->Blit(textura, 38, 34, &rect1);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2500)) {
		SDL_Rect rect = n.GetCurrentFrame();
		App->render->Blit(textura, 6, 34, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = u.GetCurrentFrame();
		App->render->Blit(textura, 22, 34, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3500)) {
		SDL_Rect rect = b.GetCurrentFrame();
		App->render->Blit(textura, 38, 34, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneFinal::CleanUp()
{
	App->textures->Unload(textura);

	return true;
}