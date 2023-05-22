#ifndef __SCENE_PLAYERSELECT_H__
#define __SCENE_PLAYERSELECT_H__

#include "Module.h"
#include "Animation.h"


struct SDL_Texture;

class ScenePlayerSelect : public Module
{
public:
	//Constructor
	ScenePlayerSelect(bool startEnabled);

	//Destructor
	~ScenePlayerSelect();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* Texture1 = nullptr;
	SDL_Texture* texture = nullptr;
	int PowerUpCollectFx = 0;

	int arrayselection[0][4];
};

#endif