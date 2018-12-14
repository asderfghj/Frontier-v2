#include "frontier/Component.h"

class LightMove : public frontier::Component
{
public:
	void OnInit(std::weak_ptr<frontier::Entity> _parent);
	void OnTick() override;
private:
	float m_lightMoveSpeed;
	float m_lightAdjustSpeed;
	float m_yPos;
};