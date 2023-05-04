#include "ModuleUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"

#include <stdio.h>


ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{

}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{

	UIElements = App->textures->Load("Assets/UI/gp-ui.png");
	wintexture = App->textures->Load("Assets/Sprites/stageclear.png");

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { " 01&........x23456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/yb-numbers.png", lookupTable, 1);

	return true;
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

	if (App->player->kills == 10) {
		App->render->Blit(wintexture, 0, 0, NULL, 0);
	}

	if (App->player->lives < 0) {
		App->render->Blit(UIElements, 50, 150, &GameOver, 0);
	}

	return update_status::UPDATE_CONTINUE;
}