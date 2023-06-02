#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleUI : public Module
{
public:
	// Constructor
	ModuleUI(bool startEnabled);

	// Destructor
	~ModuleUI();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status Update() override; 
	update_status PostUpdate() override;

public:
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	char livesText[10] = { "\0" };
	char bombsText[10] = { "\0" };

	SDL_Texture* UIElements = nullptr;
	SDL_Texture* wintexture = nullptr;
	SDL_Texture* stage1texture = nullptr;
	SDL_Texture* typingtexture = nullptr;

	Animation stage1;
	Animation type;
};

#endif //!__MODULE_PLAYER_H__