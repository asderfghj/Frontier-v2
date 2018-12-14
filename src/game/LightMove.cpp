#include "LightMove.h"
#include "frontier/Entity.h"
#include "graphicsextension/SpotLight.h"
#include "frontier/Transform.h"
#include "frontier/Input.h"
#include "frontier/Environment.h"

void LightMove::OnInit(std::weak_ptr<frontier::Entity> _parent)
{
	frontier::Component::OnInit(_parent);
	/*if (!_parent.lock()->hasComponent<frontier::SpotLight>())
	{
		std::cout << "Light move compoenent needs a spotlight" << std::endl;
		throw std::exception();
	}*/
	m_lightMoveSpeed = 0.5f;
	m_lightAdjustSpeed = 0.5f;
}

void LightMove::OnTick()
{
	if (GetInput()->GetKey(frontier::Input::UP_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() += glm::vec3(0.0f, 0.0f, 1.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::DOWN_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() -= glm::vec3(0.0f, 0.0f, 1.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::LEFT_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() -= glm::vec3(1.0f, 0.0f, 0.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::RIGHT_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() += glm::vec3(1.0f, 0.0f, 0.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::O_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() += glm::vec3(0.0f, 1.0f, 0.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
		m_yPos = GetEntity()->getComponent<frontier::Transform>()->GetPosition().y;
	}

	if (GetInput()->GetKey(frontier::Input::P_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() -= glm::vec3(0.0f, 1.0f, 0.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
		m_yPos = GetEntity()->getComponent<frontier::Transform>()->GetPosition().y;
	}

	if (GetInput()->GetKey(frontier::Input::K_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetRotation(GetEntity()->getComponent<frontier::Transform>()->GetRotation() -= glm::vec3(0.0f, 1.0f, 0.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
	}

	if (GetInput()->GetKey(frontier::Input::L_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetRotation(GetEntity()->getComponent<frontier::Transform>()->GetRotation() += glm::vec3(0.0f, 1.0f, 0.0f) * (m_lightMoveSpeed * GetEnvironment()->GetDeltaTime()));
	}



}
