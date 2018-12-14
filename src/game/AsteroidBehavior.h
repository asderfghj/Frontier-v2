#ifndef ASTEROIDBEHAVIOR_H_
#define ASTEROIDBEHAVIOR_H_

#include "glm.hpp"
#include "frontier/myengine.h"


class AsteroidBehavior: public frontier::Component
{
private:
	glm::vec3 ForwardVector;
	float forwardSpeed;
	float rotateForce;
	bool randomiserOverride = false;

public:
	void OnInit(std::weak_ptr<frontier::Entity> _parent);
	void OnTick() override;
	void OnActivate() override;
	void SetDirection(glm::vec3 newDirection);
	void setRandomiserOverride(bool _override);
};

#endif // !ASTEROIDBEHAVIOR_H_