#include "FPSCamera.h"
#include <SDL2/SDL.h>
#include "gtc/matrix_transform.hpp"
#include "graphicsextension/LightController.h"
#include "graphicsextension/DirectionalLight.h"

void FPSCamera::OnInit(std::weak_ptr<frontier::Entity> _parent)
{
	frontier::Component::OnInit(_parent);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	m_sensitivity = 0.05f;
	m_moveSpeed = 5.0f;
	m_yPos = _parent.lock()->getComponent<frontier::Transform>()->GetPosition().y;
}

void FPSCamera::OnTick()
{
	float xOffset = GetCore()->GetInput()->GetMousePos().x;
	float yOffset = GetCore()->GetInput()->GetMousePos().y;
	//m_lastMousePos = GetCore()->GetInput()->GetMousePos();


	xOffset *= m_sensitivity;
	yOffset *= m_sensitivity;

	m_pitch -= yOffset;
	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	m_yaw += xOffset;


	glm::vec3 forward;

	forward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	forward.y = sin(glm::radians(m_pitch));
	forward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	forwardVector = glm::normalize(forward);

	GetEntity()->getComponent<frontier::Camera>()->SetCustomViewMatrix(glm::lookAt(GetEntity()->getComponent<frontier::Transform>()->GetPosition(), GetEntity()->getComponent<frontier::Transform>()->GetPosition() + forwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

	GetEntity()->getComponent<frontier::Transform>()->SetRotation(glm::vec3(m_pitch, m_yaw, 0.0f));


	if (GetInput()->GetKey(frontier::Input::W_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() += forwardVector * (m_moveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::S_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() -= forwardVector * (m_moveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::A_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() -= glm::normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f))) * (m_moveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::D_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() += glm::normalize(glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f))) * (m_moveSpeed * GetEnvironment()->GetDeltaTime()));
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(GetEntity()->getComponent<frontier::Transform>()->GetPosition().x, m_yPos, GetEntity()->getComponent<frontier::Transform>()->GetPosition().z));
	}

	if (GetInput()->GetKey(frontier::Input::Q_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() +=  glm::vec3(0.0f, 1.0f, 0.0f) * (m_moveSpeed * GetEnvironment()->GetDeltaTime()));
		m_yPos = GetEntity()->getComponent<frontier::Transform>()->GetPosition().y;
	}

	if (GetInput()->GetKey(frontier::Input::E_KEY))
	{
		GetEntity()->getComponent<frontier::Transform>()->SetPosition(GetEntity()->getComponent<frontier::Transform>()->GetPosition() -= glm::vec3(0.0f, 1.0f, 0.0f) * (m_moveSpeed * GetEnvironment()->GetDeltaTime()));
		m_yPos = GetEntity()->getComponent<frontier::Transform>()->GetPosition().y;
	}

	if (GetInput()->GetKey(frontier::Input::O_KEY))
	{
		GetCore()->setShaderMode(frontier::Core::BLINN_PHONG);
	}

	if (GetInput()->GetKey(frontier::Input::P_KEY))
	{
		GetCore()->setShaderMode(frontier::Core::PBR);
	}

	if (GetInput()->GetKey(frontier::Input::Z_KEY))
	{
		if (GetCore()->GetLightController()->HasDirectionalLight())
		{
			float newLightColor = GetCore()->GetLightController()->GetDirectionalLight()->getLightColor().x + 0.05f;
			if (newLightColor > 1.0f)
			{
				newLightColor = 1.0f;
			}
			GetCore()->GetLightController()->GetDirectionalLight()->setLightColor(glm::vec3(newLightColor));
		}
	}

	if (GetInput()->GetKey(frontier::Input::X_KEY))
	{
		if (GetCore()->GetLightController()->HasDirectionalLight())
		{
			float newLightColor = GetCore()->GetLightController()->GetDirectionalLight()->getLightColor().x - 0.05f;
			if (newLightColor < 0.05f)
			{
				newLightColor = 0.05f;
			}
			GetCore()->GetLightController()->GetDirectionalLight()->setLightColor(glm::vec3(newLightColor));
		}
	}
}

glm::vec3 FPSCamera::GetForwardVector()
{
	return forwardVector;
}