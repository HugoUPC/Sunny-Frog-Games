#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	lasertexture = App->textures->Load("Assets/Sprites/particles.png");
	explosiontexture = App->textures->Load("Assets/Sprites/explosion.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	// TODO 2:	Create the template for a new particle "laser"
	//			Remember: not all the code goes here!
	//			Follow the example with the "explosion" particle

	laser.anim.PushBack({ 0, 0, 16, 33});
	laser.anim.loop = true;
	laser.anim.speed = 0.3f;
	laser.speed.y = -6;
	
	laserR.anim.PushBack({ 0, 0, 16, 33 });
	laserR.anim.loop = true;
	laserR.anim.speed = 0.3f;
	laserR.speed.y = -6;
	laserR.speed.x = 1;

	laserL.anim.PushBack({ 0, 0, 16, 33 });
	laserL.anim.loop = true;
	laserL.anim.speed = 0.3f;
	laserL.speed.y = -6;
	laserL.speed.x = -1;

	bat_shotsR.anim.PushBack({ 17, 0, 112, 33 });
	bat_shotsR.anim.loop = true;
	bat_shotsR.anim.speed = 0.3f;
	bat_shotsR.speed.y = -6;
	bat_shotsR.speed.x = 2;

	bat_shotsL.anim.PushBack({ 17, 0, 112, 33 });
	bat_shotsL.anim.loop = true;
	bat_shotsL.anim.speed = 0.3f;
	bat_shotsL.speed.y = -6;
	bat_shotsL.speed.x = -2;
	
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			// TODO 6: Make so every time a particle hits a wall it triggers an explosion particle
			AddParticle(explosion, particles[i]->position.x, particles[i]->position.y);

			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(lasertexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			App->render->Blit(explosiontexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}