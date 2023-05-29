#include "ModuleUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"

#include <stdio.h>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
	stage1.PushBack({ 0,40,240,40 });
	stage1.PushBack({ 0,40,240,40 });
	stage1.PushBack({ 0,40,240,40 });
	stage1.PushBack({ 0,40,240,40 });
	stage1.speed = 0.1f;
	stage1.loop = false;

	type.PushBack({ 4,8,91,132 });
	type.PushBack({ 102,8,91,132 });
	type.PushBack({ 201,8,91,132 });
	type.PushBack({ 298,8,91,132 });
	type.PushBack({ 396,8,91,132 });
	type.PushBack({ 495,8,91,132 });
	type.PushBack({ 592,8,91,132 });
	type.PushBack({ 690,8,91,132 });

	type.PushBack({ 5,149,91,132 });
	type.PushBack({ 101,149,91,132 });
	type.PushBack({ 200,149,91,132 });
	type.PushBack({ 297,149,91,132 });
	type.PushBack({ 395,149,91,132 });
	type.PushBack({ 494,149,91,132 });
	type.PushBack({ 591,149,91,132 });
	type.PushBack({ 689,149,91,132 });

	type.PushBack({ 4,287,91,132 });
	type.PushBack({ 102,287,91,132 });
	type.PushBack({ 201,287,91,132 });
	type.PushBack({ 298,287,91,132 });
	type.PushBack({ 396,287,91,132 });
	type.PushBack({ 495,287,91,132 });
	type.PushBack({ 592,287,91,132 });
	type.PushBack({ 690,287,91,132 });
	type.speed = 0.1f;
	type.loop = false;
}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{

	UIElements = App->textures->Load("Assets/UI/gp-ui.png");
	wintexture = App->textures->Load("Assets/Sprites/stageclear1.png");
	stage1texture = App->textures->Load("Assets/Sprites/stage1.png");
	typingtexture = App->textures->Load("Assets/Sprites/typing.png");

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { " 01&........x23456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/yb-numbers.png", lookupTable, 1);

	return true;
}

update_status ModuleUI::Update() {
	stage1.Update();
	type.Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate()
{

	SDL_Rect Player1 = { 35, 1, 55, 8 };
	SDL_Rect livesIcon = { 145, 46, 15, 16 };
	SDL_Rect bombsIcon = { 163, 47, 16, 16 };
	SDL_Rect HighScore = { 93, 1, 64, 8 };
	SDL_Rect Player2 = { 1, 29, 56, 8 };
	SDL_Rect InsertCoinPlayer2 = { 192,45,55,16 };

	SDL_Rect GameOver = { 1, 47, 143, 16 };
	


	App->render->Blit(UIElements, 5, 5, &Player1, 0);
	App->render->Blit(UIElements, 5, 25, &livesIcon, 0);
	App->render->Blit(UIElements, 35, 25, &bombsIcon, 0);
	App->render->Blit(UIElements, 90, 5, &HighScore, 0);
	App->render->Blit(UIElements, 170, 5, &Player2, 0);
	App->render->Blit(UIElements, 170, 20, &InsertCoinPlayer2, 0);


	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", App->player->score);
	sprintf_s(livesText, 10, "x%1d", App->player->lives);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 13, scoreFont, scoreText);
	App->fonts->BlitText(20, 30, scoreFont, livesText);
	App->fonts->BlitText(50, 30, scoreFont, "x0");
	App->fonts->BlitText(100, 13, scoreFont, "999999");
	App->fonts->BlitText(220, 13, scoreFont, "0");

	//App->fonts->BlitText(50, 300, scoreFont, "0123456789");

	if (App->player->kills >= 20) {
		App->render->Blit(wintexture, 0, 0, NULL, 0);
	}

	if (App->player->lives < 0) {
		App->render->Blit(UIElements, 50, 150, &GameOver, 0);
	}

	if (App->render->camera.y < -100 && App->render->camera.y > -300) {
		SDL_Rect rect = stage1.GetCurrentFrame();
		App->render->Blit(stage1texture, 0, App->render->camera.y, &rect);
	}
	if (App->render->camera.y > -200) {
		SDL_Rect rect = type.GetCurrentFrame();
		App->render->Blit(typingtexture, 10, 104 + App->render->camera.y, &rect);
	}
	return update_status::UPDATE_CONTINUE;
}