#include "LightController.h"
#include <iostream>

#include "frontier/Core.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "frontier/Entity.h"
#include "frontier/Shader.h"

namespace frontier
{
	LightController::LightController(std::weak_ptr<Core> _corePtr)
	{
		m_corePtr = _corePtr;
	}

	void LightController::AddPointLight(std::weak_ptr<Entity> _newPointLight)
	{
		m_pointLights.push_back(_newPointLight);
	}

	void LightController::SetDirectionalLight(std::weak_ptr<Entity> _directionalLight)
	{
		m_directionalLight = _directionalLight;
	}

	void LightController::AddSpotLight(std::weak_ptr<Entity> _newSpotLight)
	{
		m_spotLights.push_back(_newSpotLight);
	}

	void LightController::SetLightUniformValues(std::shared_ptr<Shader> _shader)
	{
		if (!m_directionalLight.expired())
		{
			_shader->SetUniform("NR_DIR_LIGHTS", 1);
			m_directionalLight.lock()->getComponent<DirectionalLight>()->SetLightUniform("dirlight", _shader);
		}
		else
		{
			_shader->SetUniform("NR_DIR_LIGHTS", 0);
		}
		_shader->SetUniform("hasDirLight", HasDirectionalLight());
		for (int i = 0; i < m_pointLights.size(); i++)
		{
			m_pointLights[i].lock()->getComponent<PointLight>()->SetLightUniform("pointlights", _shader, i);
		}

		_shader->SetUniform("NR_POINT_LIGHTS", (int)m_pointLights.size());

		for (int i = 0; i < m_spotLights.size(); i++)
		{
			m_spotLights[i].lock()->getComponent<SpotLight>()->SetLightUniform("spotlights", _shader, i);
		}

		_shader->SetUniform("NR_SPOT_LIGHTS", (int)m_spotLights.size());

	}

	glm::mat4 LightController::GetLightSpacematrix()
	{
		return m_directionalLight.lock()->getComponent<DirectionalLight>()->getLightSpaceMatrix();
	}

	glm::vec3 LightController::GetDirectionalLightPosition()
	{
		return m_directionalLight.lock()->getComponent<DirectionalLight>()->getDirection();
	}

	std::shared_ptr<DepthMap> LightController::GetDirectionalLightDepthMap()
	{
		return m_directionalLight.lock()->getComponent<DirectionalLight>()->getDepthMap();
	}

	void LightController::SetLightUniformValuesPBR(std::shared_ptr<Shader> _shader)
	{
		if (!m_directionalLight.expired())
		{
			_shader->SetUniform("NR_DIR_LIGHTS", 1);
			m_directionalLight.lock()->getComponent<DirectionalLight>()->SetLightUniformPBR("dirlights", _shader);
		}
		else
		{
			_shader->SetUniform("NR_DIR_LIGHTS", 0);
		}
		for (int i = 0; i < m_pointLights.size(); i++)
		{
			m_pointLights[i].lock()->getComponent<PointLight>()->SetLightUniformPBR("pointlights", _shader, i);
		}

		_shader->SetUniform("NR_POINT_LIGHTS", (int)m_pointLights.size());
	}

	bool LightController::HasDirectionalLight()
	{
		if (!m_directionalLight.expired())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::shared_ptr<DirectionalLight> LightController::GetDirectionalLight()
	{
		return m_directionalLight.lock()->getComponent<DirectionalLight>();
	}
}