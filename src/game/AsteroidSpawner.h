#ifndef ASTEROIDSPAWNER_H_
#define ASTEROIDSPAWNER_H_

#include "frontier/MyEngine.h"
#include "glm.hpp"

class AsteroidSpawner : public frontier::Component
{
private:
	std::weak_ptr<frontier::Pooler> AsteroidPooler;
	std::weak_ptr<frontier::Entity> Player;
	bool _doSpawn;
	int spawnCooldownTime, countedFrames, asteroidLimit, initalSpawnCooldownTime, intialCounter;
	void Spawn();
	glm::vec3 GetAsteroidDirection(float val1, float val2);
	bool _initialSpawn;

public:
	void OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<frontier::Pooler> _asteroidPooler);
	void OnTick() override;
	void SetPlayer(std::weak_ptr<frontier::Entity> _player);
		
};

#endif // !ASTEROIDSPAWNER_H_