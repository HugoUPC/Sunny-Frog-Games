#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"

#include "SceneDescription.h"
#include "SceneIntro.h"
#include "Intro1.h"
#include "Intro2.h"
#include "SceneStory.h"

#include "SceneLevel1.h"
#include "ScenePlayerSelect.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"

#include "ModuleAnim.h"

#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =    scenedescription = new SceneDescription(true);
	modules[5] =	sceneIntro =	new SceneIntro(false);
	modules[6] =	sceneLevel_1 =	new SceneLevel1(false);		//Gameplay scene starts disabled
	modules[7] =    intro1 =        new Intro1(false);
	modules[8] =    intro2 =        new Intro2(false);
	modules[9] =    scenestory =    new SceneStory(false);

	modules[10] =    scenePlayerSelect = new ScenePlayerSelect(false);

	modules[11] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[12] =	particles =		new ModuleParticles(true);
	modules[13] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled
	modules[14] =	powerups =		new ModulePowerUp(false);

	modules[15] =   animation =     new ModuleAnim(false);

	modules[16] =	collisions =	new ModuleCollisions(true);
	modules[17] =	UI =			new ModuleUI(false);
	modules[18] =	fade =			new ModuleFadeToBlack(true);
	modules[19] =	fonts =			new ModuleFonts(true);
	modules[20] =	render =		new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
