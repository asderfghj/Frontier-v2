#include "frontier/MyEngine.h"
#include <memory>
#include <glm.hpp>

class FPSCamera : public frontier::Component
{
private:
	float m_sensitivity, m_pitch, m_yaw, m_moveSpeed, m_yPos = 0.0f;
	glm::vec3 forwardVector;

public:
	void OnInit(std::weak_ptr<frontier::Entity> _parent);
	void OnTick() override;
	glm::vec3 GetForwardVector();

};