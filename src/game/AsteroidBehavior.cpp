#include "AsteroidBehavior.h"
#include "frontier/MyEngine.h"
#include "PlayerController.h"
#include "ProjectileBehavior.h"


	void AsteroidBehavior::OnInit(std::weak_ptr<frontier::Entity> _parent)
	{
		Component::OnInit(_parent);
		m_copyable = true;

		if (!randomiserOverride)
		{

			if (_parent.lock()->hasComponent<frontier::Transform>())
			{
				float scalar = _parent.lock()->GetCore()->GetEnvironment()->GetRandomBetweenTwoValues(0.05f, 0.3f);

				GetEntity()->getComponent<frontier::Transform>()->SetScale(glm::vec3(scalar, scalar, scalar));
			}

			glm::normalize(ForwardVector);
		}

		forwardSpeed = GetEnvironment()->GetRandomBetweenTwoValues(1.0f, 3.0f);

		if (GetEnvironment()->GetRandomBetweenTwoValues(1.0f, 10.0f) > 5.0f)
		{
			rotateForce = forwardSpeed;
		}
		else
		{
			rotateForce = -forwardSpeed;
		}
	}

	void AsteroidBehavior::OnActivate()
	{

		if (!randomiserOverride)
		{
			glm::vec3 direction = glm::vec3(0.0f, GetEnvironment()->GetRandomBetweenTwoValues(0.0f, 360.0f), 0.0f);


			if (GetEntity()->hasComponent<frontier::Transform>())
			{
				float scalar = GetEntity()->GetCore()->GetEnvironment()->GetRandomBetweenTwoValues(0.05f, 0.3f);

				GetEntity()->getComponent<frontier::Transform>()->SetScale(glm::vec3(scalar, scalar, scalar));
			}

			ForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
			ForwardVector.y = sin(glm::radians(direction.x));
			ForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));

			glm::normalize(ForwardVector);

		}

		forwardSpeed = GetEnvironment()->GetRandomBetweenTwoValues(1.0f, 3.0f);

		if (GetEnvironment()->GetRandomBetweenTwoValues(1.0f, 10.0f) > 5.0f)
		{
			rotateForce = forwardSpeed;
		}
		else
		{
			rotateForce = -forwardSpeed;
		}
	}

	void AsteroidBehavior::OnTick()
	{

		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() + (ForwardVector * (-forwardSpeed * GetEnvironment()->GetDeltaTime())));

		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, 0.0f, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));

		GetEntity()->getComponent<frontier::Transform>()->SetRotation(GetEntity()->getComponent<frontier::Transform>()->GetRotation() + (glm::vec3(1.0f) * (rotateForce * GetEnvironment()->GetDeltaTime())));

		if (GetEntity()->getComponent<frontier::Transform>()->GetPosition().x > 50)
		{
			GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(-49, GetEntity()->getComponent<frontier::Transform>()->GetPosition().y, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
		}

		if (GetEntity()->getComponent<frontier::Transform>()->GetPosition().x < -50)
		{
			GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(49, GetEntity()->getComponent<frontier::Transform>()->GetPosition().y, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
		}

		if (GetEntity()->getComponent<frontier::Transform>()->GetPosition().z > 40)
		{
			GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, GetEntity()->getComponent<frontier::Transform>()->GetPosition().y, -39));
		}

		if (GetEntity()->getComponent<frontier::Transform>()->GetPosition().z < -40)
		{
			GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, GetEntity()->getComponent<frontier::Transform>()->GetPosition().y, 39));
		}

		if (GetEntity()->getComponent<frontier::Collider>()->IsColliding())
		{
			std::vector<std::weak_ptr<frontier::Entity>> _collidingEntities = GetEntity()->getComponent<frontier::Collider>()->GetCollidingEntities();
			for (size_t i = 0; i < _collidingEntities.size(); i++)
			{
				if (_collidingEntities[i].lock()->hasComponent<ProjectileBehavior>())
				{
					_collidingEntities[i].lock()->SetActive(false);
					if (GetEntity()->getComponent<frontier::Transform>()->GetScale().x > 0.1f)
					{
						glm::vec3 direction = glm::vec3(0.0f, GetEnvironment()->GetRandomBetweenTwoValues(0.0f, 360.0f), 0.0f);
						glm::vec3 newForwardVector;

						newForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
						newForwardVector.y = sin(glm::radians(direction.x));
						newForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));

						glm::normalize(newForwardVector);

						std::weak_ptr<frontier::Entity> newAsteroid1 = GetCore()->GetPooler("asteroidpooler")->Spawn(GetEntity()->getComponent<frontier::Transform>()->GetPosition());
						newAsteroid1.lock()->getComponent<frontier::Transform>()->SetScale(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetScale().x / 2, GetEntity()->getComponent<frontier::Transform>()->GetScale().y / 2, GetEntity()->getComponent<frontier::Transform>()->GetScale().z / 2));
						newAsteroid1.lock()->getComponent<AsteroidBehavior>()->setRandomiserOverride(true);
						newAsteroid1.lock()->getComponent<AsteroidBehavior>()->SetDirection(newForwardVector);

						std::weak_ptr<frontier::Entity> newAsteroid2 = GetCore()->GetPooler("asteroidpooler")->Spawn(GetEntity()->getComponent<frontier::Transform>()->GetPosition());
						newAsteroid2.lock()->getComponent<frontier::Transform>()->SetScale(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetScale().x / 2, GetEntity()->getComponent<frontier::Transform>()->GetScale().y / 2, GetEntity()->getComponent<frontier::Transform>()->GetScale().z / 2));
						newAsteroid2.lock()->getComponent<AsteroidBehavior>()->setRandomiserOverride(true);
						newAsteroid2.lock()->getComponent<AsteroidBehavior>()->SetDirection(-newForwardVector);

						
					}

					randomiserOverride = false;
					GetEntity()->SetActive(false);
				}
				else if (_collidingEntities[i].lock()->hasComponent<PlayerController>())
				{
					if (!_collidingEntities[i].lock()->getComponent<PlayerController>()->IsGameOver() && !_collidingEntities[i].lock()->getComponent<PlayerController>()->IsInvicible())
					{
						_collidingEntities[i].lock()->getComponent<PlayerController>()->Hit();
						GetEntity()->SetActive(false);
					}

				}
			}
		}


	}

	void AsteroidBehavior::SetDirection(glm::vec3 _direction)
	{
		ForwardVector = _direction;
	}

	void AsteroidBehavior::setRandomiserOverride(bool _override)
	{
		randomiserOverride = _override;
	}
