#include "SpotLight.h"
#include "frontier/Shader.h"
#include "frontier/Entity.h"
#include "frontier/Transform.h"
#include "frontier/Core.h"
#include "LightController.h"

namespace frontier
{
	void SpotLight::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction, float _constant, float _linear, float _quadratic, float _cutoff, float _outerCutoff)
	{
		Light::OnInit(_parent, _ambient, _diffuse, _specular);
		m_direction = _direction;
		m_constant = _constant;
		m_linear = _linear;
		m_quadratic = _quadratic;
		m_cutoff = _cutoff;
		m_outerCutoff = _outerCutoff;
		_parent.lock()->GetCore()->GetLightController()->AddSpotLight(_parent);
	}

	void SpotLight::SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
	{
		std::string arrayIndexStr = "";

		if (_index > -1)
		{
			arrayIndexStr = "[" + std::to_string(_index) + "]";
		}

		std::string positionUniformID = _uniformName + arrayIndexStr + ".position";

		_shader.lock()->SetUniform(positionUniformID.c_str(), GetEntity()->getComponent<Transform>()->GetPosition());

		std::string directionUniformID = _uniformName + arrayIndexStr + ".direction";

		_shader.lock()->SetUniform(directionUniformID.c_str(), m_direction);

		std::string ambientUniformID = _uniformName + arrayIndexStr + ".ambient";

		_shader.lock()->SetUniform(ambientUniformID.c_str(), m_ambient);

		std::string diffuseUniformID = _uniformName + arrayIndexStr + ".diffuse";

		_shader.lock()->SetUniform(diffuseUniformID.c_str(), m_diffuse);

		std::string specularUniformID = _uniformName + arrayIndexStr + ".specular";

		_shader.lock()->SetUniform(specularUniformID.c_str(), m_specular);

		std::string constantUniformID = _uniformName + arrayIndexStr + ".constant";

		_shader.lock()->SetUniform(constantUniformID.c_str(), m_constant);

		std::string linearUniformID = _uniformName + arrayIndexStr + ".linear";

		_shader.lock()->SetUniform(linearUniformID.c_str(), m_linear);

		std::string quadraticUniformID = _uniformName + arrayIndexStr + ".quadratic";

		_shader.lock()->SetUniform(quadraticUniformID.c_str(), m_quadratic);

		std::string cutoffUniformID = _uniformName + arrayIndexStr + ".cutoff";

		_shader.lock()->SetUniform(cutoffUniformID.c_str(), glm::radians(m_cutoff));

		std::string cutoffOuterUniformID = _uniformName + arrayIndexStr + ".outercutoff";

		_shader.lock()->SetUniform(cutoffOuterUniformID.c_str(), glm::radians(m_outerCutoff));

	}

	void SpotLight::setCutoffs(float _inner, float _outer)
	{
		m_cutoff = _inner;
		m_outerCutoff = _outer;
	}

	float SpotLight::getOuterCutoff()
	{
		return m_outerCutoff;
	}

	float SpotLight::getInnerCutoff()
	{
		return m_cutoff;
	}

	void SpotLight::outputAngleData()
	{
		std::cout << "Inner: " << m_cutoff << " Outer: " << m_outerCutoff << std::endl;
	}
}