#ifndef PROJECTILEBEHAVIOR_H_
#define PROJECTILEBEHAVIOR_H_

#include "frontier/MyEngine.h"
#include "glm.hpp"


class ProjectileBehavior : public frontier::Component
{
public:
	void OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<frontier::Entity> _player);
	void OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<ProjectileBehavior> _original);
	void OnTick() override;
	void OnActivate() override;
	std::weak_ptr<frontier::Entity> GetPlayer();

private:
	glm::vec3 forwardVector;
	float speed;
	std::weak_ptr<frontier::Entity> player;
};

#endif