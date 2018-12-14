#include "DirectionalLight.h"
#include "frontier/Shader.h"
#include "frontier/Entity.h"
#include "frontier/Transform.h"
#include "frontier/Core.h"
#include "LightController.h"
#include "gtc/matrix_transform.hpp"
#include "DepthMap.h"

namespace frontier
{
	void DirectionalLight::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction)
	{
		Light::OnInit(_parent, _ambient, _diffuse, _specular);
		m_direction = _direction;
		_parent.lock()->GetCore()->GetLightController()->SetDirectionalLight(_parent);
		m_lightProjectionMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 200.0f);
		m_depthMap = std::make_shared<DepthMap>(1024, 1024, 8);
	}

	void DirectionalLight::SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
	{
		std::string directionUniformID = _uniformName + "[0].direction";

		_shader.lock()->SetUniform(directionUniformID.c_str(), m_direction);

		std::string ambientUniformID = _uniformName + "[0].ambient";

		_shader.lock()->SetUniform(ambientUniformID.c_str(), m_ambient);

		std::string diffuseUniformID = _uniformName + "[0].diffuse";

		_shader.lock()->SetUniform(diffuseUniformID.c_str(), m_diffuse);

		std::string specularUniformID = _uniformName + "[0].specular";

		_shader.lock()->SetUniform(specularUniformID.c_str(), m_specular);

		std::string shadowMapUniformID = _uniformName + "[0].shadowMap";

		_shader.lock()->SetUniform(shadowMapUniformID.c_str(), m_depthMap);

		m_depthMap->BindTexture();
	}

	void DirectionalLight::SetLightUniformPBR(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
	{
		std::string directionUniformID = _uniformName + "[0].direction";

		_shader.lock()->SetUniform(directionUniformID.c_str(), m_direction);

		std::string colorUniformID = _uniformName + "[0].color";

		glm::vec3 modifiedColor = m_diffuse * 5.0f;

		_shader.lock()->SetUniform(colorUniformID.c_str(), modifiedColor);

	}

	void DirectionalLight::OnTick()
	{
		GetCore()->RequestDepthMapRender(m_depthMap);
	}

	glm::mat4 DirectionalLight::getLightSpaceMatrix()
	{
		glm::mat4 lightViewMatrix = glm::lookAt(m_direction * -1.0f, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		return m_lightProjectionMatrix * lightViewMatrix;
	}

	glm::vec3 DirectionalLight::getDirection()
	{
		return m_direction;
	}

	glm::vec3 DirectionalLight::getLightColor()
	{
		return m_diffuse;
	}

	void DirectionalLight::setLightColor(glm::vec3 _newColor)
	{
		m_diffuse = _newColor;
		m_specular = _newColor;
	}

	std::shared_ptr<DepthMap> DirectionalLight::getDepthMap()
	{
		return m_depthMap;
	}
}