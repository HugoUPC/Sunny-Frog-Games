#ifndef __MODULE_ANIM_H__
#define __MODULE_ANIM_H__

#include "Module.h"

#define MAX_ANIM 100

enum class ANIM_TYPE
{
	NO_TYPE,
	GOBLINS,
};

struct AnimSpawnpoint
{
	ANIM_TYPE type = ANIM_TYPE::NO_TYPE;
	int x, y;
};

class Anim;
struct SDL_Texture;

class ModuleAnim : public Module
{
public:
	// Constructor
	ModuleAnim(bool startEnabled);

	// Destructor
	~ModuleAnim();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	update_status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired

	// Add an enemy into the queue to be spawned later
	bool AddAnim(ANIM_TYPE type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnAnim(const AnimSpawnpoint& info);

private:
	// A queue with all spawn points information
	AnimSpawnpoint spawnQueue[MAX_ANIM];

	// All spawned enemies in the scene
	Anim* animation[MAX_ANIM] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
};

#endif // __MODULE_ENEMIES_H__