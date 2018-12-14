#include "AsteroidSpawner.h"

#include "AsteroidBehavior.h"
#include "PlayerController.h"


void AsteroidSpawner::OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<frontier::Pooler> _asteroidPooler)
{
	Component::OnInit(_parent);
	AsteroidPooler = _asteroidPooler;
	_doSpawn = true;
	_initialSpawn = true;
	countedFrames = 0;
	spawnCooldownTime = 120;
	initalSpawnCooldownTime = 30;
	intialCounter = 0;
	asteroidLimit = 8;
}

void AsteroidSpawner::OnTick()
{
	if (!_initialSpawn && !Player.lock()->getComponent<PlayerController>()->IsGameOver())
	{
		if (_doSpawn)
		{
			Spawn();
			_doSpawn = false;

		}
		else
		{
			countedFrames++;
			if (countedFrames > spawnCooldownTime)
			{
				_doSpawn = true;
				countedFrames = 0;
			}
		}
	}
	else if(_initialSpawn && !Player.lock()->getComponent<PlayerController>()->IsGameOver())
	{
		if (_doSpawn)
		{
			Spawn();
			_doSpawn = false;
			intialCounter++;
			if (intialCounter >= 8)
			{
				_initialSpawn = false;
			}
		}
		else
		{
			countedFrames++;
			if (countedFrames > initalSpawnCooldownTime)
			{
				_doSpawn = true;
				countedFrames = 0;
			}
		}
	}

}

void AsteroidSpawner::Spawn()
{
	if (AsteroidPooler.lock()->GetActiveInPool() < asteroidLimit)
	{
		float determinant = GetEnvironment()->GetRandomBetweenTwoValues(0.0f, 4.0f);
		if (determinant < 1.0f)
		{
			//spawnpoint 1
			std::weak_ptr<frontier::Entity> newAsteroid = AsteroidPooler.lock()->Spawn(glm::vec3(0.0f, 0.0f, -49.0f));
			newAsteroid.lock()->getComponent<AsteroidBehavior>()->SetDirection(GetAsteroidDirection(145.0f, 205.0f));
		}
		else if (determinant >= 1.0f && determinant < 2.0f)
		{
			//spawnpoint 2
			std::weak_ptr<frontier::Entity> newAsteroid = AsteroidPooler.lock()->Spawn(glm::vec3(39.0f, 0.0f, 0.0f));
			newAsteroid.lock()->getComponent<AsteroidBehavior>()->SetDirection(GetAsteroidDirection(55.0f, 115.0f));
		}
		else if (determinant >= 2.0f && determinant < 3.0f)
		{
			//spawnpoint 3
			std::weak_ptr<frontier::Entity> newAsteroid = AsteroidPooler.lock()->Spawn(glm::vec3(0.0f, 0.0f, 49.0f));
			newAsteroid.lock()->getComponent<AsteroidBehavior>()->SetDirection(GetAsteroidDirection(330.0f, 390.0f));
		}
		else
		{
			//spawnpoint 4
			std::weak_ptr<frontier::Entity> newAsteroid = AsteroidPooler.lock()->Spawn(glm::vec3(-39.0f, 0.0f, 0.0f));
			newAsteroid.lock()->getComponent<AsteroidBehavior>()->SetDirection(GetAsteroidDirection(230.0f, 295.0f));
		}
	}
}

glm::vec3 AsteroidSpawner::GetAsteroidDirection(float val1, float val2)
{
	glm::vec3 direction = glm::vec3(0.0f, GetEnvironment()->GetRandomBetweenTwoValues(val1, val2), 0.0f);
	glm::vec3 newForwardVector;

	newForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
	newForwardVector.y = sin(glm::radians(direction.x));
	newForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));
		
	return newForwardVector;
}

void AsteroidSpawner::SetPlayer(std::weak_ptr<frontier::Entity> _player)
{
	Player = _player;
}
