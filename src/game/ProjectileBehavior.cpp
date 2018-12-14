#include "ProjectileBehavior.h"
#include "PlayerController.h"



void ProjectileBehavior::OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<frontier::Entity> _player)
{
	Component::OnInit(_parent);
	player = _player;
	speed = 8.0f;
}

void ProjectileBehavior::OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<ProjectileBehavior> _original)
{
	Component::OnInit(_parent);
	player = _original.lock()->GetPlayer();
	speed = 8.0f;
}

void ProjectileBehavior::OnTick()
{
	GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() + (forwardVector * (-speed * GetEnvironment()->GetDeltaTime())));

	if (GetEntity()->getComponent<frontier::Transform>()->GetPosition().x > 50 || GetEntity()->getComponent<frontier::Transform>()->GetPosition().x < -50 || GetEntity()->getComponent<frontier::Transform>()->GetPosition().z > 40 || GetEntity()->getComponent<frontier::Transform>()->GetPosition().z < -40)
	{
		GetEntity()->SetActive(false);
	}

}

void ProjectileBehavior::OnActivate()
{
	GetEntity()->getComponent<frontier::Transform>()->SetPosition(player.lock()->getComponent<frontier::Transform>()->GetPosition());
	forwardVector = player.lock()->getComponent<PlayerController>()->getForwardVector();
}

std::weak_ptr<frontier::Entity> ProjectileBehavior::GetPlayer()
{
	return player;
}
