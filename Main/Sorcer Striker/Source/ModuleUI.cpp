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

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { " 01..........23456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/yb-numbers.png", lookupTable, 1);

	return true;
}

update_status ModuleUI::PostUpdate()
{

	App->render->Blit(UIElements, 0, 0, NULL, 0);


	// Draw UI (score) --------------------------------------
	LOG("Holaa %d", App->player->score);
	sprintf_s(scoreText, 10, "%7d", App->player->score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(50, 20, scoreFont, scoreText);

	App->fonts->BlitText(50, 300, scoreFont, "0123456789");

	return update_status::UPDATE_CONTINUE;
}