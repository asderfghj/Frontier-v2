#include "PlayerController.h"
#include "frontier/MyEngine.h"


void PlayerController::OnInit(std::weak_ptr<frontier::Entity> _parent)
{
	Component::OnInit(_parent);
	RotateVelocity = 0.0f;
	RotateVelocityCap = 10.0f;
	ForwardVelocity = 0.0f;
	ForwardVelocityCap = 5.0f;
	RotateFade = 0.1f;
	ForwardFade = 0.05f;
	RotateIncreaseAmount = 0.3f;
	ForwardIncreaseAmount = 0.2f;
	shotCooldownTime = 15;
	countedFrames = 0;
	life = 3;
	gameOver = false;
	forwardVector.x = cos(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().x)) * sin(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().y));
	forwardVector.y = sin(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().x));
	forwardVector.z = cos(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().x)) * cos(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().y));
	forwardVector = glm::normalize(forwardVector);
}

void PlayerController::OnTick()
{
	bool moveForward, rotateLeft, rotateRight;

	if (GetInput()->IsJoystickConnected())
	{
		moveForward = GetInput()->GetJoystickAxis(frontier::Input::LEFTSTICK).y < -8000;
		rotateLeft = GetInput()->GetJoystickAxis(frontier::Input::LEFTSTICK).x < -8000;
		rotateRight = GetInput()->GetJoystickAxis(frontier::Input::LEFTSTICK).x > 8000;
		shooting = GetInput()->GetJoystickButton(frontier::Input::A_BUTTON);
	}
	else
	{
		moveForward = GetInput()->GetKey(frontier::Input::W_KEY);
		rotateLeft = GetInput()->GetKey(frontier::Input::A_KEY);
		rotateRight = GetInput()->GetKey(frontier::Input::D_KEY);
		shooting = GetInput()->GetKey(frontier::Input::O_KEY);
	}

	if (moveForward)
	{
		ForwardVelocity += ForwardIncreaseAmount;
	}

	if (rotateLeft)
	{
		RotateVelocity += RotateIncreaseAmount;
	}
	else if (rotateRight)
	{
		RotateVelocity -= RotateIncreaseAmount;
	}

	if (ForwardVelocity > 0)
	{
		ForwardVelocity -= ForwardFade;
	}
	if (ForwardVelocity < 0)
	{
		ForwardVelocity = 0;
	}
	if (ForwardVelocity > ForwardVelocityCap)
	{
		ForwardVelocity = ForwardVelocityCap;
	}

	if (RotateVelocity > 0)
	{
		RotateVelocity -= RotateFade;
	}
	if (RotateVelocity < 0)
	{
		RotateVelocity += RotateFade;
	}

	if ((RotateVelocity < 0.2f && RotateVelocity > -0.2f) && (!rotateLeft || !rotateRight))
	{
		RotateVelocity = 0;
	}

	if (RotateVelocity > RotateVelocityCap)
	{
		RotateVelocity = RotateVelocityCap;
	}
	if (RotateVelocity < -RotateVelocityCap)
	{
		RotateVelocity = -RotateVelocityCap;
	}

	if (RotateVelocity > 0 || RotateVelocity < 0)
	{
		glm::vec3 rotation = GetEntity()->getComponent<frontier::Transform>()->GetRotation();
		GetEntity()->getComponent<frontier::Transform>()->SetRotation(glm::vec3(rotation.x, rotation.y + (RotateVelocity * GetEnvironment()->GetDeltaTime()), rotation.z));



		forwardVector.x = cos(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().x)) * sin(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().y));
		forwardVector.y = sin(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().x));
		forwardVector.z = cos(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().x)) * cos(glm::radians(GetEntity()->getComponent<frontier::Transform>()->GetRotation().y));
		forwardVector = glm::normalize(forwardVector);

	}

	if (ForwardVelocity > 0)
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() + (forwardVector * (-ForwardVelocity * GetEnvironment()->GetDeltaTime())));
	}

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
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3( GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, GetEntity()->getComponent<frontier::Transform>()->GetPosition().y, -39));
	}

	if (GetEntity()->getComponent<frontier::Transform>()->GetPosition().z < -40)
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, GetEntity()->getComponent<frontier::Transform>()->GetPosition().y, 39));
	}

	if (shooting && !hasshot)
	{
		shootSound.lock()->PlayWithVariance(1.0f, 0.9f, 1.1f);
		GetCore()->GetPooler("missilepooler")->Spawn(GetEntity()->getComponent<frontier::Transform>()->GetPosition());
		hasshot = true;
		countedFrames = 0;
	}
	else if (hasshot)
	{
		countedFrames++;
		if (countedFrames > shotCooldownTime)
		{
			hasshot = false;
		}
	}

	if (isInvicible)
	{
		if (invincibleCounter >= invincibleCooldownTime)
		{
			invincibleCounter = 0;
			isInvicible = false;
		}
		else
		{
			invincibleCounter++;
		}
	}


}

glm::vec3 PlayerController::getForwardVector()
{
	return forwardVector;
}

void PlayerController::setUIIcons(std::weak_ptr<frontier::Entity> _icon1, std::weak_ptr<frontier::Entity> _icon2, std::weak_ptr<frontier::Entity> _icon3, std::weak_ptr<frontier::Entity> _gameOver)
{
	_lifeIcon1 = _icon1;
	_lifeIcon2 = _icon2;
	_lifeIcon3 = _icon3;
	_gameOverText = _gameOver;
}

void PlayerController::Hit()
{
	life--;
	crashSound.lock()->PlayWithVariance(1.0f, 0.9f, 1.1f);
	if (life >= 3)
	{
		_lifeIcon1.lock()->SetActive(true);
		_lifeIcon2.lock()->SetActive(true);
		_lifeIcon3.lock()->SetActive(true);
		isInvicible = true;
	}
	else if (life == 2)
	{
		_lifeIcon1.lock()->SetActive(true);
		_lifeIcon2.lock()->SetActive(true);
		_lifeIcon3.lock()->SetActive(false);
		isInvicible = true;
	}
	else if (life == 1)
	{
		_lifeIcon1.lock()->SetActive(true);
		_lifeIcon2.lock()->SetActive(false);
		_lifeIcon3.lock()->SetActive(false);
		isInvicible = true;
	}
	else
	{
		_lifeIcon1.lock()->SetActive(false);
		_lifeIcon2.lock()->SetActive(false);
		_lifeIcon3.lock()->SetActive(false);
		gameOver = true;
		GetCore()->DeactivateAllInstancesInPools();
		_gameOverText.lock()->SetActive(true);
		GetEntity()->SetActive(false);
	}
}

void PlayerController::setAudioPlayers(std::weak_ptr<frontier::AudioPlayer> _shootSound, std::weak_ptr<frontier::AudioPlayer> _crashSound)
{
	shootSound = _shootSound;
	crashSound = _crashSound;
}

bool PlayerController::IsGameOver()
{
	return gameOver;
}

bool PlayerController::IsInvicible()
{
	return isInvicible;
}

