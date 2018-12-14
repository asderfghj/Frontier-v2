#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "frontier/MyEngine.h"
#include "glm.hpp"

class PlayerController : public frontier::Component
{
public:
	void OnInit(std::weak_ptr<frontier::Entity> _parent);
	void OnTick() override;
	glm::vec3 getForwardVector();
	void setUIIcons(std::weak_ptr<frontier::Entity> _icon1, std::weak_ptr<frontier::Entity> _icon2, std::weak_ptr<frontier::Entity> _icon3, std::weak_ptr<frontier::Entity> _gameOver);
	void setAudioPlayers(std::weak_ptr<frontier::AudioPlayer> _shootSound, std::weak_ptr<frontier::AudioPlayer> _crashSound);
	void Hit();
	bool IsGameOver();
	bool IsInvicible();

private:

	float RotateVelocity, ForwardVelocity, RotateFade, ForwardFade, RotateIncreaseAmount, ForwardIncreaseAmount, ForwardVelocityCap, RotateVelocityCap; 
	glm::vec3 forwardVector;
	bool shooting, hasshot, gameOver, isInvicible;
	int shotCooldownTime, countedFrames, life, invincibleCooldownTime, invincibleCounter;
	std::weak_ptr<frontier::Entity> _lifeIcon1, _lifeIcon2, _lifeIcon3, _gameOverText;
	std::weak_ptr<frontier::AudioPlayer> shootSound, crashSound;

};


#endif // !PLAYERCONTROLLER_H_