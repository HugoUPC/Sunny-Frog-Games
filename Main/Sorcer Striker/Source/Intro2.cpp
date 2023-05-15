#include "Intro2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

Intro2::Intro2(bool startEnabled) : Module(startEnabled)
{

}

Intro2::~Intro2()
{

}

// Load assets
bool Intro2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Intro/Intro1.png");
	//NO HA DE SONAR MUSICA EN AQUESTA PANTALLA TAMPOC
	//App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);
	//App->audio->Disable();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status Intro2::Update()
{
	App->fade->FadeToBlack(this, (Module*)App->scenestory, 90);

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status Intro2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, -246, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}